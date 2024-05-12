// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#include <iostream>
#include "Graph.hpp"

namespace ariel{
        
        void Graph::loadGraph(const std::vector<std::vector<int>> &input_matrix){
            
            if(input_matrix.size() == 0) throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            if(input_matrix[0].size() == 0) throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            
            size_t rows_number = input_matrix.size();
            for(const auto &col : input_matrix){ // going over all the rows
                if(col.size() != rows_number){
                    throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
                }
            }
            
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
            size_t n = this->adj_matrix[0].size();
            size_t edges_counter = 0;
            for(size_t i=0; i<n; i++){
                for(size_t j=0; j<n; j++){
                    if(this->adj_matrix[i][j] != 0){
                        edges_counter++;
                    }
                }
            }
            printf("In this graph: %zu vertices and %zu edges.\n", n, edges_counter);
        }

        size_t Graph::size(){
            return this->adj_matrix[0].size();
        }

};
