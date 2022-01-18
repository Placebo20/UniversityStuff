


#include "graph.h"

using namespace std;

//************************* методи классу Vertex*************************//

Vertex::Vertex(Group& d) :data(d) {
}

Group& Vertex::getData() {
    return  data;
}

//************************* мктоли классуEdge*************************//

Edge::Edge(size_t f, size_t t, int dist) :
    from(f), to(t), distance(dist) {
}

int Edge::getDistance() {
    return distance;
}

size_t Edge::getFromVertex() {
    return  from;
}

size_t Edge::getToVertex() {
    return  to;
}

void Edge::setDistance(int dist) {
    distance = dist;
}

//************************* методи классу AdjecentListBasedGraph *************************

AdjecentListBasedGraph::AdjecentListBasedGraph(std::string file, std::vector<Group>& dataVector) {
    for (int i = 0; i < dataVector.size(); i++) {
        vertices.emplace_back(dataVector[i]);
    }
    ifstream read(file);
    size_t from;
    size_t to;
    int dist;
    while (!read.eof()) {
        read >> from >> to >> dist;
        edges.emplace_back(from, to, dist);
    }
    read.close();
}

Edge& AdjecentListBasedGraph::findEdge(size_t u, size_t v)
throw(runtime_error) {
    for (auto& i : edges) {
        if (i.getFromVertex() == u && i.getToVertex() == v)
            return i;
    }
    throw runtime_error("Edge was not found");
}

bool AdjecentListBasedGraph::isEdge(size_t u, size_t v) {
    try {
        findEdge(u, v);
    }
    catch (runtime_error& findError) {
        return false;
    }
    return true;
}

int AdjecentListBasedGraph::edgeWeight(size_t u, size_t v) {
    int weight = INT_MAX;
    try {
        weight = findEdge(u, v).getDistance();
    }
    catch (runtime_error& findError) {
        throw findError;
    }
    return weight;
}

edgesContainer& AdjecentListBasedGraph::getEdges() {
    return edges;
}

verticesContainer& AdjecentListBasedGraph::getVertices() {
    return vertices;
}

size_t AdjecentListBasedGraph::verticesSize() {
    return vertices.size();
}

size_t AdjecentListBasedGraph::edgesSize() {
    return edges.size();
}

void AdjecentListBasedGraph::addSpecialVertex() {
    auto pl = Group();
    vertices.push_back(pl);
    for (int i = 0; i < vertices.size() - 1; i++) {
        edges.emplace_back(vertices.size() - 1, i, 0);
    }
}

//************************* методи классу Graph*************************//

Graph::Graph(std::string file, vector<Group>& dataVector) :graphData(file, dataVector) {
}

bool Graph::isEdge(size_t u, size_t v) {
    return graphData.isEdge(u, v);
}

int Graph::edgeWeight(size_t u, size_t v) {
    return graphData.edgeWeight(u, v);
}

edgesContainer& Graph::getEdges() {
    return graphData.getEdges();
}

verticesContainer& Graph::getVertices() {
    return graphData.getVertices();
}

size_t Graph::verticesSize() {
    return graphData.verticesSize();
}

size_t Graph::edgesSize() {
    return graphData.edgesSize();
}

void Graph::addSpecialVertex() {
    graphData.addSpecialVertex();
}

