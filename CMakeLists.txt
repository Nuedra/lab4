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
        data_structures/PriorityQueue.hpp
        graph_algorithms.hpp
        graph_algorithms.cpp)
