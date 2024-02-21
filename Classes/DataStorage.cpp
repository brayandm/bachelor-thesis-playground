#include "DataStorage.h"

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