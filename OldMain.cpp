#pragma GCC optimize("O3", "Ofast", "no-stack-protector", "unroll-loops", "omit-frame-pointer", "inline") // Optimization flags
// #pragma GCC option("arch=native", "tune=native", "no-zero-upper")                                         // Enable AVX
// #pragma GCC target("avx2")                                                                                // Enable AVX

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#define debugMode true
#include "/home/brayand/debugger.h"
#else
#define debugMode false
#define db(...) false
#define dbl(...) false
#define dbg(...) false
#define dbm(...) false
#define dbs(...) false
#define dbas(...) false
#endif

typedef long long ll;
mt19937_64 _rng(0);

ll rng(ll a, ll b)
{
    return uniform_int_distribution<ll>(a, b)(_rng);
}

typedef double ld;

const ld EPS = 1e-12;

const ld DATAEPS = 1e-3;

const int MAXK = 10;
const int MAXR = 10;
const int MAXN = 100;
const int MAXT = 1000;
const int MAXJ = 5000;
const int MAXS = 10000;
const int W = 192;

int N, K, T, R;

int J;

ld s0[MAXK][MAXR][MAXN][MAXT];
ld d[MAXK][MAXN][MAXR][MAXN];
ld expD[MAXK][MAXN][MAXR][MAXN];

ld p[MAXK][MAXR][MAXN][MAXT];
bool b[MAXK][MAXR][MAXN][MAXT];

ld dPrecal[MAXK][MAXR][MAXN];
ld sPrecal[MAXK][MAXR][MAXN];
ld s[MAXK][MAXR][MAXN][MAXT];
ld st[MAXK][MAXN][MAXT];

ld dFactorPerR[MAXK][MAXR][MAXN];
ld dFactorPerK[MAXK][MAXN];

ld TBS[MAXJ];
ld G[MAXJ];
int userId[MAXJ];
int firstTTI[MAXJ];
int amountTTIs[MAXJ];

vector<int> framesInTTI[MAXT];

bool dataUserInTTI[MAXN][MAXT];

void read()
{
    cin >> N >> K >> T >> R;

    for (int t = 0; t < T; t++)
        for (int k = 0; k < K; k++)
            for (int r = 0; r < R; r++)
                for (int n = 0; n < N; n++)
                    cin >> s0[k][r][n][t];

    for (int k = 0; k < K; k++)
        for (int r = 0; r < R; r++)
            for (int m = 0; m < N; m++)
                for (int n = 0; n < N; n++)
                {
                    cin >> d[k][m][r][n];
                    expD[k][m][r][n] = exp(-d[k][m][r][n]);
                }

    cin >> J;

    for (int j = 0; j < J; j++)
    {
        int id;
        cin >> id >> TBS[j] >> userId[j] >> firstTTI[j] >> amountTTIs[j];

        for (int t = firstTTI[j]; t < firstTTI[j] + amountTTIs[j]; t++)
        {
            framesInTTI[t].push_back(id);
            dataUserInTTI[userId[j]][t] = true;
        }
    }
}

void write()
{
    for (int t = 0; t < T; t++)
    {
        for (int k = 0; k < K; k++)
        {
            for (int r = 0; r < R; r++)
            {
                for (int n = 0; n < N; n++)
                {
                    cout << p[k][r][n][t] << " ";
                }
                cout << '\n';
            }
        }
    }
}

ld geometricMean(vector<ld> vect)
{
    ld ans = 1;

    for (auto x : vect)
    {
        ans *= x;
    }

    return pow(ans, (ld)1 / (ld)vect.size());
}

ld mean(vector<ld> vect)
{
    ld ans = 0;

    for (auto x : vect)
    {
        ans += x;
    }

    return ans / (ld)vect.size();
}

void precal()
{
    for (int k = 0; k < K; k++)
        for (int m = 0; m < N; m++)
        {
            vector<ld> values;
            for (int r = 0; r < R; r++)
            {
                ld up = 1;
                ld down = 1;

                for (int n = 0; n < N; n++)
                {
                    if (m != n)
                        up *= exp(-d[k][m][r][n]);
                }
                for (int n = 0; n < N; n++)
                {
                    if (m != n)
                        for (int kt = 0; kt < K; kt++)
                        {
                            if (k != kt)
                                down += exp(d[kt][m][r][n]);
                        }
                }
                dFactorPerR[k][r][m] = up / down;

                values.push_back(dFactorPerR[k][r][m]);
            }
            dFactorPerK[k][m] = geometricMean(values);
        }
}

ld joinInterference(int t, int k, int r, vector<int> vect)
{
    vector<ld> values;

    for (auto m : vect)
    {
        ld up = 1;
        ld down = 1;

        for (auto n : vect)
        {
            if (m != n)
                up *= exp(-d[k][m][r][n]);
        }
        for (auto n : vect)
        {
            if (m != n)
                for (int kt = 0; kt < K; kt++)
                {
                    if (k != kt)
                        down += exp(d[kt][m][r][n]);
                }
        }

        values.push_back(up / down);
    }

    return geometricMean(values);
}

void computeGfromPinT(int t)
{
    for (int k = 0; k < K; k++)
    {
        for (int r = 0; r < R; r++)
        {
            for (int n = 0; n < N; n++)
            {
                if (dataUserInTTI[n][t])
                {
                    sPrecal[k][r][n] = 0;
                    dPrecal[k][r][n] = 0;
                    for (int m = 0; m < N; m++)
                    {
                        if (n != m)
                        {
                            sPrecal[k][r][n] += p[k][r][m][t] * expD[k][m][r][n];
                            dPrecal[k][r][n] += d[k][m][r][n] * b[k][r][m][t];
                        }
                    }
                    sPrecal[k][r][n] *= s0[k][r][n][t];
                }
            }
        }
    }

    for (int k = 0; k < K; k++)
    {
        for (int n = 0; n < N; n++)
        {
            st[k][n][t] = 1;
            int bt = 0;

            for (int r = 0; r < R; r++)
            {
                ld up = s0[k][r][n][t] * p[k][r][n][t] * exp(dPrecal[k][r][n]);

                ld down = 1;

                for (int kt = 0; kt < K; kt++)
                {
                    if (kt != k)
                    {
                        down += sPrecal[kt][r][n];
                    }
                }

                s[k][r][n][t] = up / down;

                if (b[k][r][n][t])
                {
                    st[k][n][t] *= s[k][r][n][t];
                    bt++;
                }
            }

            if (bt)
            {
                st[k][n][t] = pow(st[k][n][t], (ld)1 / (ld)bt);
            }
            else
            {
                st[k][n][t] = 0;
            }
        }
    }

    for (auto j : framesInTTI[t])
    {
        for (int k = 0; k < K; k++)
        {
            for (int r = 0; r < R; r++)
            {
                G[j] += (int)b[k][r][userId[j]][t] * log2(1 + st[k][userId[j]][t]) * W;
            }
        }
    }
}

void normalize(vector<ld> &vect)
{
    vector<ld> values;
    ld sumValues = 0;

    for (int n = 0; n < vect.size(); n++)
    {
        ld val = vect[n];
        values.push_back(val);
        sumValues += val;
    }

    for (int n = 0; n < vect.size(); n++)
    {
        vect[n] = values[n] / (sumValues + EPS);
    }
}

void analize()
{
    int ans = 0;

    for (int j = 0; j < J; j++)
    {
        if (G[j] >= TBS[j])
            ans++;
    }

    db(J);
    db(ans);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (debugMode)
        freopen("A.in", "r", stdin);
    // freopen("A.out", "w", stdout);

    cout << setprecision(9) << fixed << '\n';

    read();

    precal();

    for (int t = 0; t < T; t++)
    {
        vector<ld> userData(N);
        for (auto j : framesInTTI[t])
        {
            ld value = max(TBS[j] + DATAEPS - G[j], (ld)0) / pow(firstTTI[j] + amountTTIs[j] - t, 2);
            userData[userId[j]] += value;
        }

        normalize(userData);

        for (int k = 0; k < K; k++)
        {
            vector<pair<ld, int>> vect;

            for (int n = 0; n < N; n++)
            {
                ld value = userData[n];
                if (value > 0)
                {
                    vect.push_back({value, n});
                }
            }

            sort(vect.begin(), vect.end());
            // shuffle(vect.begin(), vect.end(), _rng);

            vector<bool> mk(R);

            // db(vect);
            for (auto x : vect)
            {
                ld value = x.first;
                int n = x.second;

                ld may = -1;
                int rt = -1;

                for (int r = 0; r < R; r++)
                {
                    if (!mk[r])
                    {
                        rt = r;
                    }
                }

                if (rt == -1)
                    continue;

                mk[rt] = true;

                b[k][rt][n][t] = true;
                p[k][rt][n][t] = 1;
            }
        }

        computeGfromPinT(t);
        // dbm(G, 0, J - 1);
    }

    if (debugMode)
        analize();
    else
        write();
    // write();;;

    return 0;
}