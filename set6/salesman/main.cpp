#include "graph.h"

#define MAX_IT 10

void simulatedAnnealing(Graph* graph)
{
    double T, r;
    std::vector<int> edges {0, 0};
    Graph* graph1 = new Graph;
    for(int i = 100; i > 0; --i)
    {
        T = 0.001 * pow(i, 2);
        for(int it = 0; it < MAX_IT; ++it)
        {
            graph->getRandomEdges(edges);
            graph1->copy(graph);
            graph1->swapEdges(edges);
            if(graph1->calculateLength() < graph->calculateLength())
            {
                graph->copy(graph1);
            }
            else
            {
                r = (double)rand() / RAND_MAX;
                if(r < exp((graph1->calculateLength() - graph->calculateLength()) / -T))
                {
                    graph->copy(graph1);
                }
            }
        }
    }
    delete graph1;
}

void addNode(std::string text, Graph* graph)
{
    double x, y;
    char* str = const_cast<char*>(text.c_str());
    x = atof(strtok(str, " "));
    y = atof(strtok(NULL, " "));
    graph->addNode(x, y);
}

int main()
{
    Graph* graph = new Graph;
    std::string text;
    std::ifstream file("input_150.dat");

    while(getline(file, text))
        addNode(text, graph);
    graph->closeGraph();

    file.close();

    std::cout << "edges length: " << graph->calculateLength() << std::endl;
    graph->drawGraph();

    srand(time(NULL));

    simulatedAnnealing(graph);

    std::cout << "edges length: " << graph->calculateLength() << std::endl;
    graph->drawGraph();

    delete graph;

    return 0;
}