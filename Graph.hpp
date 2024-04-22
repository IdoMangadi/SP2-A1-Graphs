#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel{
    class Graph{
        public:
            std::vector<std::vector<int>> adj_matrix;
            Graph(){}
            // methods:
            /**
             * this function gets a matrix represented in 2d vector and copy it into the instance graph.
            */
            void loadGraph(const std::vector<std::vector<int>> &input_matrix);
            /**
             * this function print all the values of the graph.
            */
            void printGraph();
            /**
             * this function returns the size of the square graph.
            */
            int size();
    };
}

#endif // GRAPH_HPP
