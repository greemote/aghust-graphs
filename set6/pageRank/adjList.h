#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>

class AdjList
{
    std::vector<std::vector<int>> _tab;

public:

    AdjList(std::string filename);

    void addRow(std::string text);

    void convertToAdjMatrix(std::vector<std::vector<int>>& adjMatrix) const;

    inline std::vector<int> getNodes(int node) const
    {
        return _tab[node];
    }
    inline size_t getSize(){ return _tab.size(); }
    
    inline void readTab() const
    {
        if(_tab.size() != 0)
        {
            std::cout << "loaded list:" << std::endl;
            for(auto vOut : _tab)
            {
                for(auto v : vOut)
                    std::cout << v << " ";
                std::cout << std::endl;
            }
        }
    }
};