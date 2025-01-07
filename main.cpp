#include "tests.hpp"
#include "menu.hpp"
#include <cstdlib>
#include "dijkstra_timer.hpp"

int main() {
    start_tests();
    while (true) {
        std::cout << "\nГлавное меню:\n"
                  << "1) Создать граф вручную\n"
                  << "2) Сгенерировать случайный граф (string, int)\n"
                  << "3) Измерить время работы Дейкстры (на серии графов)\n"
                  << "4) Очистка\n"
                  << "0) Выход\n";
        int choice = read_in_range<int>("Введите номер: ", 0, 4);
        if (choice == 0) {
            std::cout << "Выход.\n";
            break;
        }

        else if (choice == 1) {
            auto v_choice = choose_vertex_type();
            auto w_choice = choose_weight_type();
            // INT
            if (v_choice == VertexChoice::INT_VERTEX && w_choice == WeightChoice::INT_WEIGHT) {
                DirectedGraph<int, int> graph;
                graph_menu(graph);
            }
            else if (v_choice == VertexChoice::INT_VERTEX && w_choice == WeightChoice::DOUBLE_WEIGHT) {
                DirectedGraph<int, double> graph;
                graph_menu(graph);
            }
            else if (v_choice == VertexChoice::INT_VERTEX && w_choice == WeightChoice::PAIR_DOUBLE_DOUBLE_WEIGHT) {
                DirectedGraph<int, Pair<double, double>> graph;
                graph_menu(graph);
            }
            // STRING
            else if (v_choice == VertexChoice::STRING_VERTEX && w_choice == WeightChoice::INT_WEIGHT) {
                DirectedGraph<std::string, int> graph;
                graph_menu(graph);
            }
            else if (v_choice == VertexChoice::STRING_VERTEX && w_choice == WeightChoice::DOUBLE_WEIGHT) {
                DirectedGraph<std::string, double> graph;
                graph_menu(graph);
            }
            else if (v_choice == VertexChoice::STRING_VERTEX && w_choice == WeightChoice::PAIR_DOUBLE_DOUBLE_WEIGHT) {
                DirectedGraph<std::string, Pair<double, double>> graph;
                graph_menu(graph);
            }
            //CHAR
            else if (v_choice == VertexChoice::CHAR_VERTEX && w_choice == WeightChoice::INT_WEIGHT) {
                DirectedGraph<char, int> graph;
                graph_menu(graph);
            }
            else if (v_choice == VertexChoice::CHAR_VERTEX && w_choice == WeightChoice::DOUBLE_WEIGHT) {
                DirectedGraph<char, double> graph;
                graph_menu(graph);
            }
            else if (v_choice == VertexChoice::CHAR_VERTEX && w_choice == WeightChoice::PAIR_DOUBLE_DOUBLE_WEIGHT) {
                DirectedGraph<char, Pair<double, double>> graph;
                graph_menu(graph);
            }

        }

        else if (choice == 2) {
            const std::string& filename = "../csv/random_graph.csv";
            int n = read_in_range<int>("Количество вершин: ",1, 100000);
            double p = read_in_range<double>("Вероятность возникновения ребра (0..1), при большом кол-ве вершин не рекомендуется > 0.3: ",
                                             0.0, 1.0);
            int min_w = read_in_range<int>("Минимальный вес дуги: ", 0, 9999);
            int max_w = read_in_range<int>("Максимальный вес дуги: ", min_w, 9999);
            generate_and_write_random_graph_to_csv(filename, n, p, min_w,
                                                   max_w);
            DirectedGraph<std::string, int> graph;
            graph = read_csv(filename);
            graph_menu_for_random_graph(graph);
        }

        else if (choice == 3) {
            const std::string& filename = "../csv/dijkstra_times.csv";

            int size = read_in_range<int>("Минимальное количество вершин и шаг: ", 0, 100);
            double p = read_in_range<double>("Вероятность возникновения ребра (0..1): ", 0.0, 1.0);
            int min_w = read_in_range<int>("Минимальный вес дуги: ", 0, 9999);
            int max_w = read_in_range<int>("Максимальный вес дуги: ", min_w, 9999);
            measure_and_save_dijkstra_times(filename, size, p, min_w,
                                            max_w);
        }

        if (choice == 4) {
            std::system("clear");
        }
    }

    return 0;
}