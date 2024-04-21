#include <iostream>
#include "Graph.hpp"

using namespace std;

class Graph{
    private:
        vector<vector<int>> adj_matrix;
    
    public:
        // constructor:
        Graph(){}

        // methods:
        /**
         * this function gets a matrix represented in 2d vector and copy it into the instance graph.
        */
        void loadGraph(const vector<vector<int>> &input_matrix){
            this->adj_matrix.clear();
            // loop over the rows:
            for(const auto &row : input_matrix){
                vector<int> new_row;  // creating a new row
                // loop over the cols:
                for(int value : row){
                    new_row.push_back(value);  // pushing into the new row
                }
                this->adj_matrix.push_back(new_row);  // pushing the new row into the adj matrix
            }
        }

        void printGraph(){
            for(int i=0; i<this->adj_matrix.size(); i++){
                printf("( ");
                for(int j=0; j<this->adj_matrix[i].size(); j++){
                    printf("%d ", this->adj_matrix[i][j]);
                }
                printf(")\n");
            }
        }

};
