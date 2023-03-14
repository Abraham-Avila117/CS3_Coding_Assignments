#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>
//make function to put all the data reading code below
//input the num variable to the corrisponding connections. this will be a function of itself
using namespace std;
using namespace chrono;

int main(int argv, char* argc[]){

    try{
        int vertices, edges, row, col, size = 10;
        char line[size];
        ifstream infile(argc[1]);
        if(infile.bad()){
            cerr << "File could not be read" << endl;
        }

        infile >> vertices >> edges;
        vertices++;

        int adjacency_matrix[vertices][vertices];

        for(int i = 0; i < vertices; i++){
            for(int j = 0; j < vertices; j++){
                adjacency_matrix[i][j] = 0;
            }
        }  

        while(!infile.eof()){

            infile >> line[0];
            infile.getline(&line[1], size-1);

            int i = 0, j = 0;
            char* temp = new char[size];
            assert(temp!=nullptr);

            while(line[i]!='\n'){
                if(line[i]=='-'){
                    row = atoi(temp);
                    delete [] temp;
                    temp = new char[size];
                    j = 0;
                }
                else if(line[i+1]=='\n'){
                    col = atoi(temp);
                    delete [] temp;
                    temp = nullptr;
                }
                else{
                    temp[j] = line[i];
                    j++;
                }
                i++;
            }
            adjacency_matrix[row][col] = 1;
            delete [] temp;
            i=0;
            j=0;
        }
    }  
    catch(...) {
        cerr << "Error in program. Please debug" << endl;
    }    

    return 0;
}