#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
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
    virtual void print() const = 0;
    int getFrom() const { return from; }
    int getTo() const { return to; }
};

class Graph {
public:
    virtual ~Graph() {}
    virtual void addVertex(Vertex* v) = 0;
    virtual void addEdge(Edge* e) = 0;
    virtual void removeVertex(int id) = 0;
    virtual void removeEdge(int from, int to) = 0;
    virtual void print() const = 0;
};
#endif // GRAPH_H
 
