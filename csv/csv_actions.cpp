#include <fstream>
#include <random>
#include <string>
#include <iostream>
#include <sstream>
#include "csv_actions.hpp"

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

void generate_and_write_random_graph_to_csv(const std::string& filename, int number_of_vertices, double edge_probability,
                                            int min_weight, int max_weight) {
    std::ofstream dot_file(filename);
    if (!dot_file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    dot_file << "source,target,weight\n";

    for(int i = 0; i < number_of_vertices; i++){
        dot_file << i << "\n";
    }

    for (int i = 0; i < number_of_vertices; i++) {
        for (int j = 0; j < number_of_vertices; j++) {
            if (i == j) {
                continue; // не делаем петли i->i
            }

            double prob = random_double(0.0, 1.0);
            if (prob <= edge_probability) {
                int w = generate_random_int(min_weight, max_weight);
                dot_file << i << "," << j << "," << w << "\n";
            }
        }
    }

    dot_file.close();
}

DirectedGraph<std::string, int> read_csv(const std::string& filename) {
    DirectedGraph<std::string, int> graph;

    std::ifstream dot_file(filename);
    if (!dot_file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    if (!std::getline(dot_file, line)) {
        throw std::runtime_error("CSV file is empty: " + filename);
    }

    while (std::getline(dot_file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream stream(line);
        std::string source_str, target_str, weight_str;

        std::getline(stream, source_str, ',');
        std::getline(stream, target_str, ',');
        std::getline(stream, weight_str, ',');

        if (weight_str.empty()) {
            continue;
        }

        int weight_val = std::stoi(weight_str);

        graph.add_edge(source_str, target_str, weight_val);
    }

    dot_file.close();
    return graph;
}


