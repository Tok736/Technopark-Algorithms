//
// Created by kotik on 16.12.2019.
//

#include "MatrixGraph.h"
#include <iostream>

MatrixGraph::MatrixGraph(size_t size) {
    Init(size);
}

MatrixGraph::~MatrixGraph() {
    Clear();
}

void MatrixGraph::AddEdge(int from, int to) {
    data[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
    return vertices;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;
    for (int i = 0; i < vertices; i++) {
        if (data[vertex][i] != 0) next.push_back(i);
    }
    return next;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;
    for (int i = 0; i < vertices; i++) {
        if (data[i][vertex] != 0) prev.push_back(i);
    }
    return prev;
}

void MatrixGraph::Init(size_t size) {
    this->vertices = size;
    data = new int *[vertices];
    for (int i = 0; i < vertices; i++) {
        data[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            data[i][j] = 0;
        }
    }
}

void MatrixGraph::Clear() {
    for (int i = 0; i < vertices; i++) {
        delete[] data[i];
    }
    delete[] data;
    data = nullptr;
}

MatrixGraph::MatrixGraph(const IGraph &other) {
    Set(other);
}

void MatrixGraph::Set(const IGraph &other) {
    if (data != nullptr) Clear();
    vertices = other.VerticesCount();
    for (int i = 0; i < vertices; i++) {
        std::vector<int> temp(other.GetNextVertices(i));
        for (auto it : temp) {
            data[i][it] = 1;
        }
    }
}


