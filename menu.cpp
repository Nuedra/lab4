#include "menu.hpp"
#include "DirectedGraph.hpp"
#include <iostream>
#include "dijkstra_algorithm.hpp"
#include "csv/csv_actions.hpp"
#include "dijkstra_timer.hpp"
#include <string>
#include "pair/Pair.hpp"
#include <limits>
#include <stdexcept>
#include "data_structures/ArraySequence.h"
#include "PriorityQueue.hpp"

VertexChoice choose_vertex_type() {
    std::cout << "Выберите тип вершины:\n"
              << "1. int\n"
              << "2. char\n"
              << "3. string\n";
    int choice = read_in_range<int>("Введите номер: ", 1, 3);
    switch (choice) {
        case 1: return VertexChoice::INT_VERTEX;
        case 2: return VertexChoice::CHAR_VERTEX;
        case 3: return VertexChoice::STRING_VERTEX;
        default:
            return VertexChoice::STRING_VERTEX;
    }
}

WeightChoice choose_weight_type() {
    std::cout << "Выберите тип веса:\n"
              << "1. int\n"
              << "2. double\n"
              << "3. Pair<double, double>\n";
    int choice = read_in_range<int>("Введите номер: ", 1, 3);
    switch (choice) {
        case 1: return WeightChoice::INT_WEIGHT;
        case 2: return WeightChoice::DOUBLE_WEIGHT;
        case 3: return WeightChoice::PAIR_DOUBLE_DOUBLE_WEIGHT;
        default:
            return WeightChoice::INT_WEIGHT;
    }
}


