//
// Created by kotik on 16.12.2019.
//

#ifndef GRAPHSPRESENTATION_IGRAPH_H
#define GRAPHSPRESENTATION_IGRAPH_H


#include <vector>


class IGraph {
public:
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};




#endif //GRAPHSPRESENTATION_IGRAPH_H
