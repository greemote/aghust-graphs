#include "matrices.h"

class NewTab
{
    std::vector<std::vector<int>> _tab;

    bool checkIf01() const;
    bool checkIfAdjList() const;
    bool checkIfAdjMatrix() const;
    bool checkIfIncMatrix() const;

public:

    void addRow(std::string text);

    inline void readTab() const
    {
        if(_tab.size() != 0)
        {
            std::cout << "loaded matrix:" << std::endl;
            for(auto vOut : _tab)
            {
                for(auto v : vOut)
                    std::cout << v << " ";
                std::cout << std::endl;
            }
        }
    }

    void fill(AdjList*, AdjMatrix*, IncMatrix*) const;
};