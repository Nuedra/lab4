#include "tests.hpp"
#include "DirectedGraph.hpp"
#include "iostream"

template<typename TVertex, typename TWeight>
void print_graph(const IGraph<TVertex, TWeight>& graph) {
    std::cout << "Directed Graph contents:\n";

    auto vertices = graph.get_vertices();
    for (size_t i = 0; i < vertices.get_length(); i++) {
        const TVertex& v = vertices.get(i);
        std::cout << "Vertex [" << v << "]:\n";

        auto edges = graph.get_outgoing_edges(v);
        for (size_t j = 0; j < edges.get_length(); j++) {
            const auto& pair_vertex_edge = edges.get(j);
            std::cout << "   -> " << pair_vertex_edge.value1 << " (weight = "
            << pair_vertex_edge.value2 << ")\n";
        }
    }

    std::cout << std::endl;
}

int main() {
    start_tests();
    DirectedGraph<std::string, int> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_edge("A", "B", 5);
    graph.add_edge("B", "A", 2);

    print_graph(graph);

    return 0;
}
