#ifndef INPUTSTORAGE_H
#define INPUTSTORAGE_H

#include <vector>

class InputStorage
{
public:
    int N, K, T, R, J;

    std::vector<std::vector<std::vector<std::vector<double>>>> s0;
    std::vector<std::vector<std::vector<std::vector<double>>>> d;

    std::vector<double> TBS;
    std::vector<int> userId;
    std::vector<int> firstTTI;
    std::vector<int> amountTTIs;
};

#endif // INPUTSTORAGE_H

#ifndef OUTPUTSTORAGE_H
#define OUTPUTSTORAGE_H

#include <vector>

class OutputStorage
{
public:
    std::vector<std::vector<std::vector<std::vector<double>>>> p;
    std::vector<std::vector<std::vector<std::vector<bool>>>> b;
};

#endif // OUTPUTSTORAGE_H

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <vector>



class DataStorage
{
public:
    InputStorage input;
    OutputStorage output;

    std::vector<std::vector<std::vector<std::vector<double>>>> expD;
    std::vector<std::vector<int>> framesInTTI;
    std::vector<std::vector<bool>> dataUserInTTI;

    std::vector<std::vector<std::vector<double>>> dFactorPerR;
    std::vector<std::vector<double>> dFactorPerK;

    std::vector<std::vector<std::vector<double>>> dPrecal;
    std::vector<std::vector<std::vector<double>>> sPrecal;
    std::vector<std::vector<std::vector<std::vector<double>>>> s;
    std::vector<std::vector<std::vector<double>>> st;

    std::vector<double> G;

    void fitSize();
};

#endif // DATASTORAGE_H

#ifndef OUTPUTREADER_H
#define OUTPUTREADER_H

#include <iostream>



class OutputReader
{
public:
    static void read(InputStorage &inputStorage, OutputStorage &outputStorage);
};

#endif // OUTPUTREADER_H

#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <iostream>


class InputReader
{
public:
    static void read(InputStorage &inputStorage);
};

#endif // INPUTREADER_H

#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <iomanip>


class Printer
{
public:
    static void printResult(DataStorage &dataStorage);
};

#endif // PRINTER_H

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>

class Utils
{
public:
    static double geometricMean(const std::vector<double> &vect);
    static double mean(const std::vector<double> &vect);
};

#endif // UTILS_H

#ifndef PRECALCULATOR_H
#define PRECALCULATOR_H

#include <vector>




class Precalculator
{
public:
    static void precalculateUtils(DataStorage &dataStorage);

    static void precalculateFactors(DataStorage &dataStorage);
};

#endif // PRECALCULATOR_H

#ifndef VALIDATOR_H
#define VALIDATOR_H


#include <cassert>

class Validator
{
public:
    static void validateResult(DataStorage &dataStorage);
};

#endif // VALIDATOR_H

#ifndef DATATRANSMISSIONCALCULATOR_H
#define DATATRANSMISSIONCALCULATOR_H


#include <cmath>

class DataTransmissionCalculator
{
public:
    static const int W = 192;

    static void computeGfromPinT(DataStorage &dataStorage, int t);

    static double computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j);

    static double computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j, int t);
};

#endif // DATATRANSMISSIONCALCULATOR_H

#ifndef SUMMARIZER_H
#define SUMMARIZER_H

#include <iostream>




class Summarizer
{
public:
    static void summarize(DataStorage &dataStorage);
};

#endif // SUMMARIZER_H

#ifndef SCHEDULER_H
#define SCHEDULER_H






#include <vector>
#include <algorithm>

class Scheduler
{
public:
    static const int EPS = 1e-9;
    static const int numberOfIterations = 100;
    void run();
};

#endif // SCHEDULER_H






void DataStorage::fitSize()
{
    expD.resize(input.K, std::vector<std::vector<std::vector<double>>>(input.N, std::vector<std::vector<double>>(input.R, std::vector<double>(input.N))));
    framesInTTI.resize(input.T, std::vector<int>());
    dataUserInTTI.resize(input.N, std::vector<bool>(input.T));

    dFactorPerR.resize(input.K, std::vector<std::vector<double>>(input.R, std::vector<double>(input.N)));
    dFactorPerK.resize(input.K, std::vector<double>(input.N));

    dPrecal.resize(input.K, std::vector<std::vector<double>>(input.R, std::vector<double>(input.N)));
    sPrecal.resize(input.K, std::vector<std::vector<double>>(input.R, std::vector<double>(input.N)));
    s.resize(input.K, std::vector<std::vector<std::vector<double>>>(input.R, std::vector<std::vector<double>>(input.N, std::vector<double>(input.T))));
    st.resize(input.K, std::vector<std::vector<double>>(input.N, std::vector<double>(input.T)));

    G.resize(input.J);

    output.p.resize(input.K, std::vector<std::vector<std::vector<double>>>(input.R, std::vector<std::vector<double>>(input.N, std::vector<double>(input.T))));
    output.b.resize(input.K, std::vector<std::vector<std::vector<bool>>>(input.R, std::vector<std::vector<bool>>(input.N, std::vector<bool>(input.T))));
}


void OutputReader::read(InputStorage &inputStorage, OutputStorage &outputStorage)
{
    for (int t = 0; t < inputStorage.T; t++)
    {
        for (int k = 0; k < inputStorage.K; k++)
        {
            for (int r = 0; r < inputStorage.R; r++)
            {
                for (int n = 0; n < inputStorage.N; n++)
                {
                    std::cin >> outputStorage.p[k][r][n][t];

                    if (outputStorage.p[k][r][n][t] > 0)
                    {
                        outputStorage.b[k][r][n][t] = true;
                    }
                }
            }
        }
    }
}


void InputReader::read(InputStorage &inputStorage)
{
    std::cin >> inputStorage.N >> inputStorage.K >> inputStorage.T >> inputStorage.R;

    inputStorage.s0.resize(inputStorage.K, std::vector<std::vector<std::vector<double>>>(inputStorage.R, std::vector<std::vector<double>>(inputStorage.N, std::vector<double>(inputStorage.T))));
    inputStorage.d.resize(inputStorage.K, std::vector<std::vector<std::vector<double>>>(inputStorage.N, std::vector<std::vector<double>>(inputStorage.R, std::vector<double>(inputStorage.N))));

    for (int t = 0; t < inputStorage.T; t++)
        for (int k = 0; k < inputStorage.K; k++)
            for (int r = 0; r < inputStorage.R; r++)
                for (int n = 0; n < inputStorage.N; n++)
                    std::cin >> inputStorage.s0[k][r][n][t];

    for (int k = 0; k < inputStorage.K; k++)
        for (int r = 0; r < inputStorage.R; r++)
            for (int m = 0; m < inputStorage.N; m++)
                for (int n = 0; n < inputStorage.N; n++)
                    std::cin >> inputStorage.d[k][m][r][n];

    std::cin >> inputStorage.J;

    inputStorage.TBS.resize(inputStorage.J);
    inputStorage.userId.resize(inputStorage.J);
    inputStorage.firstTTI.resize(inputStorage.J);
    inputStorage.amountTTIs.resize(inputStorage.J);

    for (int j = 0; j < inputStorage.J; j++)
    {
        int id;
        std::cin >> id >> inputStorage.TBS[j] >> inputStorage.userId[j] >> inputStorage.firstTTI[j] >> inputStorage.amountTTIs[j];
    }
}


void Printer::printResult(DataStorage &dataStorage)
{
    for (int t = 0; t < dataStorage.input.T; t++)
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    std::cout << std::fixed << std::setprecision(5) << dataStorage.output.p[k][r][n][t] << " ";
                }
                std::cout << '\n';
            }
        }
    }
}



double Utils::geometricMean(const std::vector<double> &vect)
{
    double ans = 1;

    for (auto x : vect)
    {
        ans *= x;
    }

    return pow(ans, (double)1 / (double)vect.size());
}

double Utils::mean(const std::vector<double> &vect)
{
    double ans = 0;

    for (auto x : vect)
    {
        ans += x;
    }

    return ans / (double)vect.size();
}



void Precalculator::precalculateUtils(DataStorage &dataStorage)
{

    for (int k = 0; k < dataStorage.input.K; k++)
        for (int r = 0; r < dataStorage.input.R; r++)
            for (int m = 0; m < dataStorage.input.N; m++)
                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    dataStorage.expD[k][m][r][n] = exp(-dataStorage.input.d[k][m][r][n]);
                }

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
        {
            dataStorage.framesInTTI[t].push_back(j);
            dataStorage.dataUserInTTI[dataStorage.input.userId[j]][t] = true;
        }
    }
}

void Precalculator::precalculateFactors(DataStorage &dataStorage)
{
    for (int k = 0; k < dataStorage.input.K; k++)
        for (int m = 0; m < dataStorage.input.N; m++)
        {
            std::vector<double> values;
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                double up = 1;
                double down = 1;

                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    if (m != n)
                        up *= exp(-dataStorage.input.d[k][m][r][n]);
                }
                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    if (m != n)
                        for (int kt = 0; kt < dataStorage.input.K; kt++)
                        {
                            if (k != kt)
                                down += exp(dataStorage.input.d[kt][m][r][n]);
                        }
                }
                dataStorage.dFactorPerR[k][r][m] = up / down;

                values.push_back(dataStorage.dFactorPerR[k][r][m]);
            }
            dataStorage.dFactorPerK[k][m] = Utils::geometricMean(values);
        }
}


void Validator::validateResult(DataStorage &dataStorage)
{
    for (int t = 0; t < dataStorage.input.T; t++)
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            double sumOverR = 0;

            for (int r = 0; r < dataStorage.input.R; r++)
            {
                double sumOverN = 0;

                for (int n = 0; n < dataStorage.input.N; n++)
                {
                    assert(dataStorage.output.p[k][r][n][t] >= 0);

                    assert((dataStorage.output.p[k][r][n][t] == 0) ^ dataStorage.output.b[k][r][n][t]);

                    sumOverN += dataStorage.output.p[k][r][n][t];
                }

                assert(sumOverN <= 4);

                sumOverR += sumOverN;
            }

            assert(sumOverR <= dataStorage.input.R);
        }
    }
}


void DataTransmissionCalculator::computeGfromPinT(DataStorage &dataStorage, int t)
{
    for (int k = 0; k < dataStorage.input.K; k++)
    {
        for (int r = 0; r < dataStorage.input.R; r++)
        {
            for (int n = 0; n < dataStorage.input.N; n++)
            {
                if (dataStorage.dataUserInTTI[n][t])
                {
                    dataStorage.sPrecal[k][r][n] = 0;
                    dataStorage.dPrecal[k][r][n] = 0;
                    for (int m = 0; m < dataStorage.input.N; m++)
                    {
                        if (n != m)
                        {
                            dataStorage.sPrecal[k][r][n] += dataStorage.output.p[k][r][m][t] * dataStorage.expD[k][m][r][n];
                            dataStorage.dPrecal[k][r][n] += dataStorage.input.d[k][m][r][n] * dataStorage.output.b[k][r][m][t];
                        }
                    }
                    dataStorage.sPrecal[k][r][n] *= dataStorage.input.s0[k][r][n][t];
                }
            }
        }
    }

    for (int k = 0; k < dataStorage.input.K; k++)
    {
        for (int n = 0; n < dataStorage.input.N; n++)
        {
            dataStorage.st[k][n][t] = 1;
            int bt = 0;

            for (int r = 0; r < dataStorage.input.R; r++)
            {
                double up = dataStorage.input.s0[k][r][n][t] * dataStorage.output.p[k][r][n][t] * exp(dataStorage.dPrecal[k][r][n]);

                double down = 1;

                for (int kt = 0; kt < dataStorage.input.K; kt++)
                {
                    if (kt != k)
                    {
                        down += dataStorage.sPrecal[kt][r][n];
                    }
                }

                dataStorage.s[k][r][n][t] = up / down;

                if (dataStorage.output.b[k][r][n][t])
                {
                    dataStorage.st[k][n][t] *= dataStorage.s[k][r][n][t];
                    bt++;
                }
            }

            if (bt)
            {
                dataStorage.st[k][n][t] = pow(dataStorage.st[k][n][t], (double)1 / (double)bt);
            }
            else
            {
                dataStorage.st[k][n][t] = 0;
            }
        }
    }

    for (auto j : dataStorage.framesInTTI[t])
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                dataStorage.G[j] += (int)dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] * log2(1 + dataStorage.st[k][dataStorage.input.userId[j]][t]) * W;
            }
        }
    }
}

double DataTransmissionCalculator::computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j)
{
    double g = 0;

    for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
    {
        for (int k = 0; k < dataStorage.input.K; k++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                g += (int)dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] * log2(1 + dataStorage.input.s0[k][r][dataStorage.input.userId[j]][t] * dataStorage.output.p[k][r][dataStorage.input.userId[j]][t]);
            }
        }
    }

    g *= W;

    return g;
}

double DataTransmissionCalculator::computeGforFrameWithoutInterferences(DataStorage &dataStorage, int j, int t)
{
    double g = 0;

    for (int k = 0; k < dataStorage.input.K; k++)
    {
        for (int r = 0; r < dataStorage.input.R; r++)
        {
            g += (int)dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] * log2(1 + dataStorage.input.s0[k][r][dataStorage.input.userId[j]][t] * dataStorage.output.p[k][r][dataStorage.input.userId[j]][t]);
        }
    }

    g *= W;

    return g;
}


void Summarizer::summarize(DataStorage &dataStorage)
{
    const std::string redColor = "\033[31m";
    const std::string yellowColor = "\033[33m";
    const std::string greenColor = "\033[32m";
    const std::string resetColor = "\033[0m";

    Precalculator::precalculateUtils(dataStorage);

    for (int t = 0; t < dataStorage.input.T; t++)
    {
        DataTransmissionCalculator::computeGfromPinT(dataStorage, t);
    }

    int totalDelivered = 0;

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        if (dataStorage.G[j] >= dataStorage.input.TBS[j])
        {
            totalDelivered++;
        }
    }

    if ((double)totalDelivered / (double)dataStorage.input.J > 0.8)
    {
        std::cout << greenColor << "Total delivered: " << totalDelivered << " / " << dataStorage.input.J << resetColor << '\n';
    }
    else if ((double)totalDelivered / (double)dataStorage.input.J > 0.5)
    {
        std::cout << yellowColor << "Total delivered: " << totalDelivered << " / " << dataStorage.input.J << resetColor << '\n';
    }
    else
    {
        std::cout << redColor << "Total delivered: " << totalDelivered << " / " << dataStorage.input.J << resetColor << '\n';
    }
}


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

    for (int it = 0; it < numberOfIterations; it++)
    {
        sort(frames.begin(), frames.end());

        std::vector<std::vector<std::pair<int, int>>> resourceBlockOcupation(dataStorage.input.T, std::vector<std::pair<int, int>>(dataStorage.input.R, {-1, -1}));

        std::vector<int> resourceBlockOcupationPerFrame(dataStorage.input.J, 0);

        std::vector<std::vector<std::tuple<int, int, int>>> ocuppiedCellsPerFrame(dataStorage.input.J);

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

                    resourceBlockOcupationPerFrame[j]++;

                    g += DataTransmissionCalculator::computeGforFrameWithoutInterferences(dataStorage, j, t);

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

                    resourceBlockOcupationPerFrame[j]--;
                }

                ocuppiedCells.clear();
            }

            ocuppiedCellsPerFrame[j] = ocuppiedCells;
        }

        if (it == numberOfIterations - 1)
            break;

        frames.clear();

        for (int j = 0; j < dataStorage.input.J; j++)
        {
            frames.push_back({resourceBlockOcupationPerFrame[j], dataStorage.input.TBS[j], j});
        }

        for (int j = 0; j < dataStorage.input.J; j++)
        {
            for (auto cell : ocuppiedCellsPerFrame[j])
            {
                int t = std::get<0>(cell);
                int r = std::get<1>(cell);
                int k = std::get<2>(cell);

                resourceBlockOcupation[t][r] = {-1, -1};
                dataStorage.output.p[k][r][dataStorage.input.userId[j]][t] = 0;
                dataStorage.output.b[k][r][dataStorage.input.userId[j]][t] = false;

                resourceBlockOcupationPerFrame[j]--;
            }
        }
    }

    Printer::printResult(dataStorage);
}

#pragma GCC optimize("O3", "Ofast", "no-stack-protector", "unroll-loops", "omit-frame-pointer", "inline")

#include <bits/stdc++.h>


int main(int argc, char *argv[])
{
    if (argc >= 2)
        freopen(argv[1], "r", stdin);

    if (argc >= 3)
        freopen(argv[2], "w", stdout);

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    Scheduler scheduler;

    scheduler.run();

    return 0;
}