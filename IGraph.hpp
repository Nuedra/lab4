#ifndef LAB4_IGRAPH_HPP
#define LAB4_IGRAPH_HPP

#include "data_structures/HashTable.hpp"
#include "data_structures/ArraySequence.h"
#include "pair/Pair.hpp"

template <typename TVertex, typename TWeight>
class IGraph {
public:
    virtual ~IGraph() = default;

    virtual void add_vertex(const TVertex& vertex) = 0;
    virtual void remove_vertex(const TVertex& vertex) = 0;
    virtual void add_edge(const TVertex& from, const TVertex& to, const TWeight& weight) = 0;
    virtual void remove_edge(const TVertex& from, const TVertex& to) = 0;
    virtual bool contains_vertex(const TVertex& vertex) const = 0;
    virtual bool contains_edge(const TVertex& from, const TVertex& to) const = 0;
    virtual TWeight get_edge_weight(const TVertex& from, const TVertex& to) const = 0;
    virtual ArraySequence<TVertex> get_vertices() const = 0;
    virtual ArraySequence<Pair<TVertex, TWeight>> get_outgoing_edges(const TVertex& vertex) const = 0;
};

#endif //LAB4_IGRAPH_HPP
