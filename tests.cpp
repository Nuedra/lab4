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

void test_contains_vertex() {
    DirectedGraph<std::string, int> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");

    assert(graph.contains_vertex("A"));
    assert(graph.contains_vertex("B"));
    assert(!graph.contains_vertex("C"));

    std::cout << "test_contains_vertex() passed!\n";
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

void test_contains_edge() {
    DirectedGraph<std::string, int> graph;
    graph.add_edge("A", "B", 5);

    assert(graph.contains_edge("A", "B"));
    assert(!graph.contains_edge("B", "A"));
    assert(!graph.contains_edge("A", "C"));

    std::cout << "test_contains_edge() passed!\n";
}

void test_get_edge_weight() {
    DirectedGraph<std::string, int> graph;
    graph.add_edge("A", "B", 5);

    assert(graph.get_edge_weight("A", "B") == 5);

    bool exception_thrown = false;
    try {
        [[maybe_unused]] int w = graph.get_edge_weight("B", "A");
    }
    catch (const std::out_of_range&) {
        exception_thrown = true;
    }
    assert(exception_thrown && "Expected std::out_of_range when getting weight for non-existent edge");

    graph.add_edge("A", "B", 10);
    assert(graph.get_edge_weight("A", "B") == 10);

    std::cout << "test_get_edge_weight() passed!\n";
}

void test_remove_edge() {
    DirectedGraph<std::string, int> graph;
    graph.add_edge("A", "B", 5);
    graph.add_edge("B", "C", 3);

    graph.remove_edge("A", "B");
    assert(graph.contains_vertex("A"));
    assert(graph.contains_vertex("B"));
    assert(!graph.contains_edge("A", "B"));

    assert(!graph.contains_edge("A", "C"));
    graph.remove_edge("A", "C");
    assert(graph.contains_edge("B", "C"));

    std::cout << "test_remove_edge() passed!\n";
}