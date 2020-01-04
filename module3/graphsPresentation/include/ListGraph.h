//
// Created by kotik on 16.12.2019.
//

#ifndef GRAPHSPRESENTATION_LISTGRAPH_H
#define GRAPHSPRESENTATION_LISTGRAPH_H

#include "IGraph.h"
#include <forward_list>

class ListGraph : public IGraph {
private:
    size_t vertices;
    std::forward_list<int> * data;

    void Init(size_t size);
    void Clear();
public:
    ListGraph(size_t size);
    ListGraph(const IGraph &other);
    virtual ~ListGraph() override;


    void Set(const IGraph &other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

};

#endif //GRAPHSPRESENTATION_LISTGRAPH_H
