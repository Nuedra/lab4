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