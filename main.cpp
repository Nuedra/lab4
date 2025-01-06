#include "tests.hpp"
#include "menu.hpp"

int main() {
    start_tests();
    /*
    while (true) {
        std::cout << "\nГлавное меню:\n"
                  << "1) Создать граф вручную\n"
                  << "2) Сгенерировать случайный граф (в памяти)\n"
                  << "3) Измерить время работы Дейкстры (серию графов)\n"
                  << "0) Выход\n";
        int choice = read_int_in_range("Введите номер: ", 0, 3);
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

        }
    }
    */
    const std::string& filename = "../dot/mama.dot";
    int number_of_vertices = 10;
    double edge_probability = 0.0;
    int min_weight = 1;
    int max_weight = 10;

    generate_and_write_random_graph_to_dot(filename,  number_of_vertices,  edge_probability, min_weight, max_weight);
    return 0;
}