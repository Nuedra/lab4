#ifndef LAB4_DIJKSTRA_TIMES_GRAPHIC_HPP
#define LAB4_DIJKSTRA_TIMES_GRAPHIC_HPP

#include <string>

void plot_dijkstra_times(const std::string& csv_filename, const std::string& png_filename, double edge_probability,
                         int min_step, int max_step);

#endif //LAB4_DIJKSTRA_TIMES_GRAPHIC_HPP
