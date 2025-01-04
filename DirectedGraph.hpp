#ifndef LAB4_DIRECTEDGRAPH_HPP
#define LAB4_DIRECTEDGRAPH_HPP

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
        return from_neighbors.get(to);
    }

    void remove_edge(const TVertex& from, const TVertex& to) override {

    }

private:
    //структура: вершина -> (HashTable из соседей -> вес дуги)
    HashTable<TVertex, HashTable<TVertex, TWeight>> adjacency_list_;
};

#endif //LAB4_DIRECTEDGRAPH_HPP
