#include <stdio.h>
#include <list>
#include <vector>
#include "group.h"
#include <string>



class Vertex;//класс для  опису вершини графу
class Edge;//класс для опису ребра 
class Graph;//класс для опису графа


using verticesContainer = std::vector<Vertex>;
using edgesContainer = std::vector<Edge>;

class Vertex {//класс для опису ребра 
private:
    Group data;
public:
    Vertex(Group& d);
    Group& getData();
    bool operator== (const Vertex& v)const {
        return this->data == v.data;
    }
};

class Edge {//класс для опису ребра
private:
    size_t from;
    size_t to;
    int distance;
public:
    Edge(size_t f, size_t t, int dist);
    int getDistance();
    void setDistance(int distance);
    size_t getFromVertex();
    size_t getToVertex();
};

class GraphFunctionality {
public:
    virtual bool isEdge(size_t u, size_t v) = 0;
    virtual int edgeWeight(size_t u, size_t v) = 0;
    virtual size_t verticesSize() = 0;
    virtual size_t edgesSize() = 0;
    virtual edgesContainer& getEdges() = 0;
    virtual verticesContainer& getVertices() = 0;
    virtual void addSpecialVertex() = 0;
};

class AdjecentListBasedGraph {//класс для опису списку мінімальних маршрутів
private:
    verticesContainer vertices;
    edgesContainer edges;

    Edge& findEdge(size_t u, size_t v)throw(std::runtime_error);
public:
    AdjecentListBasedGraph(std::string file, std::vector<Group>& dataVector);
    bool isEdge(size_t u, size_t v);
    int edgeWeight(size_t u, size_t v);
    edgesContainer& getEdges();
    verticesContainer& getVertices();
    size_t verticesSize();
    size_t edgesSize();
    void addSpecialVertex();
};

class Graph : public GraphFunctionality {//класс для опису графа
private:
    AdjecentListBasedGraph graphData;
public:
    Graph(std::string file, std::vector<Group>& dataVector);
    bool isEdge(size_t u, size_t v);
    int edgeWeight(size_t u, size_t v);
    edgesContainer& getEdges();
    verticesContainer& getVertices();
    size_t verticesSize();
    size_t edgesSize();
    void addSpecialVertex();

};