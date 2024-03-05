#ifndef OUTPUTSTORAGE_H
#define OUTPUTSTORAGE_H

#include <vector>

class OutputStorage
{
public:
    std::vector<std::vector<std::vector<std::vector<double>>>> p;
    std::vector<std::vector<std::vector<std::vector<bool>>>> b;

    void clear();
};

#endif // OUTPUTSTORAGE_H

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
    void clear();
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

#ifndef SOLUTIONSTORE_H
#define SOLUTIONSTORE_H



class SolutionStore
{
public:
    int dataFrameTransmitted;
    OutputStorage output;
};

#endif // SOLUTIONSTORE_H

#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <iostream>


class InputReader
{
public:
    static void read(InputStorage &inputStorage);
};

#endif // INPUTREADER_H

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

#ifndef DELIVERYCALCULATOR_H
#define DELIVERYCALCULATOR_H





class DeliveryCalculator
{
public:
    DeliveryCalculator(DataStorage &dataStorage);
    int calculateDelivery(DataStorage &dataStorage);
};

#endif // DELIVERYCALCULATOR_H

#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include <iomanip>


class Printer
{
public:
    static void printResult(DataStorage &dataStorage);
    static void printResult(OutputStorage &OutputStorage);
};

#endif // PRINTER_H

#ifndef VALIDATOR_H
#define VALIDATOR_H


#include <cassert>

class Validator
{
public:
    static void validateResult(DataStorage &dataStorage);
};

#endif // VALIDATOR_H

#ifndef SOLUTIONMANAGER_H
#define SOLUTIONMANAGER_H



#include <vector>
#include <cassert>

class SolutionManager
{
public:
    std::vector<SolutionStore> solutions;

    void addSolution(OutputStorage output, int dataFrameTransmitted);
    void clear();
    SolutionStore getBestSolution();
};

#endif // SOLUTIONMANAGER_H

#ifndef FRAMESORTER_H
#define FRAMESORTER_H


#include <vector>
#include <algorithm>
#include <tuple>

class FrameSorter
{
public:
    static constexpr double oo = 1e9;
    static std::vector<int> getFramesSortByTBS(DataStorage &dataStorage);
    static std::vector<int> getFramesSortByTTI(DataStorage &dataStorage);
    static std::vector<int> getFramesSortByTTIAndTBS(DataStorage &dataStorage);
    static std::vector<int> getFramesSortByRBGConsumed(DataStorage &dataStorage);
    static std::vector<int> getFramesSortRandom(DataStorage &dataStorage);
};

#endif // FRAMESORTER_H

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
    static const int numberOfIterations = 1;
    static constexpr double initialPower = 1.0;
    void run();
    void step(DataStorage &dataStorage, std::vector<int> frameIds);
};

#endif // SCHEDULER_H

#ifndef SIMPLEGREEDY_H
#define SIMPLEGREEDY_H










#include <vector>
#include <algorithm>

class SimpleGreedy
{
public:
    static constexpr double EPS = 1e-9;
    static const int numberOfIterations = 1;
    static constexpr double initialPower = 1.0;
    void run();
    void step(DataStorage &dataStorage, std::vector<int> frameIds);
};

#endif // SIMPLEGREEDY_H




void OutputStorage::clear()
{
    for (int k = 0; k < p.size(); k++)
    {
        for (int r = 0; r < p[k].size(); r++)
        {
            for (int n = 0; n < p[k][r].size(); n++)
            {
                for (int t = 0; t < p[k][r][n].size(); t++)
                {
                    p[k][r][n][t] = 0;
                }
            }
        }
    }

    for (int k = 0; k < b.size(); k++)
    {
        for (int r = 0; r < b[k].size(); r++)
        {
            for (int n = 0; n < b[k][r].size(); n++)
            {
                for (int t = 0; t < b[k][r][n].size(); t++)
                {
                    b[k][r][n][t] = false;
                }
            }
        }
    }
}



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

void DataStorage::clear()
{
    output.clear();

    for (int j = 0; j < G.size(); j++)
    {
        G[j] = 0;
    }
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


DeliveryCalculator::DeliveryCalculator(DataStorage &dataStorage)
{
    Precalculator::precalculateUtils(dataStorage);
}

int DeliveryCalculator::calculateDelivery(DataStorage &dataStorage)
{
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

    return totalDelivered;
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

void Printer::printResult(OutputStorage &outputStorage)
{
    int K = outputStorage.p.size();
    int R = outputStorage.p[0].size();
    int N = outputStorage.p[0][0].size();
    int T = outputStorage.p[0][0][0].size();

    for (int t = 0; t < T; t++)
    {
        for (int k = 0; k < K; k++)
        {
            for (int r = 0; r < R; r++)
            {
                for (int n = 0; n < N; n++)
                {
                    std::cout << std::fixed << std::setprecision(5) << outputStorage.p[k][r][n][t] << " ";
                }
                std::cout << '\n';
            }
        }
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


void SolutionManager::addSolution(OutputStorage output, int dataFrameTransmitted)
{
    SolutionStore solution;
    solution.output = output;
    solution.dataFrameTransmitted = dataFrameTransmitted;
    solutions.push_back(solution);
}

void SolutionManager::clear()
{
    solutions.clear();
}

SolutionStore SolutionManager::getBestSolution()
{
    assert(solutions.size() > 0);

    SolutionStore bestSolution = solutions[0];

    for (int i = 1; i < solutions.size(); i++)
    {
        if (solutions[i].dataFrameTransmitted > bestSolution.dataFrameTransmitted)
        {
            bestSolution = solutions[i];
        }
    }
    return bestSolution;
}


std::vector<int> FrameSorter::getFramesSortByTBS(DataStorage &dataStorage)
{
    std::vector<std::tuple<double, int>> frames;

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        frames.push_back({dataStorage.input.TBS[j], j});
    }

    sort(frames.begin(), frames.end());

    std::vector<int> frameIds;

    for (auto &t : frames)
    {
        frameIds.push_back(std::get<1>(t));
    }

    return frameIds;
}

std::vector<int> FrameSorter::getFramesSortByTTI(DataStorage &dataStorage)
{
    std::vector<std::tuple<int, int>> frames;

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        frames.push_back({dataStorage.input.amountTTIs[j], j});
    }

    sort(frames.begin(), frames.end());

    std::vector<int> frameIds;

    for (auto &t : frames)
    {
        frameIds.push_back(std::get<1>(t));
    }

    return frameIds;
}

std::vector<int> FrameSorter::getFramesSortByTTIAndTBS(DataStorage &dataStorage)
{
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

    return frameIds;
}

std::vector<int> FrameSorter::getFramesSortByRBGConsumed(DataStorage &dataStorage)
{
    std::vector<std::tuple<int, int>> frames;

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        int n = dataStorage.input.userId[j];

        int rbgConsumed = 0;

        for (int t = dataStorage.input.firstTTI[j]; t < dataStorage.input.firstTTI[j] + dataStorage.input.amountTTIs[j]; t++)
        {
            for (int r = 0; r < dataStorage.input.R; r++)
            {
                bool isConsumed = false;

                for (int k = 0; k < dataStorage.input.K; k++)
                {
                    if (dataStorage.output.b[k][r][n][t] == true)
                    {
                        isConsumed = true;
                        break;
                    }
                }

                if (isConsumed)
                    rbgConsumed++;
            }
        }

        if (rbgConsumed == 0)
            rbgConsumed = 1e9;

        frames.push_back({rbgConsumed, j});
    }

    sort(frames.begin(), frames.end());

    std::vector<int> frameIds;

    for (auto &t : frames)
    {
        frameIds.push_back(std::get<1>(t));
    }

    return frameIds;
}

std::vector<int> FrameSorter::getFramesSortRandom(DataStorage &dataStorage)
{
    std::vector<int> frameIds(dataStorage.input.J);

    for (int j = 0; j < dataStorage.input.J; j++)
    {
        frameIds[j] = j;
    }

    std::random_shuffle(frameIds.begin(), frameIds.end());

    return frameIds;
}


void Summarizer::summarize(DataStorage &dataStorage)
{
    const std::string redColor = "\033[31m";
    const std::string yellowColor = "\033[33m";
    const std::string greenColor = "\033[32m";
    const std::string resetColor = "\033[0m";

    DeliveryCalculator deliveryCalculator(dataStorage);

    int totalDelivered = deliveryCalculator.calculateDelivery(dataStorage);

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
        std::vector<std::tuple<int, int, int, std::tuple<int, double, double, double>>> userRollbacks;

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
            // if (resourceBlockUserAssignment[optionT][optionR].size())
            // {
            //     continue;
            // }

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

                int id = 0;

                for (auto &user : resourceBlockUserAssignment[optionT][optionR])
                {
                    double userId = std::get<0>(user);
                    double userS0 = std::get<1>(user);
                    double userP = std::get<2>(user);
                    double userD = std::get<3>(user);
                    double totalSinr = userS0 * userP * userD * exp(dataStorage.input.d[optionK][n][optionR][userId]);

                    rollbacks.push_back({optionK, optionR, userId, optionT, dataStorage.output.p[optionK][optionR][userId][optionT], dataStorage.output.b[optionK][optionR][userId][optionT]});

                    dataStorage.output.p[optionK][optionR][userId][optionT] += totalSinr * (1 - exp(dataStorage.input.d[optionK][n][optionR][userId])) / (userS0 * userD);

                    userRollbacks.push_back({optionT,
                                             optionR,
                                             id,
                                             user});

                    user = {userId, userS0, dataStorage.output.p[optionK][optionR][userId][optionT], userD * exp(dataStorage.input.d[optionK][n][optionR][userId])};

                    interference *= exp(dataStorage.input.d[optionK][userId][optionR][n]);

                    id++;
                }

                if (resourceBlockCellAssignment[optionT][optionR] == -1)
                {
                    resourceBlockCellAssignment[optionT][optionR] = optionK;
                    cellRollbacks.push_back({optionT, optionR});
                }

                RBGRollbacks.push_back({optionT, optionR});

                resourceBlockUserAssignment[optionT][optionR].push_back({n, optionS0, currentPower, interference});

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

            for (auto rollback : userRollbacks)
            {
                int t = std::get<0>(rollback);
                int r = std::get<1>(rollback);
                int id = std::get<2>(rollback);
                std::tuple<int, double, double, double> user = std::get<3>(rollback);

                resourceBlockUserAssignment[t][r][id] = user;
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


void SimpleGreedy::run()
{
    DataStorage dataStorage;
    InputReader::read(dataStorage.input);
    dataStorage.fitSize();

    SolutionManager solutionManager;

    DeliveryCalculator deliveryCalculator(dataStorage);

    SimpleGreedy::step(dataStorage, FrameSorter::getFramesSortByTTIAndTBS(dataStorage));
    solutionManager.addSolution(dataStorage.output, deliveryCalculator.calculateDelivery(dataStorage));

    for (int iteration = 0; iteration < numberOfIterations; iteration++)
    {
        std::vector<int> frameIds = FrameSorter::getFramesSortByRBGConsumed(dataStorage);

        dataStorage.clear();

        SimpleGreedy::step(dataStorage, frameIds);
        solutionManager.addSolution(dataStorage.output, deliveryCalculator.calculateDelivery(dataStorage));
    }

    SolutionStore bestSolution = solutionManager.getBestSolution();

    Printer::printResult(bestSolution.output);
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

    SimpleGreedy scheduler;

    scheduler.run();

    return 0;
}