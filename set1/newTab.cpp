#include "newTab.h"

void NewTab::addRow(std::string text)
{
    std::vector<int> newRow;
    char* str = const_cast<char*>(text.c_str());
    char* token = strtok(str, " ");
    while(token != NULL)
    {
        newRow.push_back(atoi(token));
        token = strtok(NULL, " ");
    }
    _tab.push_back(newRow);
}

bool NewTab::checkIf01() const
{
    for(auto v : _tab)
        for(int x : v)
            if(x != 0 && x != 1)
                return false;
    return true;
}

bool NewTab::checkIfAdjMatrix() const
{
    unsigned int rows = _tab.size();
    for(auto v : _tab)
        if(v.size() != rows)
            return false;
    for(unsigned int i =  0; i < rows; ++i)
        if(_tab[i][i] != 0)
            return false;
    return true;
}
bool NewTab::checkIfIncMatrix() const
{
    int n = _tab.size();
    int e = _tab[0].size();
    if(e > n * (n - 1) / 2.0)
        return false;
    int sum = 0;
    for(auto v : _tab)
        for(int x : v)
            sum += x;
    if(sum != 2 * e)
        return false;
    return true;
}
bool NewTab::checkIfAdjList() const
{
    NewTab* temp = new NewTab;
    unsigned int n = _tab.size();
    std::vector<int> v;
    for(unsigned int i = 0; i < n; ++i)
        v.push_back(0);
    for(unsigned int i = 0; i < n; ++i)
        temp->_tab.push_back(v);
    for(unsigned int i = 0; i < n; ++i)
        for(unsigned int j = 0; j < _tab[i].size(); ++j)
            temp->_tab[i][_tab[i][j] - 1] = 1;
    return temp->checkIfAdjMatrix();
}

void NewTab::fill(AdjList* aL, AdjMatrix* aM, IncMatrix* iM) const
{
    if(_tab.size() != 0)
    {
        if(checkIf01())
        {
            if(checkIfAdjMatrix())
            {
                std::cout << "the input is an adjacency matrix" << std::endl;
                aM->create(_tab);
                aM->convertToIncMatrix(iM);
                std::cout << "converted incidence matrix: " << std::endl;
                iM->read();
                aM->convertToAdjList(aL);
                std::cout << "converted adjacency list: " << std::endl;
                aL->read();
            }
            else if(checkIfIncMatrix())
            {
                std::cout << "the input is an incidence matrix" << std::endl;
                iM->create(_tab);
                iM->convertToAdjMatrix(aM);
                std::cout << "converted adjacency matrix: " << std::endl;
                aM->read();
                aM->convertToAdjList(aL);
                std::cout << "converted adjacency list: " << std::endl;
                aL->read();
            }
            else
                std::cout << "the program couldn't detect any graph matrix nor list" << std::endl;
        }
        else if(checkIfAdjList())
        {
            std::cout << "the input is an adjacency list" << std::endl;
            aL->create(_tab);
            aL->convertToAdjMatrix(aM);
            std::cout << "converted adjacency matrix: " << std::endl;
            aM->read();
            aM->convertToIncMatrix(iM);
            std::cout << "converted incidence matrix: " << std::endl;
            iM->read();
        }
        else
            std::cout << "the program couldn't detect any graph matrix nor list" << std::endl;
    }
    else
        std::cout << "wrong input file" << std::endl;
}