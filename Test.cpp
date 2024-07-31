#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Test isConnected")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isConnected(g) == false);

    // EDGE CASE: empty graph
    vector<vector<int>> graph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(Algorithms::isConnected(g) == false);

}

TEST_CASE("Test shortestPath")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::shortestPath(g, 0, 4) == "-1");

    // EDGE CASE: empty graph
    vector<vector<int>> graph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "-1");
    // EDGE CASE: unvalid src or dst:
    CHECK(Algorithms::shortestPath(g, 0, 3) == "-1");  // unvalid dst
    CHECK(Algorithms::shortestPath(g, 7, 2) == "-1");  // unvalid src

    vector<std::vector<int>> graph4 = {
        {  0,   2,   2,   1,    2,  10,    8,   6},
        {  1,   0,   2,   4,    5,  20,   12,   9},
        {  4,   0,   0,   0,    6,   3,    1,   0},
        {  2,   2,   7,   0,    0,   6,    1,   6},
        {  0,   0,   0,   2,    0,   2,    5,   4},
        {  2,   1,   3,   2,    1,   0,    1,   1},
        {  2,  10,   2,   1,    6,   1,    0,   3},
        { 10,   5,   0,   9,    9,   1,    1,   0}};
    g.loadGraph(graph4);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->2");
    CHECK(Algorithms::shortestPath(g, 4, 5) == "4->5");
    CHECK(Algorithms::shortestPath(g, 7, 2) == "7->6->2");
    CHECK(Algorithms::shortestPath(g, 1, 3) == "1->0->3");
    CHECK(Algorithms::shortestPath(g, 6, 1) == "6->5->1");
    CHECK(Algorithms::shortestPath(g, 6, 1) == "6->5->1");
    CHECK(Algorithms::shortestPath(g, 0, 7) == "0->3->6->5->7");
    CHECK(Algorithms::shortestPath(g, 0, 0) == "-1");  // EDGE CASE: src=dst
}

TEST_CASE("Test isContainsCycle")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isContainsCycle(g) == true);

    vector<std::vector<int>> graph3 = {
        {  0,   2,   2,   1,    2,  10,    8,   6},
        {  1,   0,   2,   4,    5,  20,   12,   9},
        {  4,   0,   0,   0,    6,   3,    1,   0},
        {  2,   2,   7,   0,    0,   6,    1,   6},
        {  0,   0,   0,   2,    0,   2,    5,   4},
        {  2,   1,   3,   2,    1,   0,    1,   1},
        {  2,  10,   2,   1,    6,   1,    0,   3},
        { 10,   5,   0,   9,    9,   1,    1,   0}};
    g.loadGraph(graph3);
    CHECK(Algorithms::isContainsCycle(g) == true);

    vector<vector<int>> graph4 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(Algorithms::isContainsCycle(g) == false);
}

TEST_CASE("Test isBipartite")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(Algorithms::isBipartite(g) == "0");

     vector<std::vector<int>> graph4 = {
        {  0,   0,   0,   0,    0,  10,   -8,  -6},
        {  0,   0,   0,   0,    0,  20,   12,  -9},
        {  0,   0,   0,   0,    0,   1,   -2,   0},
        {  0,   0,   0,   0,    0,  -6,    0,   6},
        {  0,   0,   0,   0,    0,   0,   -8,   2},
        { -2,   1,   3,   2,    1,   0,    0,   0},
        { -2,  10,  -2,   0,    6,   0,    0,   0},
        { 10,   5,   0,   9,    0,   0,    0,   0}};

    g.loadGraph(graph4);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2, 3, 4}, B={5, 6, 7}");

    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2}, B={}");
}

TEST_CASE("Test invalid graph")
{
    // EDGE CASE: not square matrix
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    // EDGE CASE: not square matrix
    vector<vector<int>> graph2 = {
        {0, 1, 0, 1},
        {1, 0, 1, 1},
        {0, 1, 0}};
    CHECK_THROWS(g.loadGraph(graph2));

    // EDGE CASE: empty graph
    vector<vector<int>> graph3 = {};
    CHECK_THROWS(g.loadGraph(graph3));
}

TEST_CASE("Test negativeCycle")
{
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 0},
        {0, 0, 2, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0,-9},
        {1, 0, 9, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::negativeCycle(g) == "0->1->2->3->4->0");

    vector<std::vector<int>> graph2 = {
        {  0,   1,  10,   6,   -1,  10,   -8,  -6},
        { 10,   0,  10,   0,    0,   0,   -3,  10},
        {  1, -10,   0,   1,    0,  -3,  -10,  -9},
        {  1,  -3,   0,   0,    0,  -4,    3,   0},
        { 10,   2,  -3,   0,    0,  -1,    0,   1},
        { -2,   1,   0,   0,    0,   0,    1,   1},
        {  2,  10,   2,   0,    0,   0,    0,   1},
        { 10,   5,   0,  10,    0,  10,  -10,   0}};
    g.loadGraph(graph2);
    CHECK(Algorithms::negativeCycle(g) == "6->7->6");  // inner negative cycle

    vector<vector<int>> graph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph3);
    // EDGE CASE: directed graph
    CHECK(Algorithms::negativeCycle(g) == "-1");  // directed graph

    vector<std::vector<int>> graph4 = {
        {  0,   2,   2,   0,    0,  10,    8,   6},
        {  0,   0,  -1,   0,    0,  20,   12,   9},
        {  4,   0,   0,   0,    6,   2,    2,   0},
        {  2,   2,   0,   0,    0,   6,    0,   6},
        {  0,   0,   0,   2,    0,   0,    5,   2},
        {  2,  -1,   3,   2,   -1,   0,    0,   2},
        {  2,  10,   2,   0,    6,   0,    0,   2},
        { 10,   5,   0,   9,    9,   1,    0,   0}};
    g.loadGraph(graph4);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle");  

    
}
