#include "dijkstra_times_graphic.hpp"
#include "../libs/gnuplot-iostream.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

void plot_dijkstra_times(const std::string& csv_filename, const std::string& png_filename, double edge_probability, int min_step, int max_step) {
    std::ifstream csv_file(csv_filename);
    if (!csv_file.is_open()) {
        std::cerr << "Failed to open CSV file: " << csv_filename << std::endl;
        return;
    }

    std::string line;
    std::getline(csv_file, line);

    std::vector<std::string> headers;
    std::istringstream header_ss(line);
    std::string header_token;

    while (std::getline(header_ss, header_token, ',')) {
        headers.push_back(header_token);
    }

    if (headers.size() < 2) {
        std::cerr << "CSV file must have at least 'Vertices' and 'Time_ms' columns." << std::endl;
        return;
    }

    if (headers[0] != "Vertices") {
        std::cerr << "First column must be 'Vertices'." << std::endl;
        return;
    }

    std::vector<int> vertices;
    std::vector<long long> times;

    while (std::getline(csv_file, line)) {
        std::istringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int vertex_count = std::stoi(token);
        vertices.push_back(vertex_count);

        std::getline(ss, token, ',');
        long long time = std::stoll(token);
        times.push_back(time);
    }

    csv_file.close();

    Gnuplot gp;

    gp << "set terminal png size 800,600 enhanced font 'Arial,10'\n";
    gp << "set output '" << png_filename << "'\n";
    gp << "set title 'Dijkstra Algorithm Performance'\n";
    gp << "set xlabel 'Number of Vertices'\n";
    gp << "set ylabel 'Execution Time (ms)'\n";
    gp << "set grid\n";
    gp << "set key left top\n";

    // Добавление информации в легенду
    std::ostringstream legend;
    legend << "Edge Probability: " << edge_probability << ", Weight Range: [" << min_step << ", " << max_step << "]";

    gp << "plot '-' with linespoints title '" << legend.str() << "'\n";

    gp.send1d(boost::make_tuple(vertices, times));

    std::cout << "Graph saved to " << png_filename << std::endl;

    std::string command = "open " + png_filename;
    system(command.c_str());
}
