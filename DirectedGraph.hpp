#ifndef LAB4_DIRECTEDGRAPH_HPP
#define LAB4_DIRECTEDGRAPH_HPP

#include "IGraph.hpp"
#include "data_structures/HashTable.hpp"
#include "data_structures/ArraySequence.h"
#include "pair/Pair.hpp"

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
        if (!adjacency_list_.contains_key(vertex)) {
            return;
        }

        adjacency_list_.remove(vertex);

        auto it_main = adjacency_list_.get_iterator();
        auto kvp = it_main.get_current_item();

        while (it_main.try_get_current_item(kvp)) {
            HashTable<TVertex, TWeight> neighbors = kvp.value;

            if (neighbors.contains_key(vertex)) {
                neighbors.remove(vertex);
                adjacency_list_.add(kvp.key, neighbors);
            }

            it_main.next();
        }
    }

    void add_edge(const TVertex& from, const TVertex& to, const TWeight& weight) override {
        if (!adjacency_list_.contains_key(from)) {
            add_vertex(from);
        }
        if (!adjacency_list_.contains_key(to)) {
            add_vertex(to);
        }

        HashTable<TVertex, TWeight> from_neighbors = adjacency_list_.get(from);
        from_neighbors.add(to, weight);
        adjacency_list_.add(from, from_neighbors);
    }

    bool contains_edge(const TVertex& from, const TVertex& to) const override {
        if (!adjacency_list_.contains_key(from)) {
            return false;
        }

        const HashTable<TVertex, TWeight>& from_neighbors = adjacency_list_.get(from);
        return from_neighbors.contains_key(to);
    }

    TWeight get_edge_weight(const TVertex& from, const TVertex& to) const override {
        if (!adjacency_list_.contains_key(from)) {
            throw std::out_of_range("vertex 'from' not found");
        }

        const HashTable<TVertex, TWeight>& from_neighbors = adjacency_list_.get(from);
        if (!from_neighbors.contains_key(to)) {
            throw std::out_of_range("Edge not found.");
        }
        return from_neighbors.get(to);
    }

    void remove_edge(const TVertex& from, const TVertex& to) override {
        if (!adjacency_list_.contains_key(from)) {
            return;
        }

        HashTable<TVertex, TWeight> from_neighbors = adjacency_list_.get(from);

        if (from_neighbors.contains_key(to)) {
            from_neighbors.remove(to);
            adjacency_list_.add(from, from_neighbors);
        }
    }

    ArraySequence<TVertex> get_vertices() const override {
        ArraySequence<TVertex> result;
        result.reserve(adjacency_list_.get_count());

        auto it_main = adjacency_list_.get_iterator();
        KeyValuePair<TVertex, HashTable<TVertex, TWeight>> kvp;

        while (it_main.try_get_current_item(kvp)) {
            result.append(kvp.key);
            it_main.next();
        }

        return result;
    }

    ArraySequence<Pair<TVertex, TWeight>>
    get_outgoing_edges(const TVertex& vertex) const override
    {
        ArraySequence<Pair<TVertex, TWeight>> edges;
        if (!adjacency_list_.contains_key(vertex)) {
            return edges;
        }

        const HashTable<TVertex, TWeight>& neighbors = adjacency_list_.get(vertex);
        edges.reserve(neighbors.get_count());

        auto it_neighbors = neighbors.get_iterator();
        KeyValuePair<TVertex, TWeight> neigh;
        while (it_neighbors.try_get_current_item(neigh)) {
            edges.append(neigh);
            it_neighbors.next();
        }

        return edges;
    }

private:
    //структура: вершина -> (HashTable из соседей -> вес дуги)
    HashTable<TVertex, HashTable<TVertex, TWeight>> adjacency_list_;
};

#endif //LAB4_DIRECTEDGRAPH_HPP
