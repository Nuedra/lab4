#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>
#include "tests.hpp"
#include "DirectedGraph.hpp"
#include "PriorityQueue.hpp"
#include "dijkstra_algorithm.hpp"
#include "limits.hpp"

void test_add_vertex() {
    DirectedGraph<std::string, int> graph;

    assert(!graph.contains_vertex("A"));

    graph.add_vertex("A");
    assert(graph.contains_vertex("A"));

    graph.add_vertex("A");
    assert(graph.contains_vertex("A"));
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
        auto verts = graph.get_vertices();
        assert(verts.get_length() == 0);
    }

    graph.add_vertex("A");
    {
        auto verts = graph.get_vertices();
        assert(verts.get_length() == 1);

        bool has_a = false;
        for (int i = 0; i < verts.get_length(); i++) {
            if (verts.get(i) == "A") {
                has_a = true;
                break;
            }
        }
        assert(has_a);
    }

    graph.add_vertex("B");
    {
        auto verts = graph.get_vertices();
        assert(verts.get_length() == 2);

        bool has_a = false;
        bool has_b = false;
        for (int i = 0; i < verts.get_length(); i++) {
            const std::string& v = verts.get(i);
            if (v == "A") has_a = true;
            if (v == "B") has_b = true;
        }
        assert(has_a && has_b);
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
}

void test_enqueue_dequeue() {
    PriorityQueue<std::string, int> pq;

    bool exception_thrown = false;
    try {
        pq.dequeue();
    }
    catch (const std::out_of_range&) {
        exception_thrown = true;
    }
    assert(exception_thrown);

    pq.enqueue("low", 1);
    pq.enqueue("medium", 5);
    pq.enqueue("urgent", 10);
    pq.enqueue("equal_medium", 5);

    assert(pq.dequeue() == "urgent");

    std::string second = pq.dequeue();
    std::string third  = pq.dequeue();
    assert(
            (second == "medium" && third == "equal_medium") ||
            (second == "equal_medium" && third == "medium")
    );

    std::string fourth = pq.dequeue();
    assert(fourth == "low");

    exception_thrown = false;
    try {
        pq.dequeue();
    }
    catch (const std::out_of_range&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void test_peek_methods() {
    PriorityQueue<int, int> pq;

    pq.enqueue(11, 5);
    pq.enqueue(22, 8);
    pq.enqueue(33, 8);
    pq.enqueue(44, 10);

    assert(pq.peek_first() == 44);

    assert(pq.peek_last() == 11);

    assert(pq.peek(0) == 44);
    assert(pq.peek(3) == 11);

    bool exception_thrown = false;
    try {
        pq.peek(99); //  такого индекса нет
    }
    catch (const std::out_of_range&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void test_hidden_methods() {
    PriorityQueue<int,int> pq;
    Sequence<int>& seq_ref = pq; // ссылка на базовый класс

    bool exception_thrown = false;
    try {
        (void)seq_ref.get_first(); // принудительно вызываем
    }
    catch (const std::logic_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);

    exception_thrown = false;
    try {
        seq_ref.insert_at(123, 0);
    }
    catch (const std::logic_error&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void test_dijkstra() {
    {
        DirectedGraph<std::string, double> graph;

        bool exception_thrown = false;
        try {
            auto dist = dijkstra_shortest_paths<std::string, double>(graph, "A");
        }
        catch (const std::invalid_argument&) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    }

    {
        DirectedGraph<std::string, double> graph;
        graph.add_vertex("A");

        auto dist = dijkstra_shortest_paths<std::string, double>(graph, "A");

        auto verts = graph.get_vertices();
        assert(verts.get_length() == 1);
        assert(verts.get(0) == "A");

        assert(dist.get_length() == 1);
        assert(dist.get(0) == 0.0);
    }

    {
        DirectedGraph<std::string, double> graph;
        graph.add_vertex("A");
        graph.add_vertex("B");

        auto dist = dijkstra_shortest_paths<std::string, double>(graph, "A");
        auto verts = graph.get_vertices();
        assert(verts.get_length() == 2);

        int idx_a = -1, idx_b = -1;
        for (int i = 0; i < verts.get_length(); i++) {
            if (verts.get(i) == "A") idx_a = i;
            if (verts.get(i) == "B") idx_b = i;
        }

        static const double INF = custom_limits<double>::max();
        assert(dist.get(idx_a) == 0.0);
        assert(dist.get(idx_b) == INF);
    }

    {
        DirectedGraph<std::string, double> graph;
        graph.add_edge("A", "B", 2.5);

        auto dist = dijkstra_shortest_paths<std::string, double>(graph, "A");
        auto verts = graph.get_vertices();
        assert(verts.get_length() == 2);

        int idx_a = -1, idx_b = -1;
        for (int i = 0; i < verts.get_length(); i++) {
            if (verts.get(i) == "A") idx_a = i;
            if (verts.get(i) == "B") idx_b = i;
        }

        assert(dist.get(idx_a) == 0.0);
        assert(dist.get(idx_b) == 2.5);

        auto distB = dijkstra_shortest_paths<std::string, double>(graph, "B");
        static const double INF = custom_limits<double>::max();
        assert(distB.get(idx_b) == 0.0);
        assert(distB.get(idx_a) == INF);
    }

    {
        DirectedGraph<std::string, int> graph;
        graph.add_edge("A", "B", 5);
        graph.add_edge("A", "C", 10);
        graph.add_edge("B", "C", 2);

        auto dist = dijkstra_shortest_paths<std::string, int>(graph, "A");

        auto verts = graph.get_vertices();
        assert(verts.get_length() == 3);

        int idx_a = -1, idx_b = -1, idx_c = -1;
        for (int i = 0; i < verts.get_length(); i++) {
            if (verts.get(i) == "A") idx_a = i;
            if (verts.get(i) == "B") idx_b = i;
            if (verts.get(i) == "C") idx_c = i;
        }

        assert(dist.get(idx_a) == 0);
        assert(dist.get(idx_b) == 5);
        assert(dist.get(idx_c) == 7);
    }

    {
        DirectedGraph<std::string, Pair<int, int>> graph;
        graph.add_edge("A", "B", Pair<int,int>(2, 3));
        graph.add_edge("A", "C", Pair<int,int>(1, 1));
        graph.add_edge("B", "C", Pair<int,int>(1, 2));

        auto dist = dijkstra_shortest_paths<std::string, Pair<int,int>>(graph, "A");

        auto verts = graph.get_vertices();
        assert(verts.get_length() == 3);

        int idx_a = -1, idx_b = -1, idx_c = -1;
        for (int i = 0; i < verts.get_length(); i++) {
            if (verts.get(i) == "A") idx_a = i;
            if (verts.get(i) == "B") idx_b = i;
            if (verts.get(i) == "C") idx_c = i;
        }

        assert((dist.get(idx_a) == Pair<int,int>(0, 0)));
        assert((dist.get(idx_b) == Pair<int,int>(2, 3)));
        assert((dist.get(idx_c) == Pair<int,int>(1, 1)));
    }
}

void start_tests() {
    test_add_vertex();
    test_remove_vertex();
    test_add_edge();
    test_remove_edge();
    test_get_vertices();
    test_get_outgoing_edges();
    test_enqueue_dequeue();
    test_peek_methods();
    test_hidden_methods();
    test_dijkstra();

    std::cout << "All tests are passed!\n";
}