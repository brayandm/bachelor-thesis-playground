#include "Scheduler.h"

void Scheduler::run()
{
    DataStorage dataStorage;
    InputReader::read(dataStorage.input);
    dataStorage.fitSize();

    std::vector<std::tuple<int, double, int>> frames;

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        frames.push_back({dataStorage.input.amountTTIs[j], dataStorage.input.TBS[j], j});
    }

    sort(frames.begin(), frames.end());

    std::vector<int> frameIds;

    for (auto t : frames)
    {
        frameIds.push_back(std::get<2>(t));
    }

    for (int i = 0; i < numberOfIterations; i++)
    {
        Scheduler::step(dataStorage, frameIds);

        if (i == numberOfIterations - 1)
            break;

        std::vector<double> powerPerFrame(dataStorage.input.J, 0);

        for (int j = 0; j < dataStorage.input.J; j++)
        {
            for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
            {
                for (int r = 0; r < dataStorage.input.R; r++)
                {
                    for (int k = 0; k < dataStorage.input.K; k++)
                    {
                        if (dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] == true)
                        {
                            powerPerFrame[j] += dataStorage.output.p[k][r][dataStorage.input.userId[j]][t];

                            dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] = false;
                            dataStorage.output.p[k][r][dataStorage.input.userId[j]][t] = 0;
                        }
                    }
                }
            }
        }

        std::vector<std::tuple<double, int>> powerPerFrameWithId;

        for (int j = 0; j < dataStorage.input.J; j++)
        {
            powerPerFrameWithId.push_back({powerPerFrame[j], j});
        }

        sort(powerPerFrameWithId.begin(), powerPerFrameWithId.end());

        frameIds.clear();

        for (auto t : powerPerFrameWithId)
        {
            frameIds.push_back(std::get<1>(t));
        }
    }

    Printer::printResult(dataStorage);
}

void Scheduler::step(DataStorage &dataStorage, std::vector<int> frameIds)
{
    std::vector<std::vector<std::vector<bool>>>
        resourceOcupation(dataStorage.input.T, std::vector<std::vector<bool>>(dataStorage.input.R, std::vector<bool>(dataStorage.input.K, false)));

    std::vector<std::vector<bool>>
        resourceBlockOcupation(dataStorage.input.T, std::vector<bool>(dataStorage.input.R, false));

    std::vector<std::vector<bool>>
        cellOcupation(dataStorage.input.T, std::vector<bool>(dataStorage.input.K, false));

    for (auto frameId : frameIds)
    {
        int j = frameId;
        int n = dataStorage.input.userId[j];

        std::vector<std::tuple<int, int, int>> options = {};

        std::vector<int> TTIOccupation(dataStorage.input.T, false);

        double g = 0;

        bool isSent = false;

        while (true)
        {
            int bestRBG = -1;
            int bestTTI = -1;
            int bestCell = -1;
            double maxSINR0 = -1e9;

            for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
            {
                if (TTIOccupation[t] == true)
                    continue;

                for (int r = 0; r < dataStorage.input.R; r++)
                {
                    if (resourceBlockOcupation[t][r] == true)
                        continue;

                    for (int k = 0; k < dataStorage.input.K; k++)
                    {
                        // if (cellOcupation[t][k] == true)
                        //     continue;

                        if (dataStorage.input.s0[k][r][n][t] > maxSINR0)
                        {
                            maxSINR0 = dataStorage.input.s0[k][r][n][t];
                            bestRBG = r;
                            bestTTI = t;
                            bestCell = k;
                        }
                    }
                }
            }

            if (bestRBG != -1)
            {
                resourceOcupation[bestTTI][bestRBG][bestCell] = true;
                resourceBlockOcupation[bestTTI][bestRBG] = true;
                cellOcupation[bestTTI][bestCell] = true;
                TTIOccupation[bestTTI] = true;

                dataStorage.output.p[bestCell][bestRBG][n][bestTTI] = 1;
                dataStorage.output.b[bestCell][bestRBG][n][bestTTI] = true;
                options.push_back({bestTTI, bestRBG, bestCell});

                g = DataTransmissionCalculator::computeGforFrameWithoutInterferences(dataStorage, j);

                if (g > dataStorage.input.TBS[j] + EPS)
                {
                    isSent = true;
                    break;
                }
            }
            else
            {
                for (auto option : options)
                {
                    int t = std::get<0>(option);
                    int r = std::get<1>(option);
                    int k = std::get<2>(option);

                    resourceOcupation[t][r][k] = false;
                    resourceBlockOcupation[t][r] = false;
                    cellOcupation[t][k] = false;
                    TTIOccupation[t] = false;

                    dataStorage.output.p[k][r][n][t] = 0;
                    dataStorage.output.b[k][r][n][t] = false;
                }

                options.clear();

                isSent = false;
                break;
            }
        }
    }
}