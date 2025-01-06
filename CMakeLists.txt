cmake_minimum_required(VERSION 3.27)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

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
        dot/dot_actions.hpp
        dot/dot_actions.cpp
        dijkstra_timer.hpp
        dijkstra_timer.cpp
        menu.hpp
        menu.cpp)
