// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il

/**
 * In this file i implemented algorithms on graphs mentioned in the Algorithms.hpp file.
 * To do this i used: Course Algorithms 1 from last semester (lectures), 
 * wikipedia https://he.wikipedia.org/wiki/%D7%92%D7%A8%D7%A3_%D7%A7%D7%A9%D7%99%D7%A8
 * and ChatGPT.
*/

#include <iostream>
#include <queue>
#include "Algorithms.hpp"

namespace ariel{
    
    namespace Algorithms{

        // IS CONNECTED:
        // A simple implementation of DFS:
        void dfs(Graph g, int v, std::vector<int> &visited){
            visited[v] = 1;  // marking the vertix as visited
            for(int i=0; i<g.size(); i++){ // going over the neighbours and if not visited, operating dfs on them
                if(g.adj_matrix[v][i] > 0 && visited[i] == 0) {
                    dfs(g, i, visited);
                }
            }
        }

        int isConnected(Graph &g){
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

        // SHORTEST PATH:
        std::string shortestPath(Graph &g, int src, int dst){
            int n = g.adj_matrix.size();
            std::vector<int> dist(n, std::numeric_limits<int>::max()); // Initialize distances to infinity
            std::vector<int> parent(n, -1); // To store the parent of each vertex in the shortest path (init with -1)
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
                        return "-1";
                    }
                }
            }

            // Check for empty path:
            if(parent[dst] == -1){
                return "-1";
            }

            // Reconstruct the shortest path
            for (int v = dst; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());  // reversing the path

            // converting to string:
            std::string result = "";
            for(int i=0; i<path.size(); i++){
                result += path[i];
                if(i != path.size()-1){
                    result += "->";
                }
            }
        
            return result;
        }
        

        // CYCLES:
        // Simple implementation of dfs regarding cycles finding using the DAG theorem.
        enum Color { WHITE, GREY, BLACK };
    
        bool cyc_dfs(Graph &g, int u, std::vector<Color> &color, std::vector<int> &parent, std::string &cycle) {
            color[u] = GREY; // marking the current vertex as visited but not finished

            // iterate over all adjacent vertices of the current vertex
            for (int v = 0; v < g.adj_matrix[u].size(); ++v) {
                if (g.adj_matrix[u][v] != 0) { // if there is an edge between u and v
                    if (color[v] == WHITE) { // if v is not visited yet
                        parent[v] = u; // Set u as the parent of v
                        if (cyc_dfs(g, v, color, parent, cycle)) { // Recursively call DFS for vertex v
                            return true; // If a cycle is found, return true
                        }
                    } else if (color[v] == GREY) { // if v is visited but not finished
                        std::vector<bool> in_cycle(g.adj_matrix.size(), false); // Create a boolean array to mark vertices in the cycle
                        int current = u; // Start from the current vertex u
                        while (!in_cycle[current]) { // Traverse the cycle until we reach u again
                            cycle += std::to_string(current) + "->"; // Add the current vertex to the cycle string
                            in_cycle[current] = true; // Mark the current vertex as visited in the cycle
                            current = parent[current]; // Move to the parent vertex
                        }
                        cycle += std::to_string(current); // Add the last vertex of the cycle
                        std::reverse(cycle.begin(), cycle.end()); // Reverse the cycle string to get the correct order
                        return true; // Return true to indicate that a cycle is found
                    }
                }
            }

            color[u] = BLACK; // Mark the current vertex as finished
            return false; // Return false if no cycle is found
        }

        std::string isContainsCycle(Graph &g){
            int n = g.adj_matrix.size();
            std::vector<Color> color(n, WHITE); // Initialize all vertices as not visited
            std::vector<int> parent(n, -1); // To store the parent of each vertex in the DFS tree
            std::string cycle;

            // Perform DFS from each vertex
            for (int i = 0; i < n; ++i) {
                if (color[i] == WHITE && cyc_dfs(g, i, color, parent, cycle)) {
                    return cycle; // If a cycle is found, return it
                }
            }

            return "0"; // No cycle found
        }


        // BIAPARTITE:
        std::string isBipartite(Graph &g) {
            int n = g.adj_matrix.size();
            std::vector<Color> color(n, WHITE); // Initialize all vertices with no color
            std::string groupA = "{";
            std::string groupB = "{";

            // Perform BFS from each vertex
            for (int i = 0; i < n; ++i) {
                if (color[i] == WHITE) { // If the vertex is not colored
                    if (!BFS(g, i, color, groupA, groupB)) { // If the graph is not bipartite
                        return "0";
                    }
                }
            }

            // Construct the result string
            std::string result = "The graph is bipartite: A=" + groupA + "}, B=" + groupB + "}.";
            return result;
        }

        bool BFS(Graph &g, int src, std::vector<Color> &color, std::string &groupA, std::string &groupB) {
            int n = g.adj_matrix.size();
            std::queue<int> q;
            q.push(src);
            color[src] = GREY; // Color the source vertex with GREY
            groupA += std::to_string(src) + ",";
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v = 0; v < n; ++v) {
                    if (g.adj_matrix[u][v] != 0) { // If there is an edge between u and v
                        if (color[v] == WHITE) { // If v is not colored yet
                            color[v] = (color[u] == BLACK) ? GREY : BLACK; // Assign the opposite color of u to v
                            if (color[v] == BLACK) {
                                groupB += std::to_string(v) + ",";
                            } else {
                                groupA += std::to_string(v) + ",";
                            }
                            q.push(v);
                        } else if (color[v] == color[u]) { // If v and u have the same color
                            return false; // The graph is not bipartite
                        }
                    }
                }
                color[u] = BLACK; // Color the vertex as BLACK once it is completely processed
            }

            return true; // The graph is bipartite
        }


        // NEGATIVE CYCLE:
        std::string negativeCycle(Graph &g) {
            int n = g.adj_matrix.size();
            std::vector<int> dist(n, 0);
            std::vector<int> parent(n, -1);
            int lastUpdated = -1;

            for (int i = 0; i < n; ++i) {
                lastUpdated = -1;
                for (int u = 0; u < n; ++u) {
                    for (int v = 0; v < n; ++v) {
                        if (g.adj_matrix[u][v] != 0 && dist[u] + g.adj_matrix[u][v] < dist[v]) {
                            dist[v] = dist[u] + g.adj_matrix[u][v];
                            parent[v] = u;
                            lastUpdated = v;
                        }
                    }
                }
            }

            if (lastUpdated == -1) {
                return "0"; // No negative cycle found
            }

            std::vector<bool> visited(n, false);
            int start = lastUpdated;
            for (int i = 0; i < n; ++i) {
                start = parent[start];
            }

            std::string cycle = "";
            int u = start;
            do {
                cycle += std::to_string(u) + "->";
                u = parent[u];
                visited[u] = true;
            } while (!visited[u]);
            cycle += std::to_string(u);
            std::reverse(cycle.begin(), cycle.end());
            return cycle;
        }

    }  // namespace algorithms
}  // namespace ariel