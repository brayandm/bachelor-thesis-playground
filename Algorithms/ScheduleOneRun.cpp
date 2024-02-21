#include "ScheduleOneRun.h"

void ScheduleOneRun::run()
{
    DataStorage dataStorage;
    InputReader inputReader;

    inputReader.read(dataStorage.input);

    DataTransmissionCalculator dataTransmissionCalculator;

    std::vector<std::tuple<int, double, int>> frames;

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        frames.push_back({dataStorage.input.amountTTIs[j], dataStorage.input.TBS[j], j});
    }

    sort(frames.begin(), frames.end());

    std::vector<std::vector<std::pair<int, int>>> resourceBlockOcupation(dataStorage.input.T, std::vector<std::pair<int, int>>(dataStorage.input.R, {-1, -1}));

    for (auto frame : frames)
    {
        int j = std::get<2>(frame);

        double g = 0;

        std::vector<std::tuple<int, int, int>> ocuppiedCells;

        for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
        {
            int bestRBG = -1;
            int bestCell = -1;
            double maxSINR0 = -1e9;

            for (int r = 0; r < dataStorage.input.R; r++)
            {
                if (resourceBlockOcupation[t][r] != std::pair<int, int>(-1, -1))
                    continue;

                for (int k = 0; k < dataStorage.input.K; k++)
                {
                    if (dataStorage.input.s0[k][r][dataStorage.input.userId[j]][t] > maxSINR0)
                    {
                        maxSINR0 = dataStorage.input.s0[k][r][dataStorage.input.userId[j]][t];
                        bestRBG = r;
                        bestCell = k;
                    }
                }
            }

            if (bestRBG != -1)
            {
                resourceBlockOcupation[t][bestRBG] = {bestCell, dataStorage.input.userId[j]};
                ocuppiedCells.push_back({t, bestRBG, bestCell});
                dataStorage.output.p[bestCell][bestRBG][dataStorage.input.userId[j]][t] = 1;
                dataStorage.output.b[bestCell][bestRBG][dataStorage.input.userId[j]][t] = true;

                g += dataTransmissionCalculator.computeGforFrameWithoutInterferences(dataStorage, j, t);

                if (g > dataStorage.input.TBS[j] + EPS)
                    break;
            }
        }

        if (g < dataStorage.input.TBS[j] + EPS)
        {
            for (auto cell : ocuppiedCells)
            {
                int t = std::get<0>(cell);
                int r = std::get<1>(cell);
                int k = std::get<2>(cell);

                resourceBlockOcupation[t][r] = {-1, -1};
                dataStorage.output.p[k][r][dataStorage.input.userId[j]][t] = 0;
                dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] = false;
            }
        }
    }

    Printer printer;
    printer.printResult(dataStorage);
}