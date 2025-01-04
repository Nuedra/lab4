#include "tests.hpp"

#include <cassert>
#include <iostream>
#include <string>
#include "DirectedGraph.hpp"

void test_add_vertex() {
    DirectedGraph<std::string, int> graph;

    assert(!graph.contains_vertex("A"));

    graph.add_vertex("A");
    assert(graph.contains_vertex("A"));

    graph.add_vertex("A");
    assert(graph.contains_vertex("A"));

    std::cout << "test_add_vertex() passed!\n";
}

void test_remove_vertex() {
    DirectedGraph<std::string, int> graph;

    graph.add_vertex("A");
    graph.add_vertex("B");
    assert(graph.contains_vertex("A"));
    assert(graph.contains_vertex("B"));

    graph.remove_vertex("A");
    assert(!graph.contains_vertex("A"));
    assert(graph.contains_vertex("B"));

    graph.remove_vertex("Z");
    assert(graph.contains_vertex("B"));

    std::cout << "test_remove_vertex() passed!\n";
}

void test_add_edge() {
    DirectedGraph<std::string, int> graph;

    graph.add_edge("A", "B", 5);
    assert(graph.contains_vertex("A"));
    assert(graph.contains_vertex("B"));
    assert(graph.contains_edge("A", "B"));
    assert(graph.get_edge_weight("A", "B") == 5);

    graph.add_edge("A", "B", 10);
    assert(graph.get_edge_weight("A", "B") == 10);

    graph.add_edge("A", "C", 7);
    assert(graph.contains_vertex("C"));
    assert(graph.contains_edge("A", "C"));
    assert(graph.get_edge_weight("A", "C") == 7);

    std::cout << "test_add_edge() passed!\n";
}