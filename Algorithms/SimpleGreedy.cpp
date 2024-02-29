#include "SimpleGreedy.h"

void SimpleGreedy::run()
{
    DataStorage dataStorage;
    InputReader::read(dataStorage.input);
    dataStorage.fitSize();

    SimpleGreedy::step(dataStorage, FrameSorter::getFramesSortByTTIAndTBS(dataStorage));

    for (int iteration = 0; iteration < numberOfIterations; iteration++)
    {
        std::vector<int> frameIds = FrameSorter::getFramesSortRandom(dataStorage);

        dataStorage.output.clean();

        SimpleGreedy::step(dataStorage, frameIds);
    }

    Printer::printResult(dataStorage);
}

void SimpleGreedy::step(DataStorage &dataStorage, std::vector<int> frameIds)
{
    std::vector<std::vector<bool>>
        resourceBlockOcupation(dataStorage.input.T, std::vector<bool>(dataStorage.input.R, false));

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
            double maxSINR0 = -1e9;

            for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
            {
                if (TTIOccupation[t] == true)
                    continue;

                for (int r = 0; r < dataStorage.input.R; r++)
                {
                    if (resourceBlockOcupation[t][r] == true)
                        continue;

                    double totalSINR0 = 0;

                    for (int k = 0; k < dataStorage.input.K; k++)
                    {
                        totalSINR0 += dataStorage.input.s0[k][r][n][t];
                    }

                    if (totalSINR0 > maxSINR0)
                    {
                        maxSINR0 = totalSINR0;
                        bestRBG = r;
                        bestTTI = t;
                    }
                }
            }

            if (bestRBG != -1)
            {
                resourceBlockOcupation[bestTTI][bestRBG] = true;
                TTIOccupation[bestTTI] = true;

                for (int k = 0; k < dataStorage.input.K; k++)
                {
                    dataStorage.output.p[k][bestRBG][n][bestTTI] = 1;
                    dataStorage.output.b[k][bestRBG][n][bestTTI] = true;
                    options.push_back({bestTTI, bestRBG, k});
                }

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

                    resourceBlockOcupation[t][r] = false;

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