#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <limits>
#include <algorithm>
#include "Graph.hpp"

namespace ariel{
    /**
     * Namespace for algorithms on graphs.
    */
    namespace Algorithms{
        /**
         * Function to determine if a given Graph is strong connected for directed or undirected graph.
         * In case of directed graph, this function implements a brute-approach using dfs from all vertices.
         * returns: 1 for strong connected and 0 for not strong connected.
        */
        int isConnected(Graph &g);
        /**
         * Function to return the shortest path from src to dst using bellman ford algorithm.
         * The choice to use this algorithm is because we want to detect a negative cycle.
         * returns: the shortest path as a vector, empty vector if there is no such path at all or if there is a negative cycle.
        */
        std::vector<int> shortestPath(Graph &g, int src, int dst);
        int isContainsCycle(Graph &g); 
        int isBipartite(Graph &g);
    }
}


#endif // ALGORITHMS_HPP