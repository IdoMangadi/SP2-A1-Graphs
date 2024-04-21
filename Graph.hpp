#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

#ifndef ARIEL_NS
#define ARIEL_NS

namespace ariel{
    class Graph{
        private: 
            std::vector<std::vector<int>> adj_matrix;
        public:
            Graph(){}
            void loadGraph(const std::vector<std::vector<int>> &input_matrix);
            void printGraph();
    };
}
#endif // ARIEL_NS

#endif // GRAPH_HPP
