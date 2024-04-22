#include <iostream>
#include "Graph.hpp"

namespace ariel{
        
        void Graph::loadGraph(const std::vector<std::vector<int>> &input_matrix){
            this->adj_matrix.clear();
            // loop over the rows:
            for(const auto &row : input_matrix){
                std::vector<int> new_row;  // creating a new row
                // loop over the cols:
                for(int value : row){
                    new_row.push_back(value);  // pushing into the new row
                }
                this->adj_matrix.push_back(new_row);  // pushing the new row into the adj matrix
            }
        }
    
        void Graph::printGraph(){
            int n = this->adj_matrix[0].size();
            int edges_counter = 0;
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    if(this->adj_matrix[i][j] > 0){
                        edges_counter++;
                    }
                }
            }
            printf("In this graph: %d vertices and %d edges.", n, edges_counter);
        }

        int Graph::size(){
            return this->adj_matrix[0].size();
        }

};
