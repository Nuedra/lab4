#ifndef LAB4_MENU_HPP
#define LAB4_MENU_HPP

#include "DirectedGraph.hpp"
#include <iostream>
#include "dijkstra_algorithm.hpp"
#include "csv/csv_actions.hpp"
#include "dijkstra_timer.hpp"
#include <string>
#include "pair/Pair.hpp"

enum class VertexChoice {
    INT_VERTEX,
    CHAR_VERTEX,
    STRING_VERTEX
};

enum class WeightChoice {
    INT_WEIGHT,
    DOUBLE_WEIGHT,
    PAIR_DOUBLE_DOUBLE_WEIGHT,
};

VertexChoice choose_vertex_type();
WeightChoice choose_weight_type();

template <typename T>
T read_in_range(const char* prompt, T min_val, T max_val) {
    while (true) {
        std::cout << prompt;

        T value;
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некорректный ввод, попробуйте снова.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (value < min_val || value > max_val) {
            std::cout << "Значение должно быть в диапазоне ["
                      << min_val << ", " << max_val << "]. Попробуйте снова.\n";
            continue;
        }

        return value;
    }
}

template<typename TVertex, typename TWeight>
void print_graph(const DirectedGraph<TVertex, TWeight>& graph) {
    std::cout << "Directed Graph contents:\n";

    auto verts = graph.get_vertices();
    for (size_t i = 0; i < verts.get_length(); i++) {
        const TVertex& v = verts.get(i);
        std::cout << "Vertex [" << v << "]:\n";

        auto edges = graph.get_outgoing_edges(v);
        for (size_t j = 0; j < edges.get_length(); j++) {
            const auto& pair_vertex_edge = edges.get(j);
            std::cout << "   -> " << pair_vertex_edge.value1 << " (weight = " << pair_vertex_edge.value2 << ")\n";
        }
    }

    std::cout << std::endl;
}

template<typename TVertex, typename TWeight>
void graph_menu(DirectedGraph<TVertex, TWeight>& graph) {
    while (true) {
        std::cout << "\n[Операции с графом]\n"
                  << "1. Добавить вершину\n"
                  << "2. Удалить вершину\n"
                  << "3. Добавить ребро\n"
                  << "4. Удалить ребро\n"
                  << "5. Вывести граф\n"
                  << "6. Запустить Дейкстру\n"
                  << "0. Вернуться в главное меню\n";
        int c = read_in_range<int>("Выберите опцию: ", 0, 6);
        if (c == 0) {
            break;
        }
        else if (c == 1) {
            std::cout << "Введите вершину: ";
            TVertex v;
            std::cin >> v;
            graph.add_vertex(v);
        }
        else if (c == 2) {
            std::cout << "Введите вершину: ";
            TVertex v;
            std::cin >> v;
            graph.remove_vertex(v);
        }
        else if (c == 3) {
            std::cout << "Введите вершину-источник: ";
            TVertex src;
            std::cin >> src;
            std::cout << "Введите вершину-приёмник: ";
            TVertex tgt;
            std::cin >> tgt;
            std::cout << "Введите вес: ";
            TWeight w;
            if constexpr (std::is_same_v<TWeight, Pair<int,int>>) {
                int x,y;
                std::cout << "Введите два числа (x y): ";
                std::cin >> x >> y;
                w = Pair<int,int>(x,y);
            }
            else if constexpr(std::is_same_v<TWeight, Pair<double,double>>){
                double x,y;
                std::cout << "Введите два числа (x y): ";
                std::cin >> x >> y;
                w = Pair<double,double>(x,y);
            }
            else {
                std::cin >> w;
            }
            graph.add_edge(src, tgt, w);
        }
        else if (c == 4) {
            std::cout << "Введите вершину-источник: ";
            TVertex src, tgt;
            std::cin >> src;
            std::cout << "Введите вершину-приёмник: ";
            std::cin >> tgt;
            graph.remove_edge(src, tgt);
        }
        else if (c == 5) {
            print_graph(graph);
        }
        else if (c == 6) {
            std::cout << "Введите стартовую вершину: ";
            TVertex start;
            std::cin >> start;

            auto dist = dijkstra_shortest_paths(graph, start);
            auto verts = graph.get_vertices();
            for (int i = 0; i < verts.get_length(); i++) {
                if(dist.get(i) != custom_limits<TWeight>::max()){
                    std::cout << "dist(" << start << " -> " << verts.get(i) << ") = " << dist.get(i) << "\n";
                }
            }
        }
    }
}

template<typename TVertex, typename TWeight>
void graph_menu_for_random_graph(DirectedGraph<TVertex, TWeight>& graph) {
    while (true) {
        std::cout << "\n[Операции с случайно созданным графом]\n"
                  << "1. Вывести граф\n"
                  << "2. Запустить Дейкстру\n"
                  << "3. Представь в графическом виде(graphviz), не рекомендуется для графов состоящих из более чем 20 вершин\n"
                  << "0. Вернуться в главное меню\n";
        int c = read_in_range<int>("Выберите опцию: ", 0, 3);
        if (c == 0) {
            break;
        }
        if (c == 1) {
            print_graph(graph);
        }
        else if (c == 2) {
            std::cout << "Введите стартовую вершину: ";
            TVertex start;
            std::cin >> start;

            auto dist = dijkstra_shortest_paths(graph, start);
            auto verts = graph.get_vertices();
            for (int i = 0; i < verts.get_length(); i++) {
                if(dist.get(i) != custom_limits<TWeight>::max()){
                    std::cout << "dist(" << start << " -> " << verts.get(i) << ") = " << dist.get(i) << "\n";
                }
            }
        }
    }
}

#endif //LAB4_MENU_HPP
