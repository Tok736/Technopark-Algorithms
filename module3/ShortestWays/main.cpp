#include <iostream>
#include <forward_list>
#include <vector>
#include <utility>
#include <queue>


class ListGraph {
private:
    size_t _vertices;
    size_t _ribs;
    std::forward_list<int> * data;

    void init(size_t size);
    void clear();
public:
    ListGraph(size_t size);
    ~ListGraph();

    void addEdge(int from, int to);

    int vertices() const;
    int ribs() const;


    std::vector<int> getNextVertices(int vertex) const;

};



ListGraph::ListGraph(size_t size) {
    init(size);
}
ListGraph::~ListGraph() {
    clear();
}
void ListGraph::addEdge(int from, int to) {
    data[from].push_front(to);
    data[to].push_front(from);
    _ribs++;
}
int ListGraph::vertices() const {
    return _vertices;
}
int ListGraph::ribs() const {
    return _ribs;
}
std::vector<int> ListGraph::getNextVertices(int vertex) const {
    std::vector<int> next;
    for (auto it : data[vertex]) {
        next.push_back(it);
    }
    return next;
}
void ListGraph::init(size_t size) {
    this->_vertices = size;
    this->_ribs = 0;
    data = new std::forward_list<int>[_vertices];
}
void ListGraph::clear() {
    delete[] data;
}



int amountOfShortestWays(const ListGraph &graph, int from, int to) {
    bool * visited = new bool[graph.vertices()];
    int * ways = new int[graph.vertices()];
    int * d = new int[graph.vertices()];

    for (int i = 0; i < graph.vertices(); i++) {
        visited[i] = false;
        ways[i] = 0;
    }

    visited[from] = true;
    d[from] = 0;
    ways[from] = 1;

    std::queue<int> q;
    q.push(from);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        std::vector<int> next(graph.getNextVertices(curr));
        for (auto it : next) {
            if (!visited[it]) {
                d[it] = d[curr] + 1;
                q.push(it);
                visited[it] = true;
            }
            if (d[curr] + 1 == d[it]) {
                ways[it] += ways[curr];
            }
        }
    }

    return ways[to];
}


void mainTest() {
    int n, r, start, end;
    std::cin >> n >> r;
    ListGraph * graph = new ListGraph(n);

    for (int i = 0; i < r; i++) {
        int from, to;
        std::cin >> from >> to;
        graph->addEdge(from, to);
    }

    std::cin >> start >> end;

    int res = amountOfShortestWays(*graph, start, end);
    std::cout << res << std::endl;



}



int main() {
    mainTest();

    return 0;
}
