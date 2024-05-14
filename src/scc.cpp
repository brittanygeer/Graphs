#include "scc.hpp"

using namespace cs251;

int scc::search(const graph& g) {
    std::vector<graph_vertex> V = g.get_vertices();
    int index = 0;
    std::vector<int> S = {};
    std::vector<std::vector<int>> SCCs = {};
    std::vector<int> indexMap(V.size(), -1);
    std::vector<int> lowLinkMap(V.size(), -1);
    std::vector<bool> onStack(V.size(), false);
    for (int v = 0; v < V.size(); v++) {
        if (indexMap[v] == -1) {
            strongConnect(V, v, index, S, SCCs, indexMap, lowLinkMap, onStack);
        }    
    }
    return SCCs.size();
}

void scc::strongConnect(const std::vector<graph_vertex>& V, int v, int& index, std::vector<int>& S, std::vector<std::vector<int>>& SCCs, std::vector<int>& indexMap, std::vector<int>& lowLinkMap, std::vector<bool>& onStack) {
    indexMap[v] = index;
    lowLinkMap[v] = index;
    index++;
    S.push_back(v);
    onStack[v] = true;
    for (int e = 0; e < V[v].m_edges.size(); e++) {
        int w = V[v].m_edges[e].m_destinationHandle;
        if (indexMap[w] == -1) {
            strongConnect(V, w, index, S, SCCs, indexMap, lowLinkMap, onStack);
            lowLinkMap[v] = std::min(lowLinkMap[v], lowLinkMap[w]);
        } else if (onStack[w]) {
            lowLinkMap[v] = std::min(lowLinkMap[v], indexMap[w]);
        }
    }
    if (lowLinkMap[v] == indexMap[v]) {
        std::vector<int> SCC;
        while (!S.empty()) {
            int w = S.back();
            S.pop_back();
            onStack[w] = false;
            SCC.push_back(w);
            if (w == v) break;
        }
        SCCs.push_back(SCC);
    }
}