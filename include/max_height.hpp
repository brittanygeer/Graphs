#pragma once
#include <iostream>
#include <vector>
#include "graph.hpp"

namespace cs251 {

class max_height {
    std::vector<std::pair<int, graph_vertex>> heap;
public:
	static int calculate(const graph &g);
    void heapifyUp(int index);
    void heapifyDown(int index);
    void push(std::pair<int, graph_vertex>);
    graph_vertex pop();
    bool empty();
    std::pair<int, graph_vertex> top();
};

}
