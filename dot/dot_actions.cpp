#include "dot_actions.hpp"
#include <fstream>
#include <random>
#include <string>
#include <iostream>

int generate_random_int(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

double random_double(double min_val, double max_val) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(min_val, max_val);
    return dist(gen);
}

void generate_and_write_random_graph_to_dot(const std::string& filename, int number_of_vertices, double edge_probability,
                                            int min_weight, int max_weight) {
    std::ofstream dot_file(filename);
    if (!dot_file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    dot_file << "digraph G {" << std::endl;

    for (int i = 0; i < number_of_vertices; i++) {
        dot_file << "  \"" << i << "\";" << std::endl;
    }

    for (int i = 0; i < number_of_vertices; i++) {
        for (int j = 0; j < number_of_vertices; j++) {
            if (i == j) {
                continue; // не делаем петли i->i
            }

            double prob = random_double(0.0, 1.0);
            if (prob <= edge_probability) {
                int weight = generate_random_int(min_weight, max_weight);
                dot_file << "  \"" << i << "\" -> \"" << j << "\" [weight=\"" << weight << "\"];" << std::endl;
            }

        }
    }

    dot_file << "}" << std::endl;
    dot_file.close();
}

DirectedGraph<std::string, int> read_dot(const std::string& filename) {
    DirectedGraph<std::string, int> graph;

    std::ifstream dot_file(filename);
    if (!dot_file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    while (std::getline(dot_file, line)) {
        if (line.find("->") == std::string::npos) {
            continue;
        }

        size_t arrow_pos = line.find("->");
        size_t label_pos = line.find("[label=\"");
        size_t end_label_pos = line.find("\"]", label_pos);

        if (arrow_pos == std::string::npos || label_pos == std::string::npos || end_label_pos == std::string::npos) {
            continue;
        }

        std::string source = line.substr(1, arrow_pos - 2); // Узел-источник
        std::string target = line.substr(arrow_pos + 4, label_pos - arrow_pos - 6); // Узел-приёмник
        std::string weight_str = line.substr(label_pos + 8, end_label_pos - label_pos - 8); // Вес ребра

        int weight = std::stoi(weight_str);

        graph.add_edge(source, target, weight);
    }

    dot_file.close();
    return graph;
}