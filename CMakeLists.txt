cmake_minimum_required(VERSION 3.27)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GRAPHVIZ REQUIRED libgvc)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GRAPHVIZ_INCLUDE_DIRS})
link_directories(${GRAPHVIZ_LIBRARY_DIRS})

add_executable(lab4 main.cpp
        pair/Pair.hpp
        data_structures/IIterator.hpp
        data_structures/IDictionary.hpp
        data_structures/HashTable.hpp
        sorters/Isorter.hpp
        Sorters/HeapSorter.hpp
        IGraph.hpp
        DirectedGraph.hpp
        tests.hpp
        tests.cpp
        PriorityQueue.hpp
        dijkstra_algorithm.hpp
        limits.hpp
        csv/csv_actions.hpp
        csv/csv_actions.cpp
        dijkstra_timer.hpp
        dijkstra_timer.cpp
        menu.hpp
        menu.cpp
        graphics/dijkstra_times_graphic.hpp
        graphics/dijkstra_times_graphic.cpp
        graphics/graph.hpp
        graphics/graph.cpp)

target_link_libraries(lab4 ${Boost_LIBRARIES})
target_link_libraries(lab4 ${GRAPHVIZ_LIBRARIES})
