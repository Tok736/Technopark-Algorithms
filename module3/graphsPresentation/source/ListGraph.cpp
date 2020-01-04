#include "ListGraph.h"
#include <iostream>

ListGraph::ListGraph(size_t size) {
    Init(size);
}

ListGraph::~ListGraph() {
    Clear();
}

void ListGraph::AddEdge(int from, int to) {
    data[from].push_front(to);
}

int ListGraph::VerticesCount() const {
    return vertices;
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (auto it : data[vertex]) {
        next.push_back(it);
    }
    return next;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (int i = 0; i < vertices; i++) {
        for (auto it : data[i]) {
            if (it == vertex) prev.push_back(i);
        }
    }
    return prev;
}

void ListGraph::Init(size_t size) {
    this->vertices = size;
    data = new std::forward_list<int>[vertices];
}

void ListGraph::Clear() {
    delete[] data;
}

ListGraph::ListGraph(const IGraph &other) {
    Set(other);
}

void ListGraph::Set(const IGraph &other) {
    if (data != nullptr) Clear();
    vertices = other.VerticesCount();

    data = new std::forward_list<int>[vertices];
    for (int i = 0; i < other.VerticesCount(); i++) {
        std::vector<int> next(other.GetNextVertices(i));
        for (auto it : next) {
//            if (i < it) data[i].push_front(it);
        }
    }
}
