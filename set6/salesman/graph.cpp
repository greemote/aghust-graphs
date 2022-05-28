#include "graph.h"

void Graph::addNode(double x, double y)
{
    Node* n = new Node(x, y);
    if(nodes.empty())
        nodes.push_back(n);
    else
    {
        Node* n0 = nodes.back();
        nodes.push_back(n);

        Edge* e = new Edge(n0, n);
        edges.push_back(e);
    }
}

void Graph::drawGraph() const
{
    if(!nodes.empty())
    {
        size_t size = nodes.size();
        std::vector<double> x, y;

        for(auto e : edges)
        {
            plt::plot({e->getN1()->getX(), e->getN2()->getX()}, {e->getN1()->getY(), e->getN2()->getY()}, {{"c", "red"}, {"ls", "-"}});
        }

        for(size_t i = 0; i < size; ++i)
        {
            x.push_back(nodes[i]->getX());
            y.push_back(nodes[i]->getY());
        }

        plt::plot(x, y, {{"c", "red"}, {"marker", "o"}, {"ls", ""}});
        plt::show();
    }
}

void Graph::getRandomEdges(std::vector<int>& e) const
{
    if(!edges.empty())
    {
        int size = edges.size(), e1, e2;
        do
        {
            e1 = rand()%size;
            e2 = rand()%size;
        } while 
        (
            (edges[e1]->getN1()->getX() == edges[e2]->getN1()->getX() && edges[e1]->getN1()->getY() == edges[e2]->getN1()->getY()) || 
            (edges[e1]->getN1()->getX() == edges[e2]->getN2()->getX() && edges[e1]->getN1()->getY() == edges[e2]->getN2()->getY()) || 
            (edges[e1]->getN2()->getX() == edges[e2]->getN1()->getX() && edges[e1]->getN2()->getY() == edges[e2]->getN1()->getY()) || 
            (edges[e1]->getN2()->getX() == edges[e2]->getN2()->getX() && edges[e1]->getN2()->getY() == edges[e2]->getN2()->getY()) 
        );
        e[0] = e1;
        e[1] = e2;
    }
}

void Graph::swapEdges(std::vector<int>& e)
{
    if(!edges.empty())
    {
        Node* a = edges[e[0]]->getN1();
        Node* b = edges[e[0]]->getN2();
        Node* c = edges[e[1]]->getN1();
        Node* d = edges[e[1]]->getN2();

        Edge* newEdge1 = new Edge(a, c);
        Edge* newEdge2 = new Edge(b, d);

        delete edges[e[0]];
        edges[e[0]] = newEdge1;
        delete edges[e[1]];
        edges[e[1]] = newEdge2;

        edges[e[0]]->updateLength();
        edges[e[1]]->updateLength();
    }
}

void Graph::clear()
{
    Node* tempNode;
    Edge* tempEdge;
    while(!nodes.empty())
    {
        tempNode = nodes.back();
        tempEdge = edges.back();
        nodes.pop_back();
        edges.pop_back();
        delete tempNode;
        delete tempEdge;
    }
}

void Graph::copy(const Graph* g)
{
    clear();
    if(!g->edges.empty())
    {
        Node* n = new Node(g->edges.front()->getN1()->getX(), g->edges.front()->getN1()->getY());
        nodes.push_back(n);
        for(size_t i = 0; i < g->edges.size() - 1; ++i)
        {
            n = new Node(g->edges[i]->getN2()->getX(), g->edges[i]->getN2()->getY());
            edges.push_back(new Edge(nodes.back(), n));
            nodes.push_back(n);
        }
        edges.push_back(new Edge(nodes.back(), nodes.front()));
    }
}