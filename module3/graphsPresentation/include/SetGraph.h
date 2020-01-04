#ifndef GRAPHSPRESENTATION_SETGRAPH_H
#define GRAPHSPRESENTATION_SETGRAPH_H

#include "IGraph.h"
#include <set>

class SetGraph : public IGraph {
private:
    size_t vertices;
    std::set<int> * data;

    void Init(size_t size);
    void Clear();
public:
    SetGraph(size_t size);
    SetGraph(const IGraph &other);
    virtual ~SetGraph() override;


    void Set(const IGraph &other);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    virtual std::vector<int> GetPrevVertices(int vertex) const override;

};

#endif //GRAPHSPRESENTATION_SETGRAPH_H
