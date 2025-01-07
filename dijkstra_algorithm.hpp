#ifndef LAB4_DIJKSTRA_ALGORITHM_HPP
#define LAB4_DIJKSTRA_ALGORITHM_HPP

#include <stdexcept>
#include "DirectedGraph.hpp"
#include "PriorityQueue.hpp"
#include "data_structures/ArraySequence.h"
#include "limits.hpp"

template<typename TVertex, typename TWeight>
ArraySequence<TWeight> dijkstra_shortest_paths(const DirectedGraph<TVertex, TWeight>& graph, const TVertex& start) {
    ArraySequence<TVertex> vertices = graph.get_vertices();
    int n = vertices.get_length();

    int start_index = -1;
    for (int i = 0; i < n; i++) {
        if (vertices.get(i) == start) {
            start_index = i;
            break;
        }
    }
    if (start_index == -1) {
        throw std::invalid_argument("Start vertex not found in the graph");
    }

    static const TWeight INF = custom_limits<TWeight>::max();

    ArraySequence<TWeight> dist;
    dist.reserve(n);
    for (int i = 0; i < n; i++) {
        dist.append(INF);
    }
    dist.set(start_index, (TWeight)0); // расстояние до стартовой вершины = 0

    ArraySequence<bool> visited;
    visited.reserve(n);
    for (int i = 0; i < n; i++) {
        visited.append(false);
    }

    PriorityQueue<int, TWeight> pq;
    pq.enqueue(start_index, -(dist.get(start_index))); // со знаком минус, чтобы меньшее расстояние было вверху очереди

    while (true) {
        int u;
        bool empty = false;
        try {
            u = pq.dequeue();
        }
        catch (const std::out_of_range&) {
            empty = true;
        }
        if (empty) {
            break;
        }

        if (visited.get(u)) {
            continue;
        }
        visited.set(u, true);

        auto edges = graph.get_outgoing_edges(vertices.get(u));
        for (int i_edge = 0; i_edge < edges.get_length(); i_edge++) {
            auto edge = edges.get(i_edge);

            TVertex neighbor = edge.value1;
            TWeight w = edge.value2;
            int v = -1;
            for (int j = 0; j < n; j++) {
                if (vertices.get(j) == neighbor) {
                    v = j;
                    break;
                }
            }

            if (v == -1 || visited.get(v)) {
                continue;
            }

            TWeight old_dist = dist.get(v);
            TWeight new_dist = dist.get(u) + w; // если w >= 0

            if (new_dist < old_dist) {
                dist.set(v, new_dist);
                pq.enqueue(v, -new_dist);
            }
        }
    }

    return dist;
}

#endif //LAB4_DIJKSTRA_ALGORITHM_HPP
