#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <string.h>
#include <math.h>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

class Matrix
{
protected:

    std::vector<std::vector<int>> _tab;

public:

    inline void create(std::vector<std::vector<int>> tab)
    {
        _tab = tab;
    }

    inline void read()
    {
        for(auto v : _tab)
        {
            for(int x : v)
                std::cout << x << " ";
            std::cout << std::endl;
        }
    }
};

class AdjList : public Matrix
{
public:

    void convertToAdjMatrix(Matrix*) const;

    void plotGraph() const;

    void createG_nm(unsigned int, unsigned int);
    void createG_np(unsigned int, double);
};

class AdjMatrix : public Matrix
{
public:

    void convertToIncMatrix(Matrix*) const;
    void convertToAdjList(Matrix*) const;
};

class IncMatrix : public Matrix
{
public:

    void convertToAdjMatrix(Matrix*) const;
};