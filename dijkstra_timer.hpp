#ifndef LAB4_DIJKSTRA_TIMER_HPP
#define LAB4_DIJKSTRA_TIMER_HPP

#include <string>

void measure_and_save_dijkstra_times(const std::string& csv_filename, int step, double edge_probability, int min_weight,
                                     int max_weight);

#endif //LAB4_DIJKSTRA_TIMER_HPP
