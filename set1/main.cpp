#include <iostream>
#include <fstream>
#include "newTab.h"

int main()
{
    //task1

    std::string filename;
    std::string text;
    NewTab* tab = new NewTab;
    AdjList* aL = new AdjList;
    AdjMatrix* aM = new AdjMatrix;
    IncMatrix* iM = new IncMatrix;

    std::cout << "type in the input file: ";
    std::cin >> filename;
    std::ifstream file(filename);

    while(getline(file, text))
        tab->addRow(text);

    file.close();

    tab->readTab();

    tab->fill(aL, aM, iM);

    delete tab;
    delete aM;
    delete iM;

    //task2

    aL->plotGraph();

    delete aL;

    //task3

    unsigned int n, m;
    std::cout << "type in the number of nodes and edges to create a random graph: ";
    do std::cin >> n >> m;
    while(n < 0 || m < 0 || m > n * (n - 1) / 2);

    AdjList* G_nm = new AdjList;

    G_nm->createG_nm(n, m);
    G_nm->plotGraph();

    delete G_nm;

    double p;
    std::cout << "type in the number of nodes and the probability of creating an edge: ";
    do std::cin >> n >> p;
    while(n < 0 || p < 0. || p > 1.);

    AdjList* G_np = new AdjList;

    G_np->createG_np(n, p);
    G_np->plotGraph();

    delete G_np;

    return 0;
}