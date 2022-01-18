#include "JohnsonAlgorithm.h"

using namespace std;
const int INFINIT = 8000;

void relax(distanceVector& dist, GraphFunctionality& graph, size_t u, size_t v) {//робить релаксацію ребра тобто виключення з циклу
    if (dist[v] > dist[u] + graph.edgeWeight(u, v)) {
        dist[v] = dist[u] + graph.edgeWeight(u, v);
        cout << u << "->" << v << "   ";
    }
}

void relax(distanceVector& dist, edgesContainer& edgesWeight, size_t u, size_t v) {//робить релаксацію ребра тобто виключення з циклу
    auto edge = find_if(edgesWeight.begin(), edgesWeight.end(),
        [u, v](Edge& e)->bool {
            return e.getFromVertex() == u &&
                e.getToVertex() == v;
        });
    if (dist[v] > dist[u] + edge->getDistance()) {
        dist[v] = dist[u] + edge->getDistance();
        cout << u << "->" << v << "   ";
    }
}

distanceVector belmanFord(GraphFunctionality& graph, size_t fromVertex) throw(runtime_error) {//функція виконує алгоритм Белмана-Форда
    auto edges = graph.getEdges();
    //min distance between vertex and vertices[i]
    distanceVector distance(graph.verticesSize());
    initDistanceVector(distance, fromVertex);
    for (int i = 0; i < graph.verticesSize(); i++) {
        for (auto& i : edges) {
            relax(distance, graph, i.getFromVertex(), i.getToVertex());
        }
    }
    for (auto& i : edges) {
        if (distance[i.getToVertex()] > distance[i.getFromVertex()] + graph.edgeWeight(i.getFromVertex(), i.getToVertex()))
            throw runtime_error("negative cycle");
    }
    return  distance;
}

vector<distanceVector> johnsonAlgorithm(GraphFunctionality& g) {//функція виконує алгоритм Джонсона 
    vector<distanceVector> res;
    g.addSpecialVertex();
    auto r = belmanFord(g, g.verticesSize() - 1);
    edgesContainer newEdgesVector = g.getEdges();
    for (auto& i : newEdgesVector) {
        i.setDistance(i.getDistance() + r[i.getFromVertex()] - r[i.getToVertex()]);
    }

    for (int i = 0; i < newEdgesVector.size(); i++) {
        cout << g.getEdges()[i].getDistance() << "->" << newEdgesVector[i].getDistance() << endl;
    }

    auto vertices = g.verticesSize();

    for (int i = 0; i < vertices; i++) {
        res.push_back(dijkstra(g, newEdgesVector, i));
    }

    for (int i = 0; i < res.size() - 1; i++) {
        for (int j = 0; j < res[i].size() - 1; j++) {
            cout << i << "->" << j << " = ";
            if (res[i][j] != INFINIT) {
                cout << res[i][j] << " | " << res[i][j] + r[j] - r[i] << endl;
            }
            else {
                cout << "infinity" << endl;
            }
        }
    }

    return res;
}

distanceVector dijkstra(GraphFunctionality& graph, edgesContainer newEdgesWeight, size_t fromVertex) {//функція викнує алгоритм Дейкстри
    distanceVector distance(graph.verticesSize());
    initDistanceVector(distance, fromVertex);

    vector<bool> inGraph(graph.verticesSize(), false);
    inGraph[fromVertex] = true;

    while (true) {
        auto m = findMin(inGraph, newEdgesWeight);
        if (m.second == INFINIT) {
            break;
        }
        inGraph[m.first] = true;
        for (auto& i : newEdgesWeight) {
            if (inGraph[i.getFromVertex()] &&
                inGraph[i.getToVertex()]) {
                relax(distance, newEdgesWeight, i.getFromVertex(), i.getToVertex());
            }
        }
    }
    return distance;
}

pair<size_t, int> findMin(vector<bool>& in, edgesContainer& edgesWeight) {//функція пошуку мінімального ребра
    int minDist = INFINITY;
    size_t minDistVertex = INFINITY;
    for (auto& i : edgesWeight) {
        if (i.getDistance() < minDist &&
            in[i.getFromVertex()] &&
            !in[i.getToVertex()]) {
            minDist = i.getDistance();
            minDistVertex = i.getToVertex();
        }
    }
    return make_pair(minDistVertex, minDist);
}

void initDistanceVector(distanceVector& distance, size_t fromVertex) {//допоміжна функція  знаходить довжину маршруту 
    for (int i = 0; i < distance.size(); i++) {
        distance[i] = fromVertex == i ? 0 : INFINIT;
    }
}