#ifndef LAB4_CSV_ACTIONS_HPP
#define LAB4_CSV_ACTIONS_HPP

#include <string>
#include "../DirectedGraph.hpp"
#include <fstream>

int generate_random_int(int min, int max);
double random_double(double min_val, double max_val);
void generate_and_write_random_graph_to_csv(const std::string& filename, int number_of_vertices, double edge_probability,
                                            int min_weight, int max_weight);
DirectedGraph<std::string, int> read_csv(const std::string& filename);

#endif //LAB4_CSV_ACTIONS_HPP
