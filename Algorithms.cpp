/**
 * In this file i implemented algorithms on graphs mentioned in the Algorithms.hpp file.
 * To do this i used: Course Algorithms 1 from last semester (lectures), 
 * wikipedia https://he.wikipedia.org/wiki/%D7%92%D7%A8%D7%A3_%D7%A7%D7%A9%D7%99%D7%A8
 * and ChatGPT.
*/

#include <iostream>
#include "Algorithms.hpp"

namespace ariel{
    
    namespace Algorithms{

        // A simple implementation of DFS:
        void dfs(Graph g, int v, std::vector<int> &visited){
            visited[v] = 1;  // marking the vertix as visited
            for(int i=0; i<g.size(); i++){ // going over the neighbours and if not visited, operating dfs on them
                if(g.adj_matrix[v][i] > 0 && visited[i] == 0) {
                    dfs(g, i, visited);
                }
            }
        }

        int isConnected(Graph g){
            // checking if it is a directed or undirected graph:
            int directed = 0;
            for(int i=0; i<g.size(); i++){
                for(int j=0; j<g.size(); j++){
                    if(g.adj_matrix[i][j] != g.adj_matrix[j][i]){
                        directed = 1;
                        break;
                    }
                }
                if (directed == 1) {break;}
            }

            std::vector<int> visited(g.size(), 0); // craeting a visited vector with 0's
            if(directed){
                // in this case we do n dfs's:
                for(int i=0; i<g.size(); i++){
                    std::fill(visited.begin(), visited.end(), 0); // filling "visited" with 0's.
                    dfs(g, i, visited);
                    for(int v : visited){  // going all over the vertices
                        if( v == 0){  // means we didnt reach to one of the vertices
                            return 0;
                        }
                    }
                }

            }
            else{  // the graph is undirected:
                dfs(g, 0, visited);  // operating dfs one time on the graph
                for(int v : visited){  // going all over the vertices
                    if( v == 0){  // means we didnt reach to one of the vertices
                        return 0;
                    }
                }
            }

            return 1;  // means all validations went ok, the graph is strong connected. 
        }

        std::vector<int> shortestPath(Graph g, int src, int dst){
            int n = g.adj_matrix.size();
            std::vector<int> dist(n, std::numeric_limits<int>::max()); // Initialize distances to infinity
            std::vector<int> parent(n, -1); // To store the parent of each vertex in the shortest path
            std::vector<int> path;

            dist[src] = 0;

            // Relax edges |V|-1 times:
            for (int i = 0; i < n-1; i++) {
                for (int j = 0; j < n; j++) {
                    for (int v = 0; v < n; v++) {
                        if (g.adj_matrix[j][v] != 0 && dist[j] != std::numeric_limits<int>::max() && dist[j] + g.adj_matrix[j][v] < dist[v]) {
                            dist[v] = dist[j] + g.adj_matrix[j][v];
                            parent[v] = j;
                        }
                    }
                }
            }

            // Check for negative cycles
            for (int u = 0; u < n; ++u) {
                for (int v = 0; v < n; ++v) {
                    if (g.adj_matrix[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.adj_matrix[u][v] < dist[v]) {
                        // Negative cycle found
                        std::cout << "Graph contains negative cycle" << std::endl;
                        return path;
                    }
                }
            }

            // Reconstruct the shortest path
            for (int v = dst; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());

            return path;
        }
        

        int isContainsCycle(Graph g){
            // to implement
        }

        int isBipartite(Graph g){
            // to implement
        }
    }
}