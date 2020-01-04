#include <iostream>
#include "IGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void test();
void subtest(IGraph * graph, int n, int r, int ** ribs);


void test() {
    const int n = 8;
    const int r = 14;
    int cribs[r][2] = {
            {1, 2},
            {2, 3},
            {2, 7},
            {2, 8},
            {3, 4},
            {3, 6},
            {4, 3},
            {4, 5},
            {5, 4},
            {5, 6},
            {6, 7},
            {7, 6},
            {8, 1},
            {8, 7},
    };
    int ** ribs = new int *[r];
    for (int i = 0; i < r; i++) {
        ribs[i] = new int[2];
        ribs[i][0] = cribs[i][0];
        ribs[i][1] = cribs[i][1];
    }

    std::cout << "MatrixGraph test: " << std::endl;
    IGraph * mgraph = new MatrixGraph(n);
    subtest(mgraph, n, r, ribs);

    std::cout << "ListGraph test: " << std::endl;
    IGraph * lgraph = new ListGraph(n);
    subtest(lgraph, n, r, ribs);

    std::cout << "ArcGraph test: " << std::endl;
    IGraph * agraph = new ArcGraph(n);
    subtest(agraph, n, r, ribs);

    std::cout << "SetGraph test: " << std::endl;
    IGraph * sgraph = new SetGraph(n);
    subtest(sgraph, n, r, ribs);



    std::cout << "ListGraph copying test: " << std::endl;
    IGraph * c_lgraph = new ListGraph(*mgraph);
    subtest(c_lgraph, n, r, ribs);

    std::cout << "ArcGraph copying test: " << std::endl;
    IGraph * c_agraph = new ArcGraph(*mgraph);
    subtest(c_agraph, n, r, ribs);

    std::cout << "SetGraph copying test: " << std::endl;
    IGraph * c_sgraph = new SetGraph(*mgraph);
    subtest(c_sgraph, n, r, ribs);


}

void test2() {
    const int n = 8;
    const int r = 14;
    int cribs[r][2] = {
            {1, 2},
            {2, 3},
            {2, 7},
            {2, 8},
            {3, 4},
            {3, 6},
            {4, 3},
            {4, 5},
            {5, 4},
            {5, 6},
            {6, 7},
            {7, 6},
            {8, 1},
            {8, 7},
    };
    int ** ribs = new int *[r];
    for (int i = 0; i < r; i++) {
        ribs[i] = new int[2];
        ribs[i][0] = cribs[i][0];
        ribs[i][1] = cribs[i][1];
    }

    IGraph * mgraph = new MatrixGraph(n);


    std::cout << "ListGraph copying test: " << std::endl;
    IGraph * c_lgraph = new ListGraph(*mgraph);
    subtest(c_lgraph, n, r, ribs);

    std::cout << "ArcGraph copying test: " << std::endl;
    IGraph * c_agraph = new ArcGraph(*mgraph);
    subtest(c_agraph, n, r, ribs);

    std::cout << "SetGraph copying test: " << std::endl;
    IGraph * c_sgraph = new SetGraph(*mgraph);
    subtest(c_sgraph, n, r, ribs);
}

void subtest(IGraph * graph, int n, int r, int ** ribs) {
    for (int i = 0; i < r; i++) {
        graph->AddEdge(ribs[i][0] - 1, ribs[i][1] - 1);
    }

    std::cout << "Next vertices: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::vector<int> next(graph->GetNextVertices(i));
        std::cout << i << ": ";
        for (auto it : next) {
            std::cout << it << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << "Prev vertices: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::vector<int> next(graph->GetPrevVertices(i));
        std::cout << i << ": ";
        for (auto it : next) {
            std::cout << it << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n\n";
}



int main() {


    test();



    return 0;
}
