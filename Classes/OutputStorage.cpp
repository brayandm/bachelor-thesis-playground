#include "OutputStorage.h"

void OutputStorage::clean()
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