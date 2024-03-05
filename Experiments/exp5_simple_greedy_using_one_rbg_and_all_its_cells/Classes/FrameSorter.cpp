#include "FrameSorter.h"

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