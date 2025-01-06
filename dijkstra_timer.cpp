#include "dijkstra_timer.hpp"
#include <chrono>
#include <string>
#include <iostream>
#include "DirectedGraph.hpp"
#include "dijkstra_algorithm.hpp"
#include "data_structures/ArraySequence.h"
#include <fstream>
#include "csv/csv_actions.hpp"

void measure_and_save_dijkstra_times(const std::string& csv_filename, int step, double edge_probability, int min_weight,
                                     int max_weight) {
    std::ofstream csv_file(csv_filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open file: " << csv_filename << std::endl;
        return;
    }
    csv_file << "Vertices,Time_ms\n";

    std::string graph_file = "../csv/random_graph.csv";

    for (int size = step; size <= step * 10; size += step) {
        generate_and_write_random_graph_to_csv(graph_file, size, 0.3, 1,
                                               10);

        DirectedGraph<std::string, int> graph;
        graph = read_csv(graph_file);

        ArraySequence<int> dist_out;
        auto start_time = std::chrono::high_resolution_clock::now();

        dist_out = dijkstra_shortest_paths<std::string, int>(graph, "0");

        auto end_time = std::chrono::high_resolution_clock::now();
        long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

        csv_file << size << "," << duration << "\n";

        std::cout << "Dijkstra on graph with " << size << " vertices took " << duration << " ms.\n";
    }

    csv_file.close();
}


