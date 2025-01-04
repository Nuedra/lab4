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