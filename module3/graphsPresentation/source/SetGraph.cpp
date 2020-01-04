#include "SetGraph.h"
#include <iostream>

SetGraph::SetGraph(size_t size) {
    Init(size);
}

SetGraph::~SetGraph() {
    Clear();
}

void SetGraph::AddEdge(int from, int to) {
    data[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return vertices;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (auto it : data[vertex]) {
        next.push_back(it);
    }
    return next;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (int i = 0; i < vertices; i++) {
        for (auto it : data[i]) {
            if (it == vertex) prev.push_back(i);
        }
    }
    return prev;
}

void SetGraph::Init(size_t size) {
    this->vertices = size;
    data = new std::set<int>[vertices];
}

void SetGraph::Clear() {
    delete[] data;
}

SetGraph::SetGraph(const IGraph &other) {
    Set(other);
}

void SetGraph::Set(const IGraph &other) {
    if (data != nullptr) Clear();
    vertices = other.VerticesCount();

    data = new std::set<int>[vertices];
    for (int i = 0; i < other.VerticesCount(); i++) {
        std::vector<int> next(other.GetNextVertices(i));
        for (auto it : next) {
            data[i].insert(it);
        }
    }
}
