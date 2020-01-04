#include <iostream>
#include <forward_list>
#include <vector>
#include <utility>

#define PR(a) std::cout << #a << " = " << a << std::endl;


class ListGraph {
private:
    size_t _vertices;
    size_t _ribs;
    std::forward_list<std::pair<int, int>> * data;

    void init(size_t size);
    void clear();
public:
    ListGraph(size_t size);
    ~ListGraph();

    void addEdge(int from, int to, int weight);

    int vertices() const;
    int ribs() const;


    std::vector<std::pair<int, int>> getNextVertices(int vertex) const;

};



ListGraph::ListGraph(size_t size) {
    init(size);
}
ListGraph::~ListGraph() {
    clear();
}
void ListGraph::addEdge(int from, int to, int weight) {
    data[from].push_front(std::make_pair(to, weight));
    data[to].push_front(std::make_pair(from, weight));
    _ribs++;
}
int ListGraph::vertices() const {
    return _vertices;
}
int ListGraph::ribs() const {
    return _ribs;
}
std::vector<std::pair<int, int>> ListGraph::getNextVertices(int vertex) const {
    std::vector<std::pair<int, int>> next;
    for (auto it : data[vertex]) {
        next.push_back(it);
    }
    return next;
}
void ListGraph::init(size_t size) {
    this->_vertices = size;
    this->_ribs = 0;
    data = new std::forward_list<std::pair<int, int>>[_vertices];
}
void ListGraph::clear() {
    delete[] data;
}


int dijkstra(const ListGraph &V, int from, int to) {

    int * d = new int[V.vertices()];
    bool * used = new bool[V.vertices()];
    for (int i = 0; i < V.vertices(); i++) {
        d[i] = 10000000;
        used[i] = false;
    }
    d[from] = 0;
    for (int i = 0; i < V.vertices(); i++) {
        int v = -1;
        for (int j = 0; j < V.vertices(); j++) {
            if (!used[j] && (v == -1 || d[j] < d[v])) v = j;
        }
        if (d[v] == 10000000) break;
        used[v] = true;
        for (auto it : V.getNextVertices(v)) {
            if (d[v] + it.second < d[it.first]) {
                d[it.first] = d[v] + it.second;
            }
        }
    }
    return d[to];
}

void test() {

    const int n = 6;
    const int r = 9;
    ListGraph * graph = new ListGraph(n);
    int cribs[r][3] = {
            {0, 3, 1},
            {0, 4, 2},
            {1, 2, 7},
            {1, 3, 2},
            {1, 4, 3},
            {1, 5, 3},
            {2, 5, 3},
            {3, 4, 4},
            {3, 5, 6}
    };

    int start = 0;
    int end = 2;
    int ** ribs = new int *[r];
    for (int i = 0; i < r; i++) {
        ribs[i] = new int[3];
        ribs[i][0] = cribs[i][0];
        ribs[i][1] = cribs[i][1];
        ribs[i][2] = cribs[i][2];
    }

    for (int i = 0; i < r; i++) {
        graph->addEdge(ribs[i][0], ribs[i][1], ribs[i][2]);
    }

    std::cout << "Next _vertices: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::vector<std::pair<int, int>> next(graph->getNextVertices(i));
        std::cout << i << ": ";
        for (auto it : next) {
            std::cout << "(" << it.first << ", " << it.second << ")  ";
        }
        std::cout << std::endl;
    }

    int res = dijkstra(*graph, start, end);
    std::cout << "res: " << res << std::endl;
}





void mainTest() {
    int n, r, start, end;
    std::cin >> n >> r;
    ListGraph * graph = new ListGraph(n);

    for (int i = 0; i < r; i++) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph->addEdge(from, to, weight);
    }

    std::cin >> start >> end;

    int res = dijkstra(*graph, start, end);
    std::cout << res << std::endl;




}

int main() {

    mainTest();
    return 0;
}
