#include "color_walk.hpp"
#include <climits>

using namespace cs251;

std::vector<std::pair<char, int>> color_walk::calculate(const graph& g, const handle startHandle) {
    std::vector<graph_vertex> vertices = g.get_vertices();
    std::vector<int> dist(vertices.size(), INT_MAX);
    std::vector<int> prev(vertices.size(), -1);
    std::vector<char> colors = {'R', 'G', 'B'};
    std::vector<std::pair<char, int>> result(vertices.size(), std::make_pair('-', -1));
    for (char startColor : colors) {
        std::vector<std::pair<graph_vertex, graph_edge>> dfsStack;
        graph_edge startEdge = {0, 0, static_cast<cs251::color>('-')};
        dfsStack.push_back(std::make_pair(vertices[startHandle], startEdge));
        dist[startHandle] = 0;      
        while (!dfsStack.empty()) {
            graph_vertex u = dfsStack.back().first;
            graph_edge prevEdge = dfsStack.back().second;
            char currentColor = (prevEdge.col == 'R') ? 'G' : (prevEdge.col == 'G') ? 'B' : (prevEdge.col == 'B') ? 'R' : startColor;
            bool exploringEdges = false;
            graph_vertex v;
            for (const graph_edge& edge : u.m_edges) {
                v = vertices[edge.m_destinationHandle];
                char edgeColor = edge.col;
                bool visitedEdge = false;
                for (std::pair<graph_vertex, graph_edge> pair : dfsStack) {
                    if (pair.second.col == edge.col && pair.second.m_weight == edge.m_weight && pair.second.m_destinationHandle == edge.m_destinationHandle) {
                        visitedEdge = true;    
                    }
                }
                if (edgeColor == currentColor && (dist[v.m_handle] > dist[u.m_handle] + edge.m_weight /*|| dist[v.m_handle] == 0*/) && !visitedEdge) {
                    dist[v.m_handle] = dist[u.m_handle] + edge.m_weight;
                    prev[v.m_handle] = u.m_handle;
                    dfsStack.push_back(std::make_pair(v, edge));
                    exploringEdges = true; 
                    break;
                }
            }
            if (!exploringEdges) {
                if (dist[v.m_handle] != INT_MAX && (result[v.m_handle].second == -1 || dist[v.m_handle] < result[v.m_handle].second)) {
                    result[v.m_handle] = std::make_pair(startColor, dist[v.m_handle]);
                } 
                dfsStack.pop_back();
            }
        }      
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (dist[i] != INT_MAX && (result[i].second == -1 || dist[i] < result[i].second)) {
                result[i] = std::make_pair(startColor, dist[i]);
            }
        }       
        result[startHandle] = std::make_pair('-', 0);
    }
    return result;
}