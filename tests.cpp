#include "tests.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include "pair/Pair.hpp"
#include "DirectedGraph.hpp"

void test_add_vertex() {
    DirectedGraph<std::string, int> graph;

    assert(!graph.contains_vertex("A"));

    graph.add_vertex("A");
    assert(graph.contains_vertex("A"));

    graph.add_vertex("A");
    assert(graph.contains_vertex("A"));
}

void test_contains_vertex() {
    DirectedGraph<std::string, int> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");

    assert(graph.contains_vertex("A"));
    assert(graph.contains_vertex("B"));
    assert(!graph.contains_vertex("C"));
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
}

void test_contains_edge() {
    DirectedGraph<std::string, int> graph;
    graph.add_edge("A", "B", 5);

    assert(graph.contains_edge("A", "B"));
    assert(!graph.contains_edge("B", "A"));
    assert(!graph.contains_edge("A", "C"));
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
    assert(exception_thrown);

    graph.add_edge("A", "B", 10);
    assert(graph.get_edge_weight("A", "B") == 10);
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
}

void test_get_vertices() {
    DirectedGraph<std::string, int> graph;

    {
        auto vertices = graph.get_vertices();
        assert(vertices.get_length() == 0);
    }

    graph.add_vertex("A");
    {
        auto vertices = graph.get_vertices();
        assert(vertices.get_length() == 1);

        bool has_a = false;
        for (int i = 0; i < vertices.get_length(); i++) {
            if (vertices.get(i) == "A") {
                has_a = true;
                break;
            }
        }
        assert(has_a);
    }

    graph.add_vertex("B");
    {
        auto vertices = graph.get_vertices();
        assert(vertices.get_length() == 2);

        bool has_a = false;
        bool has_b = false;
        for (int i = 0; i < vertices.get_length(); i++) {
            const std::string& v = vertices.get(i);
            if (v == "A") has_a = true;
            if (v == "B") has_b = true;
        }
        assert(has_a && has_b);
    }

    graph.add_edge("A", "B", 5);
    {
        auto vertices = graph.get_vertices();
        assert(vertices.get_length() == 2);
    }
}


void test_get_outgoing_edges() {
    DirectedGraph<std::string, int> graph;

    {
        auto edgesX = graph.get_outgoing_edges("X");
        assert(edgesX.get_length() == 0);
    }

    graph.add_vertex("A");
    {
        auto edgesA = graph.get_outgoing_edges("A");
        assert(edgesA.get_length() == 0);
    }

    graph.add_edge("A", "B", 5);
    {
        auto edgesA = graph.get_outgoing_edges("A");
        assert(edgesA.get_length() == 1);

        const auto& first_Pair = edgesA.get(0);
        assert(first_Pair.value1 == "B");
        assert(first_Pair.value2 == 5);

        auto edgesB = graph.get_outgoing_edges("B");
        assert(edgesB.get_length() == 0);
    }

    graph.add_edge("B", "A", 10);
    {
        {
            auto edgesA = graph.get_outgoing_edges("A");
            assert(edgesA.get_length() == 1);
            const auto& pair_a0 = edgesA.get(0);
            assert(pair_a0.value1 == "B");
            assert(pair_a0.value2 == 5);
        }

        {
            auto edgesB = graph.get_outgoing_edges("B");
            assert(edgesB.get_length() == 1);
            const auto& pair_b0 = edgesB.get(0);
            assert(pair_b0.value1 == "A");
            assert(pair_b0.value2 == 10);
        }
    }

    graph.add_edge("A", "C", 7);
    {
        auto edgesA = graph.get_outgoing_edges("A");
        assert(edgesA.get_length() == 2);

        bool fount_b5 = false;
        bool fount_c7 = false;
        for (int i = 0; i < edgesA.get_length(); i++) {
            const auto& p = edgesA.get(i);
            if (p.value1 == "B" && p.value2 == 5) {
                fount_b5 = true;
            }
            if (p.value1 == "C" && p.value2 == 7) {
                fount_c7 = true;
            }
        }
        assert(fount_b5 && fount_c7);
    }
}


void start_tests() {
    test_add_vertex();
    test_remove_vertex();
    test_add_edge();
    test_contains_vertex();
    test_contains_edge();
    test_get_edge_weight();
    test_remove_edge();
    test_get_vertices();
    test_get_outgoing_edges();

    std::cout << "All tests are passed!\n";
}