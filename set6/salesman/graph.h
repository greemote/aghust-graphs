#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

class Node
{
    double _x, _y;

public:

    inline Node(double x, double y) : _x(x), _y(y) {}

    inline double getX() const { return _x; }
    inline double getY() const { return _y; }

    inline void setX(double x) { _x = x; }
    inline void setY(double y) { _y = y; }
};

class Edge
{
    Node* _n1;
    Node* _n2;
    double _l;

public:

    inline Edge(Node* n1, Node* n2) : _n1(n1), _n2(n2) { updateLength(); }

    inline Node* getN1() const { return _n1; }
    inline Node* getN2() const { return _n2; }
    inline double getLength() const { return _l; }

    inline void setN1(Node* n) { _n1 = n; }
    inline void setN2(Node* n) { _n2 = n; }
    inline void updateLength()
    {
        _l = sqrt(pow(_n1->getX() - _n2->getX(), 2) +  pow(_n1->getY() - _n2->getY(), 2));
    }
};

class Graph
{
    std::vector<Node*> nodes {};
    std::vector<Edge*> edges {};

public:

    inline ~Graph() { clear(); }

    void addNode(double x, double y);
    inline void closeGraph()
    {
        if(nodes.size() > 1)
            edges.push_back(new Edge(nodes.back(), nodes.front()));
    }
    inline double calculateLength() const
    {
        double length = 0.;
        for(auto e : edges)
            length += e->getLength();
        return length;
    }

    void drawGraph() const;
    void getRandomEdges(std::vector<int>&) const;
    void swapEdges(std::vector<int>&);
    void clear();

    Graph& operator=(const Graph&);
};