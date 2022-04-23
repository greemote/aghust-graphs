#include "matrices.h"

void AdjList::convertToAdjMatrix(Matrix* aM) const
{
    std::vector<std::vector<int>> temp;
    int n = _tab.size();
    std::vector<int> v;
    for(int i = 0; i < n; ++i)
        v.push_back(0);
    for(int i = 0; i < n; ++i)
        temp.push_back(v);
    for(int i = 0; i < n; ++i)
        for(unsigned int j = 0; j < _tab[i].size(); ++j)
            temp[i][_tab[i][j] - 1] = 1;
    
    aM->create(temp);
}

void AdjMatrix::convertToIncMatrix(Matrix* iM) const
{
    unsigned int n = _tab.size();
    int e = 0;
    for(auto v : _tab)
        for(int x : v)
            e += x;
    e /= 2.0;
    std::vector<std::vector<int>> temp(n, std::vector<int>(e, 0));
    e = 0;
    for(unsigned int i = 0; i < n; ++i)
        for(unsigned int j = i + 1; j <= n; ++j)
            if(_tab[i][j])
            {
                temp[i][e] = temp[j][e] = 1;
                ++e;
            }
    iM->create(temp);
}

void AdjMatrix::convertToAdjList(Matrix* aL) const
{
    unsigned int n = _tab.size();
    std::vector<std::vector<int>> temp(n);
    for(unsigned int i = 0; i < n; ++i)
        for(unsigned int j = 0; j < n; ++j)
            if(_tab[i][j] == 1)
                temp[i].push_back(j + 1);
    aL->create(temp);

}

void IncMatrix::convertToAdjMatrix(Matrix* aM) const
{
    unsigned int size = _tab.size();
    std::vector<std::vector<int>> temp(size, std::vector<int>(size));

    int a, b;
    unsigned int n;
    for(unsigned int e = 0; e < _tab[0].size(); ++e)
    {
        a = -1;
        b = -1;
        n = 0;
        for(; n < _tab.size() && a == -1; ++n)
            if(_tab[n][e])
                a = n;
        for(; n < _tab.size() && b == -1; ++n)
            if(_tab[n][e])
                b = n;
        if(b == -1)
            b = a;
        temp[a][b] = temp[b][a] = 1;
    }
    aM->create(temp);
}