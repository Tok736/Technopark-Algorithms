//
// Created by kotik on 16.12.2019.
//

#ifndef GRAPHSPRESENTATION_MATRIXGRAPH_H
#define GRAPHSPRESENTATION_MATRIXGRAPH_H

#include "IGraph.h"



class MatrixGraph : public IGraph {
private:
    size_t vertices;
    int ** data;

    void Init(size_t size);
    void Clear();
public:
    MatrixGraph(size_t size);
    MatrixGraph(const IGraph &other);
    virtual ~MatrixGraph() override;


    void Set(const IGraph &other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

};


#endif //GRAPHSPRESENTATION_MATRIXGRAPH_H
