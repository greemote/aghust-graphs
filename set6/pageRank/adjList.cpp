#include "adjList.h"

AdjList::AdjList(std::string filename)
{
    std::string text;
    std::ifstream file(filename);
    while(getline(file, text))
        addRow(text);
    file.close();
}

void AdjList::addRow(std::string text)
{
    std::vector<int> newRow;
    char* str = const_cast<char*>(text.c_str());
    char* token = strtok(str, " ");
    while(token != NULL)
    {
        newRow.push_back(*token - 65);
        token = strtok(NULL, " ");
    }
    _tab.push_back(newRow);
}

void AdjList::convertToAdjMatrix(std::vector<std::vector<int>>& adjMatrix) const
{
    int n = _tab.size();
    std::vector<int> v;
    for(int i = 0; i < n; ++i)
        v.push_back(0);
    for(int i = 0; i < n; ++i)
        adjMatrix.push_back(v);
    for(int i = 0; i < n; ++i)
        for(size_t j = 0; j < _tab[i].size(); ++j)
            adjMatrix[i][_tab[i][j]] = 1;
}