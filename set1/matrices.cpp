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
        for(size_t j = 0; j < _tab[i].size(); ++j)
            temp[i][_tab[i][j] - 1] = 1;
    
    aM->create(temp);
}

void AdjMatrix::convertToIncMatrix(Matrix* iM) const
{
    size_t n = _tab.size();
    int e = 0;
    for(auto v : _tab)
        for(int x : v)
            e += x;
    e /= 2.0;
    std::vector<std::vector<int>> temp(n, std::vector<int>(e, 0));
    e = 0;
    for(size_t i = 0; i < n; ++i)
        for(size_t j = i; j < n; ++j)
            if(_tab[i][j])
            {
                temp[i][e] = temp[j][e] = 1;
                ++e;
            }
    iM->create(temp);
}

void AdjMatrix::convertToAdjList(Matrix* aL) const
{
    size_t n = _tab.size();
    std::vector<std::vector<int>> temp(n);
    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < n; ++j)
            if(_tab[i][j] == 1)
                temp[i].push_back(j + 1);
    aL->create(temp);

}

void IncMatrix::convertToAdjMatrix(Matrix* aM) const
{
    size_t size = _tab.size();
    std::vector<std::vector<int>> temp(size, std::vector<int>(size));

    int a, b;
    size_t n;
    for(size_t e = 0; e < _tab[0].size(); ++e)
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

void AdjList::plotGraph() const
{
    int r = 10;
    size_t size = _tab.size();
    double alpha = 360. / size;
    double angle;
    std::vector<double> x, y;
    double x1, y1, x2, y2;

    for(size_t i = 0; i < size; ++i)
    {
        angle = alpha * i;
        x1 = -r * cos(angle * M_PI / 180.);
        y1 = r * sin(angle * M_PI / 180.);
        x.push_back(x1);
        y.push_back(y1);
        plt::text(x1, y1, std::to_string(i + 1));

        for(auto j : _tab[i])
        {
            x2 = -r * cos(alpha * (j - 1) * M_PI / 180.);
            y2 = r * sin(alpha * (j - 1) * M_PI / 180.);
            plt::plot({x1, x2}, {y1, y2}, {{"c", "lightgrey"}, {"ls", "-"}});
        }
    }
    plt::plot(x, y, {{"c", "lightblue"}, {"marker", "D"}, {"ls", ""}});
    plt::axis("off");
    plt::show();
}

bool contains(std::vector<int> v, int x)
{
    for(int x1 : v)
        if(x == x1)
            return true;
    return false;
}

void AdjList::createG_nm(unsigned int n, unsigned int m)
{
    _tab.clear();
    srand(time(NULL));
    
    _tab = std::vector<std::vector<int>>(n);
    unsigned int i = 0, n1, n2;

    while(i < m)
    {
        n1 = rand()%n + 1;
        n2 = rand()%n + 1;
        while(n1 == n2)
            n1 = rand()%n + 1;
        if(!contains(_tab[n2 - 1], n1) && !contains(_tab[n1 - 1], n2))
        {
            _tab[n1 - 1].push_back(n2);
            _tab[n2 - 1].push_back(n1);
            ++i;
        }
    }
}

void AdjList::createG_np(unsigned int n, double p)
{
    _tab.clear();
    srand(time(NULL));
    
    _tab = std::vector<std::vector<int>>(n);
    double r;

    for(size_t n1 = 1; n1 <= n; ++n1)
        for(size_t n2 = n1 + 1; n2 <= n; ++n2)
        {
            r = (double)rand() / RAND_MAX * 1.;
            if(r <= p && !contains(_tab[n2 - 1], n1) && !contains(_tab[n1 - 1], n2))
            {
                _tab[n1 - 1].push_back(n2);
                _tab[n2 - 1].push_back(n1);
            }
        }
}
