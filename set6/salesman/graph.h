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

    Node(double x, double y) : _x(x), _y(y) {}

    double getX() const { return _x; }
    double getY() const { return _y; }
};

class Edge
{
    Node* _n1;
    Node* _n2;
    double _l;

public:

    Edge(Node* n1, Node* n2) : _n1(n1), _n2(n2) { updateLength(); }

    Node* getN1() const { return _n1; }
    Node* getN2() const { return _n2; }
    double getLength() const { return _l; }

    void setN1(Node* n) { _n1 = n; }
    void setN2(Node* n) { _n2 = n; }
    void updateLength()
    {
        _l = sqrt(pow(_n1->getX() - _n2->getX(), 2) +  pow(_n1->getY() - _n2->getY(), 2));
    }
};

class Graph
{
    std::vector<Node*> nodes {};
    std::vector<Edge*> edges {};

public:

    ~Graph() { clear(); }

    void addNode(double x, double y);
    void closeGraph()
    {
        if(nodes.size() > 1)
            edges.push_back(new Edge(nodes.back(), nodes.front()));
    }
    double calculateLength() const
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
    void copy(const Graph*);
};