#include "graph.hpp"
#include <stdexcept>
#include <string>
#include <graphviz/gvc.h>

#pragma clang diagnostic ignored "-Wwritable-strings"
void visualize_graph(const std::string& dot_filename, const std::string& png_filename) {
    const std::string& node_color = "lightblue";
    const std::string& edge_color = "black";

    GVC_t *gvc = gvContext();

    FILE *dot_file = fopen(dot_filename.c_str(), "r");
    Agraph_t *graph = agread(dot_file, nullptr);
    fclose(dot_file);

    for (Agnode_t *node = agfstnode(graph); node; node = agnxtnode(graph, node)) {
        agsafeset(node, "style", "filled", "");
        agsafeset(node, "fillcolor", node_color.c_str(), "");
    }

    for (Agnode_t *node = agfstnode(graph); node; node = agnxtnode(graph, node)) {
        for (Agedge_t *edge = agfstout(graph, node); edge; edge = agnxtout(graph, edge)) {
            agsafeset(edge, "color", edge_color.c_str(), "");
        }
    }

    gvLayout(gvc, graph, "dot");
    gvRenderFilename(gvc, graph, "png", png_filename.c_str());

    gvFreeLayout(gvc, graph);
    agclose(graph);
    gvFreeContext(gvc);

    std::string command = "open " + png_filename;
    system(command.c_str());
}
