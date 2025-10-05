#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Vertex {
protected:
    int id;
public:
    Vertex(int id) : id(id) {}
    virtual ~Vertex() {}
    int getId() const { return id; }
    virtual void print() const = 0;
};

class Edge {
protected:
    int from;
    int to;
public:
    Edge(int f, int t) : from(f), to(t) {}
    virtual ~Edge() {}
    int getFrom() const { return from; }
    int getTo() const { return to; }
    virtual void print() const = 0;
};

class Graph {
protected:
    map<int, Vertex*> vertices;
    vector<Edge*> edges;
public:
    
    virtual ~Graph(); 

    virtual void addVertex(Vertex* v);
    virtual void addEdge(Edge* e);
    virtual void removeVertex(int id);
    virtual void removeEdge(int from, int to);

    virtual Vertex* getVertex(int id) const;
    virtual vector<int> getNeighbors(int id) const;
    virtual vector<Vertex*> getAllVertices() const;
    virtual vector<Edge*> getAllEdges() const;

    virtual void print() const;
};
#endif // GRAPH_H
 
