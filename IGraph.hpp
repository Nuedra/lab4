#ifndef LAB4_IGRAPH_HPP
#define LAB4_IGRAPH_HPP

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
};

#endif
