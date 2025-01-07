#ifndef LAB4_CSV_ACTIONS_HPP
#define LAB4_CSV_ACTIONS_HPP

#include <string>
#include "../DirectedGraph.hpp"
#include <fstream>
#include <stdexcept>

int generate_random_int(int min, int max);
double random_double(double min_val, double max_val);
void generate_and_write_random_graph_to_csv(const std::string& filename, int number_of_vertices, double edge_probability,
                                            int min_weight, int max_weight);
DirectedGraph<std::string, int> read_csv(const std::string& filename);

template <typename TVertex, typename TWeight>
void to_dot(DirectedGraph<TVertex, TWeight> graph, std::string& dot_filename) {
    {
        const std::string csv_ext = ".csv";
        const std::string dot_ext = ".dot";
        dot_filename.replace(dot_filename.size() - csv_ext.size(), csv_ext.size(), dot_ext);
    }

    std::ofstream dot_file(dot_filename);
    if (!dot_file.is_open()) {
        throw std::runtime_error("Error creating dot file: " + dot_filename);
    }
    dot_file << "digraph G {\n";
    // печатает только вершины
    {
        ArraySequence<TVertex> verts = graph.get_vertices();
        for (int i = 0; i < verts.get_length(); i++) {
            dot_file << "  " << verts.get(i) << ";\n";
        }
    }

    {
        ArraySequence<TVertex> verts = graph.get_vertices();
        for (int i = 0; i < verts.get_length(); i++) {
            const TVertex& src = verts.get(i);
            auto edges = graph.get_outgoing_edges(src);
            for (int j = 0; j < edges.get_length(); j++) {
                auto& pair_vertex_weight = edges.get(j);

                TVertex tgt = pair_vertex_weight.value1;
                TWeight w = pair_vertex_weight.value2;

                dot_file << "  " << src << " -> " << tgt << " [label=\"" << w << "\"];\n";
            }
        }
    }

    dot_file << "}\n";
    dot_file.close();
}

#endif //LAB4_CSV_ACTIONS_HPP
