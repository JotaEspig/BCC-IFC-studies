#include <iostream>

#include "graph.hpp"

Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::add_edge(const int u, const int v, const int type) {
        adj_matrix[u][v] = 1;
    if (type & ConnectionType::UNDIRECTED) {
        adj_matrix[v][u] = 1;
    }
    ++size;
}

bool Graph::bfs(const int start, const int search) {
    std::vector<bool> visited(size, false);
    std::vector<int> queue;

    queue.push_back(start);
    visited[start] = true;

    while (!queue.empty()) {
        int vertex = queue.front();
        queue.erase(queue.begin());

        if (vertex == search) {
            return true;
        }

        for (const auto &col : adj_matrix[vertex]) {
            if (!visited[col.first]) {
                queue.push_back(col.first);
                visited[col.first] = true;
            }
        }
    }
    return false;
}

bool Graph::dfs(const int start, const int search) {
    std::vector<bool> visited(size, false);
    dfs_util(start, search, visited);
    return visited[search];
}

void Graph::dfs_util(
    const int start, const int search, std::vector<bool> &visited
) {
    visited[start] = true;

    for (const auto &col : adj_matrix[start]) {
        if (!visited[col.first]) {
            dfs_util(col.first, search, visited);
        }
    }
}

void Graph::print_adj_matrix() {
    for (const auto &row : adj_matrix) {
        for (const auto &col : row.second) {
            std::cout << row.first << " -> " << col.first << "\n";
        }
        std::cout << std::endl;
    }
}
