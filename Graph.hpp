// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <cstddef>

using namespace std;

namespace ariel{
    class Graph{
        private:
            vector<vector<int>> adj_matrix;
        public:
            /**
             * constructor of the graph:
            */
            Graph(){}
            Graph(const Graph& g);  // copy constructor (performing deep copy)
            /**
             * @brief Retrieve a constant reference to the adjacency matrix of the graph.
             *
             * This function returns a constant reference to the adjacency matrix of the graph.
             * It allows external access to the graph's internal adjacency matrix for reading purposes only.
             * The returned reference is constant, meaning that it cannot be used to modify the internal state of the graph.
             *
             * @return A constant reference to the adjacency matrix of the graph.
            */
            const vector<vector<int>>& getGraph() const {
                return adj_matrix;
            }
            // methods:
            /**
             * this function gets a matrix represented in 2d vector and copy it into the instance graph.
            */
            void loadGraph(const vector<vector<int>> &input_matrix);
            /**
             * this function print all the values of the graph.
            */
            void printGraph();
            /**
             * this function returns the size of the square graph.
            */
            size_t size();
    };
}

#endif // GRAPH_HPP
