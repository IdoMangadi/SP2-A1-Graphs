// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#include <iostream>
#include "Graph.hpp"

namespace ariel{

        /**
         * implementation of the deep copy constructor:
        */
        Graph::Graph(const Graph& g){
            this->adj_matrix.clear();  // clearing the adj matrix
            for(const auto &row : g.adj_matrix){  // going over the rows
                std::vector<int> new_row;  // creating a new row
                for(int value : row){  // going over the cols
                    new_row.push_back(value);  // pushing the value into the new row
                }
                this->adj_matrix.push_back(new_row);  // pushing the new row into the adj matrix
            }
        }
        
        void Graph::loadGraph(const std::vector<std::vector<int>> &input_matrix){
            
            // checking if the input matrix is a square matrix:
            if(input_matrix.size() == 0) throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");  // no rows in the matrix
            
            size_t rows_number = input_matrix.size();
            for(const auto &row : input_matrix){ // going over all the rows and checking if the number of cols is equal to the number of rows
                if(row.size() != rows_number){
                    throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
                }
            }
            
            this->adj_matrix.clear();  // clearing the adj matrix
            // loop over the rows:
            for(size_t i=0 ; i<rows_number ; i++){
                std::vector<int> new_row;  // creating a new row
                // loop over the cols:
                for(size_t j=0 ; j<rows_number ; j++){
                    if(i==j && input_matrix[i][j] != 0){  // checking if the graph has a self loop
                        this->adj_matrix.clear();  // clearing the adj matrix
                        throw std::invalid_argument("Invalid graph: The graph has a self loop.");
                    }
                    new_row.push_back(input_matrix[i][j]); // pushing the value into the new row
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
