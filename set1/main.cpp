#include <iostream>
#include <fstream>
#include "newTab.h"

int main()
{

    std::string filename;
    std::string text;
    NewTab* tab = new NewTab;
    AdjList* aL = new AdjList;
    AdjMatrix* aM = new AdjMatrix;
    IncMatrix* iM = new IncMatrix;

    std::cout << "select the input file: ";
    std::cin >> filename;
    std::ifstream file(filename);

    while(getline(file, text))
        tab->addRow(text);

    file.close();

    tab->readTab();

    tab->fill(aL, aM, iM);

    delete tab;
    delete aL;
    delete aM;
    delete iM;

    return 0;
}