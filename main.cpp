#include "tests.hpp"
#include "DirectedGraph.hpp"
#include "iostream"
#include "graph_algorithms.hpp"

int read_int_in_range(const char* prompt, int min_val, int max_val) {
    while (true) {
        std::cout << prompt;

        int value = 0;
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод, попробуйте снова.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (value < min_val || value > max_val) {
            std::cout << "Значение должно быть в диапазоне ["
                      << min_val << ", " << max_val << "]. Попробуйте снова.\n";
            continue;
        }

        return value;
    }
}

template<typename TVertex, typename TWeight>
void print_graph(const IGraph<TVertex, TWeight>& graph) {
    std::cout << "Directed Graph contents:\n";

    auto verts = graph.get_vertices();
    for (size_t i = 0; i < verts.get_length(); i++) {
        const TVertex& v = verts.get(i);
        std::cout << "Vertex [" << v << "]:\n";

        auto edges = graph.get_outgoing_edges(v);
        for (size_t j = 0; j < edges.get_length(); j++) {
            const auto& pair_vertex_edge = edges.get(j);
            std::cout << "   -> " << pair_vertex_edge.value1 << " (weight = " << pair_vertex_edge.value2 << ")\n";
        }
    }

    std::cout << std::endl;
}

int main() {
    start_tests();
    DirectedGraph<std::string, double> graph;

    graph.add_edge("A", "B", 2.0);
    graph.add_edge("A", "C", 5.0);
    graph.add_edge("B", "C", 1.5);
    graph.add_edge("B", "D", 6.0);
    graph.add_edge("C", "D", 1.0);

    auto dist = dijkstra_shortest_paths<std::string, double>(graph, "A");
    auto verts = graph.get_vertices();

    for (int i = 0; i < verts.get_length(); i++) {
        std::cout << "Distance A -> " << verts.get(i) << " = " << dist.get(i) << std::endl;
    }

    return 0;
}
