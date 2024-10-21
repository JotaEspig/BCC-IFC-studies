#pragma once

#include <cstdint>
#include <unordered_map>
#include <vector>

class Graph {
public:
    enum ConnectionType {
        DIRECTED = 1,
        UNDIRECTED = 2,
    };

    Graph();
    ~Graph();

    void add_edge(const int u, const int v, const int type = UNDIRECTED);
    bool bfs(const int start, const int search);
    bool dfs(const int start, const int search);
    void
    dfs_util(const int start, const int search, std::vector<bool> &visited);
    void print_adj_matrix();

private:
    typedef std::unordered_map<int, std::unordered_map<int, int>> adj_matrix_t;
    std::uint32_t size = 0;
    adj_matrix_t adj_matrix;
};
