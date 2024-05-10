# Graph Algorithms
This project implements various graph algorithms such as: 
    finding whether a graph is strongly connected, 
    finding the shortest path, checking for cycles, 
    determining if a graph is bipartite, 
    and detecting negative cycles.

## Project Structure
The project is divided into two main parts:

1. **Graph**: Contains the implementation of the Graph class.
   - `Graph.hpp`: Header file containing the declaration of the Graph class.
   - `Graph.cpp`: Source file containing the implementation of the Graph class methods.

2. **Algorithms**: Contains the implementation of various graph algorithms.
   - `Algorithms.hpp`: Header file containing the declaration of the Algorithms namespace and its functions.
   - `Algorithms.cpp`: Source file containing the implementation of the graph algorithms.

## Graph Class

The `Graph` class is responsible for representing a graph. It contains an adjacency matrix to store the graph's edges.

### Methods:

1. `loadGraph(const std::vector<std::vector<int>> &input_matrix)`: Copies a given matrix into the graph's adjacency matrix.
   - **Parameters**: `input_matrix` - The matrix to be copied.
   - **Return Type**: `void`

2. `printGraph()`: Prints all the values of the graph.
   - **Return Type**: `void`

3. `size()`: Returns the size of the square graph.
   - **Return Type**: `size_t`

## Algorithms Namespace

The `Algorithms` namespace contains various graph algorithms.

### Functions:

1. `isConnected(Graph &g)`: Determines if a given graph is strongly connected for directed or undirected graphs.
   - **Return Type**: `int` - 1 for strongly connected, 0 for not strongly connected.

2. `shortestPath(Graph &g, size_t src, size_t dst)`: Returns the shortest path from source to destination using the Bellman-Ford algorithm.
   - **Return Type**: `std::string` - The shortest path as a string.

3. `isContainsCycle(Graph &g)`: Determines if a given graph contains a cycle.
   - **Return Type**: `bool` - True if the graph contains a cycle, false otherwise.

4. `isBipartite(Graph &g)`: Determines if a given graph is bipartite.
   - **Return Type**: `std::string` - "The graph is bipartite: A={...}, B={...}" or "0" if the graph is not bipartite.

5. `negativeCycle(Graph &g)`: Determines if there is a negative cycle in a given directed graph.
   - **Return Type**: `std::string` - The negative cycle as a string or "No negative cycle" if there is none.

## How to Use

1. **Include Header Files**: Include `Graph.hpp` and `Algorithms.hpp` in the project.
   ```cpp
   #include "Graph.hpp"
   #include "Algorithms.hpp"
   ...
   ...
    ariel::Graph graph;
    ...
    ...
    graph.loadGraph(input_matrix);
    ...
    ...
    int connected = ariel::Algorithms::isConnected(graph);
    std::string shortestPath = ariel::Algorithms::shortestPath(graph, src, dst);
    bool hasCycle = ariel::Algorithms::isContainsCycle(graph);
    std::string isBipartite = ariel::Algorithms::isBipartite(graph);
    std::string negativeCycle = ariel::Algorithms::negativeCycle(graph);


