#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "graph.hpp"

using namespace cs251;

void graph::read_edge_weights(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> num_vertices >> num_edges;
        m_vertices.resize(num_vertices);
        for (int i = 0; i < num_vertices; ++i) {
            m_vertices[i].m_handle = i;
        }
    }
    int source;
    int destination;
    int weight;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> source >> destination;
        if (!(iss >> weight)) {
            graph_edge edge = {1, destination, NONE};
            m_vertices[source].m_edges.push_back(edge);
        } else {
            graph_edge edge = {weight, destination, NONE};
            m_vertices[source].m_edges.push_back(edge);
        }        
    }
    file.close();
}

void graph::read_edge_colors(const std::string& filePath) {
    std::ifstream file(filePath);
    file >> num_vertices >> num_edges;
    m_vertices.resize(num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        m_vertices[i].m_handle = i;
    }
    int source;
    int destination;
    int weight;
    char color;
    for (int i = 0; i < num_edges; ++i) {
        file >> source >> destination >> weight >> color;
        graph_edge edge = {weight, destination, static_cast<cs251::color>(color)};
        m_vertices[source].m_edges.push_back(edge);
    }
    file.close();
}

std::vector<graph_vertex> graph::get_vertices() const {
    return m_vertices;    
}