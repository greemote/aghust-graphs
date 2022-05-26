#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <float.h>
#include "adjList.h"

void printResult(double* result, char* rank, int size)
{
    double temp1;
    char temp2;
    for(int i = 0; i < size; ++i)
	{		
		for(int j = i + 1; j < size; ++j)
		{
			if(result[i] < result[j])
			{
				temp1 = result[i];
				result[i] = result[j];
				result[j] = temp1;

                temp2 = rank[i];
				rank[i] = rank[j];
				rank[j] = temp2;
			}
		}
	}

    for(int i = 0; i < size; ++i)
        std::cout << rank[i] << " ==> PageRank = " << result[i] << std::endl;
}

void pageRank1(AdjList* graph, double d, int n, int node = 0)
{
    int size = graph->getSize();
    double result[size] = {0.};
    char rank[size];

    for(int i = 0; i < size; ++i)
        rank[i] = i + 65;

    double r;
    for(int i = 0; i < n; ++i)
    {
        r = (double)rand() / RAND_MAX;
        if(r <= d)
            node = rand()%size;
        else
        {
            r = rand()%(graph->getNodes(node).size());
            node = graph->getNodes(node)[r];
        }
        ++result[node];
    }

    for(auto& x : result)
    {
        x /= n;
    }

    printResult(result, rank, size);
}

void pageRank2(AdjList* graph, double d)
{
    int size = graph->getSize();
    std::vector<std::vector<int>> A {};
    std::vector<std::vector<double>> P(size, std::vector<double>(size, 0.));
    double p0[size], p1[size], diff[size];
    char rank[size];
    double err = DBL_MAX;
    for(int i = 0; i < size; ++i)
    {
        p0[i] = 1. / size;
        p1[i] = 0.;
        rank[i] = i + 65;
    }   

    graph->convertToAdjMatrix(A);

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            P[i][j] = (1. - d) * A[i][j] / graph->getNodes(i).size() + d / size;

    int iter = 0;
    while(err > 1e-8)
    {
        for(int i = 0; i < size; ++i)
        {
            p1[i] = 0.;
            for(int j = 0; j < size; ++j)
                p1[i] += P[j][i] * p0[j];
        }

        err = 0.;
        for(int i = 0; i < size; ++i)
        {
            diff[i] = p1[i] - p0[i];
            err += fabs(diff[i]);

            p0[i] = p1[i];
        }
        ++iter;
    }

    printResult(p0, rank, size);
    std::cout << "iterations: " << iter << std::endl;
}

int main()
{
    AdjList* graph = new AdjList("input.txt");

    srand(time(NULL));

    pageRank1(graph, 0.15, 1000000);
    std::cout << std::endl;
    pageRank2(graph, 0.15);

    delete graph;
}