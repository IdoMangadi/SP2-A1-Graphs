/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */

// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#include "Graph.hpp"
#include "Algorithms.hpp"
using namespace ariel;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

int main()
{
    ariel::Graph g;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->1->2.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2}, B={1}."

    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g.loadGraph(graph2); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 8 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "-1" (there is no path between 0 and 4).
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" (false).

    // 5x5 matrix that reprsents a connected weighted graph.
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 10 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: 0->2->3->4.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2, 4}, B={1, 3}."

    // 5x4 matrix that reprsents invalid graph.
    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    try
    {
        g.loadGraph(graph4); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    }

    // 5x5 matrix that reprsents graph with negataive cycle.
    vector<vector<int>> graph5 = {
        {0, 1, 0, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0,-9},
        {1, 0, 9, 0, 0}};
    g.loadGraph(graph5); // Load the graph to the object.

    g.printGraph(); 
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 3) << endl;
    cout << Algorithms::isContainsCycle(g) << endl; 
    cout << Algorithms::isBipartite(g) << endl;  
    cout << Algorithms::negativeCycle(g) << endl;

    // 8x8 matrix that reprsents graph with negataive cycle.
    vector<std::vector<int>> graph6 = {
        {  0,   1,  10,   6,   -1,  10,   -8,  -6},
        { 10,   0,  10,   0,    0,   0,   -3,  10},
        {  1  -10,   0,   1,    0,  -3,  -10,  -9},
        {  1,  -3,   0,   0,    0,  -4,    3,   0},
        { 10,   2,  -3,   0,    0,  -1,    0,   1},
        { -2,   1,   0,   0,    0,   0,    1,   1},
        {  2,  10,   2,   0,    0,   0,    0,   1},
        { 10,   5,   0,  10,    0,  10,  -10,   0}};

    g.loadGraph(graph6); // Load the graph to the object.

    g.printGraph(); 
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 3) << endl;
    cout << Algorithms::isContainsCycle(g) << endl; 
    cout << Algorithms::isBipartite(g) << endl;  
    cout << Algorithms::negativeCycle(g) << endl;  


    // 8x8 matrix that reprsents graph with negataive cycle.
    vector<std::vector<int>> graph7 = {
        {  0,   0,   0,   0,    0,  10,   -8,  -6},
        {  0,   0,   0,   0,    0,  20,   12,  -9},
        {  0,   0,   0,   0,    0,   1,   -2,   0},
        {  0,   0,   0,   0,    0,  -6,    0,   6},
        {  0,   0,   0,   0,    0,   0,   -8,   2},
        { -2,   1,   3,   2,    1,   0,    0,   0},
        { -2,  10,  -2,   0,    6,   0,    0,   0},
        { 10,   5,   0,   9,    0,   0,    0,   0}};

    g.loadGraph(graph7); // Load the graph to the object.

    g.printGraph(); 
    cout << Algorithms::isConnected(g) << endl;
    cout << Algorithms::shortestPath(g, 0, 3) << endl;
    cout << Algorithms::isContainsCycle(g) << endl; 
    cout << Algorithms::isBipartite(g) << endl;  
    cout << Algorithms::negativeCycle(g) << endl;  

}
