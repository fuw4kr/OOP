#include "Graph.h"
#include "GraphAlgorithms.h" 
#include "User.h" 
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <iostream>
using namespace std;

Graph::~Graph() {
    for (auto& p : vertices) delete p.second;
    for (auto* e : edges) delete e;
}

void Graph::addVertex(Vertex* v) {
    if (!v) return;
    vertices[v->getId()] = v;
}

void Graph::addEdge(Edge* e) {
    if (!e) return;
    edges.push_back(e);
}

void Graph::removeVertex(int id) {
    if (vertices.count(id)) {
        auto it = remove_if(edges.begin(), edges.end(), [id](Edge* e) {
            if (e->getFrom() == id || e->getTo() == id) {
                delete e;
                return true;
            }
            return false;
            });
        edges.erase(it, edges.end());

        delete vertices[id];
        vertices.erase(id);
    }
}

void Graph::removeEdge(int from, int to) {
    auto it = remove_if(edges.begin(), edges.end(), [from, to](Edge* e) {
        if (e->getFrom() == from && e->getTo() == to) {
            delete e;
            return true;
        }
        return false;
        });
    edges.erase(it, edges.end());
}


Vertex* Graph::getVertex(int id) const {
    auto it = vertices.find(id);
    return (it != vertices.end()) ? it->second : nullptr;
}

vector<int> Graph::getNeighbors(int id) const {
    vector<int> neighbors;
    for (auto* e : edges) {
        if (e->getFrom() == id) neighbors.push_back(e->getTo());
    }
    return neighbors;
}

vector<Vertex*> Graph::getAllVertices() const {
    vector<Vertex*> result;
    for (auto& p : vertices) result.push_back(p.second);
    return result;
}

vector<Edge*> Graph::getAllEdges() const {
    return edges;
}

void Graph::print() const {
    cout << "Vertices" << endl;
    for (auto& p : vertices) p.second->print();
    cout << "Edges" << endl;
    for (auto* e : edges) e->print();
}

void Graph::exportToDot(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    file << "digraph G {\n";
    file << "  rankdir=LR;\n";

    for (const auto& p : vertices) {
        int id = p.first;
        file << "  " << id << " [label=\"User id " << id << "\"];\n";
    }

    for (auto* e : edges) {
        if (dynamic_cast<const Friendship*>(e)) {
            file << "  " << e->getFrom() << " -> " << e->getTo()
                << " [color=blue, label=\"friend\"];\n";
        }
        else if (dynamic_cast<const Subscription*>(e)) {
            file << "  " << e->getFrom() << " -> " << e->getTo()
                << " [color=green, label=\"follow\"];\n";
        }
        else if (dynamic_cast<const Message*>(e)) {
            file << "  " << e->getFrom() << " -> " << e->getTo()
                << " [color=red, label=\"msg\"];\n";
        }
        else if (dynamic_cast<const Post*>(e)) {
            file << "  " << e->getFrom() << " -> " << e->getTo()
                << " [color=yellow, label=\"post\"];\n";
        }
        else {
            file << "  " << e->getFrom() << " -> " << e->getTo() << ";\n";
        }
    }

    file << "}\n";
    file.close();
}
