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

    for (auto &t : frames)
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

        for (auto &t : powerPerFrameWithId)
        {
            frameIds.push_back(std::get<1>(t));
        }
    }

    Printer::printResult(dataStorage);
}

void Scheduler::step(DataStorage &dataStorage, std::vector<int> frameIds)
{
    std::vector<std::vector<int>> resourceBlockCellAssignment(dataStorage.input.T, std::vector<int>(dataStorage.input.R, -1));

    // user, s0, p, d
    std::vector<std::vector<std::vector<std::tuple<int, double, double, double>>>> resourceBlockUserAssignment(dataStorage.input.T, std::vector<std::vector<std::tuple<int, double, double, double>>>(dataStorage.input.R, std::vector<std::tuple<int, double, double, double>>()));

    std::vector<std::vector<double>> powerLeftPerCell(dataStorage.input.T, std::vector<double>(dataStorage.input.K, dataStorage.input.R));
    std::vector<std::vector<std::vector<double>>> powerLeftPerRBGPerCell(dataStorage.input.T, std::vector<std::vector<double>>(dataStorage.input.R, std::vector<double>(dataStorage.input.K, 4.0)));

    std::vector<double> dataTransmissionPerFrame(dataStorage.input.J, 0);

    for (auto &frameId : frameIds)
    {
        int j = frameId;
        int n = dataStorage.input.userId[j];

        std::vector<std::tuple<double, int, int, int>> options = {};

        for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                if (resourceBlockCellAssignment[t][r] != -1)
                {
                    options.push_back({dataStorage.input.s0[resourceBlockCellAssignment[t][r]][r][n][t], t, r, resourceBlockCellAssignment[t][r]});
                }
                else
                {
                    for (int k = 0; k < dataStorage.input.K; k++)
                    {
                        options.push_back({dataStorage.input.s0[k][r][n][t], t, r, k});
                    }
                }
            }
        }

        sort(options.rbegin(), options.rend());

        // std::cout << "frame: " << frameId << "\n";

        std::vector<std::tuple<int, int, int, int, double, bool>> rollbacks;
        std::vector<std::tuple<int, int>> cellRollbacks;
        std::vector<std::tuple<int, int>> RBGRollbacks;
        std::vector<std::tuple<int, int, double>> powerLeftRollbacks;
        std::vector<std::tuple<int, int, int, double>> powerLeftPerRBGPerCellRollbacks;

        for (auto &option : options)
        {
            // std::cout << std::get<0>(option) << " " << std::get<1>(option) << " " << std::get<2>(option) << " " << std::get<3>(option) << "\n";

            double optionS0 = std::get<0>(option);
            int optionT = std::get<1>(option);
            int optionR = std::get<2>(option);
            int optionK = std::get<3>(option);

            if (resourceBlockCellAssignment[optionT][optionR] != -1 && resourceBlockCellAssignment[optionT][optionR] != optionK)
                continue;

            bool canAssign = true;

            for (int r = 0; r < dataStorage.input.R; r++)
            {
                if (resourceBlockCellAssignment[optionT][r] == optionK)
                {
                    for (auto &user : resourceBlockUserAssignment[optionT][r])
                    {
                        if (std::get<0>(user) == n)
                        {
                            canAssign = false;
                            break;
                        }
                    }
                }

                if (canAssign == false)
                    break;
            }

            if (canAssign == false)
                continue;

            // remove
            if (resourceBlockUserAssignment[optionT][optionR].size())
            {
                continue;
            }

            // std::cout << "can assign\n";

            double currentPower = initialPower;

            double requiredPower = 0;

            requiredPower += currentPower;

            if (resourceBlockCellAssignment[optionT][optionR] != -1)
            {
                for (auto &user : resourceBlockUserAssignment[optionT][optionR])
                {
                    double userId = std::get<0>(user);
                    double userS0 = std::get<1>(user);
                    double userP = std::get<2>(user);
                    double userD = std::get<3>(user);
                    double totalSinr = userS0 * userP * userD;

                    requiredPower += totalSinr * (1 - exp(dataStorage.input.d[optionK][n][optionR][userId])) / (userS0 * userD);
                }
            }

            // std::cout << "required power: " << requiredPower << "\n";

            // std::cout << "power left: " << powerLeftPerCell[optionT][optionK] << "\n";

            if (requiredPower <= powerLeftPerCell[optionT][optionK] && requiredPower <= powerLeftPerRBGPerCell[optionT][optionR][optionK])
            {
                powerLeftRollbacks.push_back({optionT, optionK, powerLeftPerCell[optionT][optionK]});

                powerLeftPerCell[optionT][optionK] -= requiredPower;

                powerLeftPerRBGPerCellRollbacks.push_back({optionT, optionR, optionK, powerLeftPerRBGPerCell[optionT][optionR][optionK]});

                powerLeftPerRBGPerCell[optionT][optionR][optionK] -= requiredPower;

                double interference = 1;

                for (auto &user : resourceBlockUserAssignment[optionT][optionR])
                {
                    double userId = std::get<0>(user);
                    double userS0 = std::get<1>(user);
                    double userP = std::get<2>(user);
                    double userD = std::get<3>(user);
                    double totalSinr = userS0 * userP * userD * exp(dataStorage.input.d[optionK][n][optionR][userId]);

                    rollbacks.push_back({optionK, optionR, userId, optionT, dataStorage.output.p[optionK][optionR][userId][optionT], dataStorage.output.b[optionK][optionR][userId][optionT]});

                    dataStorage.output.p[optionK][optionR][userId][optionT] += totalSinr * (1 - exp(dataStorage.input.d[optionK][n][optionR][userId])) / (userS0 * userD);

                    user = {userId, userS0, dataStorage.output.p[optionK][optionR][userId][optionT], userD * exp(dataStorage.input.d[optionK][n][optionR][userId])};

                    interference *= exp(dataStorage.input.d[optionK][userId][optionR][n]);
                }

                if (resourceBlockCellAssignment[optionT][optionR] == -1)
                {
                    resourceBlockCellAssignment[optionT][optionR] = optionK;
                    cellRollbacks.push_back({optionT, optionR});
                }

                resourceBlockUserAssignment[optionT][optionR].push_back({n, optionS0, currentPower, interference});

                RBGRollbacks.push_back({optionT, optionR});

                rollbacks.push_back({optionK, optionR, n, optionT, dataStorage.output.p[optionK][optionR][n][optionT], dataStorage.output.b[optionK][optionR][n][optionT]});

                dataStorage.output.p[optionK][optionR][n][optionT] = currentPower;
                dataStorage.output.b[optionK][optionR][n][optionT] = true;

                dataTransmissionPerFrame[j] += DataTransmissionCalculator::W * log2(1 + optionS0 * currentPower * interference);
            }

            if (dataTransmissionPerFrame[j] > dataStorage.input.TBS[j] + EPS)
            {
                break;
            }
        }

        if (dataTransmissionPerFrame[j] < dataStorage.input.TBS[j] + EPS)
        {
            for (auto rollback : rollbacks)
            {
                int k = std::get<0>(rollback);
                int r = std::get<1>(rollback);
                int userId = std::get<2>(rollback);
                int t = std::get<3>(rollback);
                double p = std::get<4>(rollback);
                bool b = std::get<5>(rollback);

                dataStorage.output.p[k][r][userId][t] = p;
                dataStorage.output.b[k][r][userId][t] = b;
            }

            for (auto rollback : cellRollbacks)
            {
                int t = std::get<0>(rollback);
                int r = std::get<1>(rollback);

                resourceBlockCellAssignment[t][r] = -1;
            }

            for (auto rollback : RBGRollbacks)
            {
                int t = std::get<0>(rollback);
                int r = std::get<1>(rollback);

                resourceBlockUserAssignment[t][r].pop_back();
            }

            for (auto rollback : powerLeftRollbacks)
            {
                int t = std::get<0>(rollback);
                int k = std::get<1>(rollback);
                double powerLeft = std::get<2>(rollback);

                powerLeftPerCell[t][k] = powerLeft;
            }

            for (auto rollback : powerLeftPerRBGPerCellRollbacks)
            {
                int t = std::get<0>(rollback);
                int r = std::get<1>(rollback);
                int k = std::get<2>(rollback);
                double powerLeft = std::get<3>(rollback);

                powerLeftPerRBGPerCell[t][r][k] = powerLeft;
            }

            dataTransmissionPerFrame[j] = 0;
        }
    }

    // std::vector<std::vector<std::vector<bool>>>
    //     resourceOcupation(dataStorage.input.T, std::vector<std::vector<bool>>(dataStorage.input.R, std::vector<bool>(dataStorage.input.K, false)));

    // std::vector<std::vector<bool>>
    //     resourceBlockOcupation(dataStorage.input.T, std::vector<bool>(dataStorage.input.R, false));

    // std::vector<std::vector<bool>>
    //     cellOcupation(dataStorage.input.T, std::vector<bool>(dataStorage.input.K, false));

    // for (auto frameId : frameIds)
    // {
    //     int j = frameId;
    //     int n = dataStorage.input.userId[j];

    //     std::vector<std::tuple<int, int, int>> options = {};

    //     std::vector<int> TTIOccupation(dataStorage.input.T, false);

    //     double g = 0;

    //     bool isSent = false;

    //     while (true)
    //     {
    //         int bestRBG = -1;
    //         int bestTTI = -1;
    //         int bestCell = -1;
    //         double maxSINR0 = -1e9;

    //         for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
    //         {
    //             if (TTIOccupation[t] == true)
    //                 continue;

    //             for (int r = 0; r < dataStorage.input.R; r++)
    //             {
    //                 if (resourceBlockOcupation[t][r] == true)
    //                     continue;

    //                 for (int k = 0; k < dataStorage.input.K; k++)
    //                 {
    //                     // if (cellOcupation[t][k] == true)
    //                     //     continue;

    //                     if (dataStorage.input.s0[k][r][n][t] > maxSINR0)
    //                     {
    //                         maxSINR0 = dataStorage.input.s0[k][r][n][t];
    //                         bestRBG = r;
    //                         bestTTI = t;
    //                         bestCell = k;
    //                     }
    //                 }
    //             }
    //         }

    //         if (bestRBG != -1)
    //         {
    //             resourceOcupation[bestTTI][bestRBG][bestCell] = true;
    //             resourceBlockOcupation[bestTTI][bestRBG] = true;
    //             cellOcupation[bestTTI][bestCell] = true;
    //             TTIOccupation[bestTTI] = true;

    //             dataStorage.output.p[bestCell][bestRBG][n][bestTTI] = 1;
    //             dataStorage.output.b[bestCell][bestRBG][n][bestTTI] = true;
    //             options.push_back({bestTTI, bestRBG, bestCell});

    //             g = DataTransmissionCalculator::computeGforFrameWithoutInterferences(dataStorage, j);

    //             if (g > dataStorage.input.TBS[j] + EPS)
    //             {
    //                 isSent = true;
    //                 break;
    //             }
    //         }
    //         else
    //         {
    //             for (auto option : options)
    //             {
    //                 int t = std::get<0>(option);
    //                 int r = std::get<1>(option);
    //                 int k = std::get<2>(option);

    //                 resourceOcupation[t][r][k] = false;
    //                 resourceBlockOcupation[t][r] = false;
    //                 cellOcupation[t][k] = false;
    //                 TTIOccupation[t] = false;

    //                 dataStorage.output.p[k][r][n][t] = 0;
    //                 dataStorage.output.b[k][r][n][t] = false;
    //             }

    //             options.clear();

    //             isSent = false;
    //             break;
    //         }
    //     }
    // }
}