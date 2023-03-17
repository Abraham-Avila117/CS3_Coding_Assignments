#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>
#include "graphClass.h"

using namespace std;
using namespace chrono;

int main(int argv, char* argc[]){
    try{
        int vertices, edges, vertex1, vertex2, size = 10;
        char line[size];
        ifstream infile(argc[1]);
        if(infile.bad()){
            cerr << "File could not be read" << endl;
        }

        infile >> vertices >> edges;
        Graph graph(vertices);

        while(!infile.eof()){

            infile >> line[0];
            infile.getline(&line[1], size-1);

            int i = 0, j = 0;
            char* temp = new char[size];
            assert(temp!=nullptr);

            while(line[i]!='\n'){
                if(line[i]=='-'){
                    vertex1 = atoi(temp);
                    delete [] temp;
                    temp = new char[size];
                    j = 0;
                }
                else if(line[i+1]=='\n'){
                    vertex2 = atoi(temp);
                    delete [] temp;
                    temp = nullptr;
                }
                else{
                    temp[j] = line[i];
                    j++;
                }
                i++;
            }
            delete [] temp;
            graph.addEdge(vertex1, vertex2);
            graph.printVertexEdges(1);
            i=0;
            j=0;
        }
    }  
    catch(...) {
        cerr << "Error in program. Please debug" << endl;
    }    

    return 0;
}