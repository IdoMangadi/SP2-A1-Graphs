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

        // ------------------------------------------------ //
        // ------------------IS CONNECTED------------------ //
        // ------------------------------------------------ //
        /**
         * A simple implementation of DFS:
        */ 
        void dfs(Graph &g, size_t v, std::vector<int> &visited){

            visited[v] = 1;  // marking the vertix as visited
            for(size_t i=0; i<g.size(); i++){ // going over the neighbours and if not visited, operating dfs on them
                if(g.adj_matrix[v][i] > 0 && visited[i] == 0) {
                    dfs(g, i, visited);
                }
            }
        }

        /**
         * A simple util function to check whethear a graph is directed or not
        */
        bool isDirected(Graph &g){
            for(size_t i=0; i<g.size(); i++){  // going over all the verteces
                for(size_t j=0; j<g.size(); j++){
                    if(g.adj_matrix[i][j] != g.adj_matrix[j][i]){ 
                        return true;
                    }
                }
            }
            return false;
        }

        int isConnected(Graph &g){
            // checking if it is a directed or undirected graph:
            bool directed = isDirected(g);
            

            std::vector<int> visited(g.size(), 0); // craeting a visited vector with 0's
            if(directed){
                // in this case we do n dfs's:
                for(size_t i=0; i<g.size(); i++){
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


        // ------------------------------------------------ //
        // ------------------SHORTEST PATH----------------- //
        // ------------------------------------------------ //

        std::string shortestPath(Graph &g, size_t src, size_t dst){
            size_t n = g.adj_matrix.size();
            std::vector<int> dist(n, std::numeric_limits<int>::max()); // Initialize distances to infinity
            std::vector<int> parent(n, -1); // To store the parent of each vertex in the shortest path (init with -1)
            std::vector<int> path; // to store the shortest path from src to dst

            dist[src] = 0; // init the distance from src to itself to 0

            // Relax edges |V|-1 times:
            for (size_t i = 0; i < n-1; i++) { // notice (n-1)
                for (size_t j = 0; j < n; j++) {  // going over the edges:
                    for (size_t v = 0; v < n; v++) {
                        if (g.adj_matrix[j][v] != 0 && dist[j] != std::numeric_limits<int>::max() && dist[j] + g.adj_matrix[j][v] < dist[v]) {
                            dist[v] = dist[j] + g.adj_matrix[j][v];
                            parent[v] = j;
                        }
                    }
                }
            }

            // Check for negative cycles (one last relaxing)
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.adj_matrix[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.adj_matrix[u][v] < dist[v]) {
                        // Negative cycle found
                        // std::cout << "Graph contains negative cycle" << std::endl;
                        return "-1";
                    }
                }
            }
            
            // Check for empty path:
            if(parent[dst] == -1){
                return "-1";
            }

            // Reconstruct the shortest path
            for (int v = dst; v != -1; v = parent[(unsigned int)v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());  // reversing the path
            // converting to string:
            std::string result = "";
            for(size_t i=0; i<path.size(); i++){
                result += std::to_string(path[i]);
                if(i != path.size()-1){
                    result += "->";
                }
            }

            return result;
        }
        

        // ------------------------------------------------ //
        // ---------------------CYCLES--------------------- //
        // ------------------------------------------------ //

        // Simple implementation of dfs regarding cycles finding using the DAG theorem.
        enum Color { WHITE, GREY, BLACK };
        // directed graphs version:
        bool hasCycleUtil_directed(Graph &g, size_t u, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycleVertices) {
            color[u] = GREY; // Mark the current vertex as visited but not finished

            for (size_t v = 0; v < g.adj_matrix[u].size(); ++v) {  // going over the neighbours:
                if (g.adj_matrix[u][v] != 0) {
                    if (color[v] == WHITE) {  // means neighbour hasnt visited yet
                        parent[v] = u;
                        if (hasCycleUtil_directed(g, v, color, parent, cycleVertices)) {  // recursive call (implementing dfs principle)
                            return true;
                        }
                    } else if (color[v] == GREY) {  // means neighbour was visited already
                        int current = u;  // holding the cycle:
                        cycleVertices.push_back(v);
                        while (current != v) {
                            cycleVertices.push_back(current);
                            current = parent[static_cast<size_t>(current)];
                        }
                        cycleVertices.push_back(v);  // Adding the starting vertex to complete the cycle
                        std::reverse(cycleVertices.begin(), cycleVertices.end());
                        return true;
                    }
                }
            }

            color[u] = BLACK; // Mark the current vertex as finished
            return false;
        }
        // undirected graphs version:
        bool hasCycleUtil_undirected(Graph &g, size_t u, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycleVertices) {
            color[u] = GREY; // Mark the current vertex as visited but not finished

            for (size_t v = 0; v < g.adj_matrix[u].size(); ++v) {  // going over the neighbours:
                if (g.adj_matrix[u][v] != 0) {
                    if (color[v] == WHITE) {  // means neighbour hasnt visited yet
                        parent[v] = u;
                        if (hasCycleUtil_undirected(g, v, color, parent, cycleVertices)) {  // recursive call (implementing dfs principle)
                            return true;
                        }
                    } else if (color[v] == GREY && parent[u] != v) {  // means neighbour was visited already
                        int current = u;  // holding the cycle:
                        cycleVertices.push_back(v);
                        while (current != v) {
                            cycleVertices.push_back(current);
                            current = parent[static_cast<size_t>(current)];
                        }
                        cycleVertices.push_back(v);  // Adding the starting vertex to complete the cycle
                        std::reverse(cycleVertices.begin(), cycleVertices.end());
                        return true;
                    }
                }
            }

            color[u] = BLACK; // Mark the current vertex as finished
            return false;
        }

        bool isContainsCycle(Graph &g) {
            size_t n = g.adj_matrix.size();
            std::vector<Color> color(n, WHITE); // Initialize all vertices as not visited
            std::vector<int> parent(n, -1); // To store the parent of each vertex in the DFS tree (init with -1)
            std::vector<int> cycleVertices;  // to store the cycle if founded

            if(isDirected(g)){
                // Perform DFS from each vertex
                for (size_t i = 0; i < n; ++i) {
                    if (color[i] == WHITE && hasCycleUtil_directed(g, i, color, parent, cycleVertices)) {
                        // Construct the cycle string
                        std::string cycle = "The cycle is: ";
                        for (size_t ver = 0; ver < cycleVertices.size(); ver++) {
                            cycle += std::to_string(cycleVertices[ver]);
                            if(ver < cycleVertices.size()-1){
                                cycle += "->";
                            }
                        }
                        std::cout << cycle << std::endl;
                        return true;
                    }
                }
                return false; // No cycle found
            }
            else{
                // Perform DFS from each vertex
                for (size_t i = 0; i < n; ++i) {
                    if (color[i] == WHITE && hasCycleUtil_undirected(g, i, color, parent, cycleVertices)) {
                        // Construct the cycle string
                        std::string cycle = "The cycle is: ";
                        for (size_t ver = 0; ver < cycleVertices.size(); ver++) {
                            cycle += std::to_string(cycleVertices[ver]);
                            if(ver < cycleVertices.size()-1){
                                cycle += "->";
                            }
                        }
                        std::cout << cycle << std::endl;
                        return true;
                    }
                }
                return false; // No cycle found
            }
        }



        // ------------------------------------------------ //
        // -------------------BIAPARTIT-------------------- //
        // ------------------------------------------------ //

        bool bfs(Graph &g, size_t src, std::vector<Color> &color, std::vector<size_t> &groupA, std::vector<size_t> &groupB) {
            size_t n = g.adj_matrix.size();
            std::queue<size_t> q;
            q.push(src);
            color[src] = GREY; // Color the source vertex with GREY
            groupA.push_back(src);

            while (!q.empty()) {
                size_t u = q.front();
                q.pop();
                for (size_t v = 0; v < n; ++v) {
                    if (g.adj_matrix[u][v] != 0) { // If there is an edge between u and v
                        if (color[v] == WHITE) { // If v is not colored yet
                            color[v] = (color[u] == BLACK) ? GREY : BLACK; // Assign the opposite color of u to v
                            if (color[v] == BLACK) {
                                groupB.push_back(v);
                            } else {
                                groupA.push_back(v);
                            }
                            q.push(v);
                        } else if (color[v] == color[u]) { // If v and u have the same color
                            return false; // The graph is not bipartite
                        }
                    }
                }
            }

            return true; // The graph is bipartite
        }

        std::string isBipartite(Graph &g) {
            size_t n = g.adj_matrix.size();
            std::vector<Color> color(n, WHITE); // Initialize all vertices with no color
            std::vector<size_t> groupA;
            std::vector<size_t> groupB;

            // Perform BFS from each vertex
            for (size_t i = 0; i < n; ++i) {
                if (color[i] == WHITE) { // If the vertex is not colored
                    if (!bfs(g, i, color, groupA, groupB)) { // If the graph is not bipartite
                        return "0";
                    }
                }
            }

            // Construct the result string
            std::string result = "The graph is bipartite: A={";
            for (size_t i = 0; i < groupA.size(); ++i) {
                result += std::to_string(groupA[i]);
                if (i != groupA.size() - 1) {
                    result += ", ";
                }
            }
            result += "}, B={";
            for (size_t i = 0; i < groupB.size(); ++i) {
                result += std::to_string(groupB[i]);
                if (i != groupB.size() - 1) {
                    result += ", ";
                }
            }
            result += "}.";

            return result;
        }


        
        // ------------------------------------------------ //
        // ----------------NEGATIVE CYCLES----------------- //
        // ------------------------------------------------ //

        std::string negativeCycle(Graph &g) {
            size_t n = g.adj_matrix.size();
            std::vector<int> dist(n, 0);
            std::vector<int> parent(n, -1);
            int lastUpdated = -1;

            for (size_t i = 0; i < n; ++i) {
                lastUpdated = -1;
                for (size_t u = 0; u < n; ++u) {
                    for (size_t v = 0; v < n; ++v) {
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
            for (size_t i = 0; i < n; ++i) {
                start = parent[(unsigned int)start];
            }

            std::string cycle = "";
            int u = start;
            do {
                cycle += std::to_string(u) + "->";
                u = parent[(unsigned int)u];
                visited[(unsigned int)u] = true;
            } while (!visited[(unsigned int)u]);
            cycle += std::to_string(u);
            std::reverse(cycle.begin(), cycle.end());
            return cycle;
        }

    }  // namespace algorithms
}  // namespace ariel