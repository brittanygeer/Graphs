#include "max_height.hpp"
#include <climits>

using namespace cs251;

int max_height::calculate(const graph& g) {
    std::vector<graph_vertex> vertices = g.get_vertices();
	std::vector<graph_edge> edgeTo(vertices.size());
    std::vector<int> distTo(vertices.size());
    std::vector<bool> visited(vertices.size());
    max_height Q;    
    for (size_t i = 0; i < vertices.size(); ++i) {
        distTo[vertices[i].m_handle] = 0; 
        visited[vertices[i].m_handle] = false;
    }
    graph_vertex s = vertices[0];
    distTo[s.m_handle] = 0;
    Q.push(std::make_pair(0, s));
    while (!Q.empty()) {
        graph_vertex u = Q.pop();
        visited[u.m_handle] = true;
        for (size_t j = 0; j < u.m_edges.size(); j++) {
            if (visited[u.m_edges[j].m_destinationHandle]) {
                continue;    
            }
            if (u.m_edges[j].m_weight > distTo[u.m_edges[j].m_destinationHandle]) {
                graph_vertex v = vertices[u.m_edges[j].m_destinationHandle];
                edgeTo[v.m_handle] = u.m_edges[j];
                distTo[v.m_handle] = u.m_edges[j].m_weight;
                bool found = false;
                max_height tempQ = Q;
                while (!tempQ.empty()) {
                    if (tempQ.top().second.m_handle == v.m_handle) {
                        found = true;
                        break;
                    }
                    tempQ.pop();
                }
                if (found) {
                    max_height tempQ2;
                    while (!Q.empty()) {
                        if (Q.top().second.m_handle != v.m_handle) {
                            tempQ2.push(Q.top());
                        } else {
                            tempQ2.push(std::make_pair(distTo[v.m_handle], v));    
                        }
                        Q.pop();
                    }
                    while (!tempQ2.empty()) {
                        Q.push(tempQ2.top());
                        tempQ2.pop();
                    }                    
                } else {
                    Q.push(std::make_pair(distTo[v.m_handle], v));     
                }
            }
        }
    }
    int minDist = INT_MAX;
    for (int i = 1; i < distTo.size(); i++) {
        if (distTo[i] < minDist) {
            minDist = distTo[i];    
        }
    }
    return minDist;
}

void max_height::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap[parentIndex].first < heap[index].first) {
            std::swap(heap[parentIndex], heap[index]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

void max_height::heapifyDown(int index) {
    int n = heap.size();
    while (2 * index + 1 < n) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int maxIndex = index;
        if (leftChild < n && heap[leftChild].first > heap[maxIndex].first) {
            maxIndex = leftChild;
        }
        if (rightChild < n && heap[rightChild].first > heap[maxIndex].first) {
            maxIndex = rightChild;
        }
        if (maxIndex != index) {
            std::swap(heap[index], heap[maxIndex]);
            index = maxIndex;
        } else {
            break;
        }
    }
}

void max_height::push(std::pair<int, graph_vertex> node) {
    heap.push_back({node.first, node.second});
    heapifyUp(heap.size() - 1);
}

graph_vertex max_height::pop() {
    if (!heap.empty()) {
        graph_vertex topElement = heap.front().second;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return topElement;
    }
}

bool max_height::empty() {
    return heap.empty();
}

std::pair<int, graph_vertex> max_height::top() {
    if (!heap.empty()) {
        return heap.front();
    }
}