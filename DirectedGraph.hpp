#ifndef LAB4_DIRECTEDGRAPH_HPP
#define LAB4_DIRECTEDGRAPH_HPP

#include <iostream>
#include "IGraph.hpp"
#include "data_structures/HashTable.hpp"

template <typename TVertex, typename TWeight>
class DirectedGraph : public IGraph<TVertex, TWeight> {
public:
    DirectedGraph() = default;
    ~DirectedGraph() override = default;

    void add_vertex(const TVertex& vertex) override {
        if (!adjacency_list_.contains_key(vertex)) {
            HashTable<TVertex, TWeight> empty_table;
            adjacency_list_.add(vertex, empty_table);
        }
    }

    bool contains_vertex(const TVertex& vertex) const override {
        return adjacency_list_.contains_key(vertex);
    }

    void remove_vertex(const TVertex& vertex) override {

    }

    void add_edge(const TVertex& from, const TVertex& to, const TWeight& weight) override {

    }

    void remove_edge(const TVertex& from, const TVertex& to) override {

    }

    bool contains_edge(const TVertex& from, const TVertex& to) const override {

    }

    TWeight get_edge_weight(const TVertex& from, const TVertex& to) const override {

    }

    void print_graph() const override {

    }

private:
    //структура: вершина -> (HashTable из соседей -> вес дуги)
    HashTable<TVertex, HashTable<TVertex, TWeight>> adjacency_list_;
};

#endif //LAB4_DIRECTEDGRAPH_HPP
