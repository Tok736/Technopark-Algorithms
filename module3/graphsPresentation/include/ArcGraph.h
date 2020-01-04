//
// Created by kotik on 16.12.2019.
//

#ifndef GRAPHSPRESENTATION_ARCGRAPH_H
#define GRAPHSPRESENTATION_ARCGRAPH_H

#include "IGraph.h"

class ArcGraph : public IGraph {
private:
    size_t vertices;
    std::vector<std::pair<int, int>> data;

    void Init(size_t size);
    void Clear();
public:
    ArcGraph(size_t size);
    ArcGraph(const IGraph &other);
    virtual ~ArcGraph() override;


    void Set(const IGraph &other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

};

#endif //GRAPHSPRESENTATION_ARCGRAPH_H
