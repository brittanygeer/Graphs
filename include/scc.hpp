#pragma once
#include "graph.hpp"

namespace cs251 {

class scc {
public:
	static int search(const graph& g);
    static void strongConnect(const std::vector<graph_vertex>& V, int v, int& index, std::vector<int>& S, std::vector<std::vector<int>>& SCCs, std::vector<int>& indexMap, std::vector<int>& lowLinkMap, std::vector<bool>& onStack);

};

}
