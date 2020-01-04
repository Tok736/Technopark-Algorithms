#include "ArcGraph.h"
#include <iostream>


ArcGraph::ArcGraph(size_t size) {
    Init(size);
}

ArcGraph::~ArcGraph() {
    Clear();
}

void ArcGraph::AddEdge(int from, int to) {
    data.push_back(std::make_pair(from, to));
}

int ArcGraph::VerticesCount() const {
    return vertices;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (auto it : data) {
        if (it.first == vertex) {
            next.push_back(it.second);
        }
    }
    return next;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (auto it : data) {
        if (it.second == vertex) {
            prev.push_back(it.first);
        }
    }
    return prev;
}

void ArcGraph::Init(size_t size) {
    this->vertices = size;
}

void ArcGraph::Clear() {

}

ArcGraph::ArcGraph(const IGraph &other) {
    Set(other);
}

void ArcGraph::Set(const IGraph &other) {
    vertices = other.VerticesCount();
    data.clear();
    for (int i = 0; i < other.VerticesCount(); i++) {
        std::vector<int> next(other.GetNextVertices(i));
        for (auto it : next) {
            if (i < it) {
            }
        }
    }
}
