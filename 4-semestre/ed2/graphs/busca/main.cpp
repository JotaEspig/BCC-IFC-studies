#include <iostream>

#include "graph.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Graph g;

    g.add_edge(0, 1);
    g.add_edge(2, 0, Graph::DIRECTED);
    g.add_edge(1, 4);
    g.add_edge(3, 4);
    g.add_edge(2, 3);
    g.print_adj_matrix();
    std::cout << g.bfs(0, 3) << std::endl;
    std::cout << g.dfs(0, 3) << std::endl;
    return 0;
}
