#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>
//#include "graphClass.h"
#include "graphClass_2.h"

using namespace std;
using namespace chrono;

void readFile(ifstream&, Graph_2&, int);

int main(int argv, char* argc[]){
    try{
        int vertices, size = 10;

        ifstream infile(argc[1]);
        if(infile.bad()){
            cerr << "File could not be read" << endl;
        }

        infile >> vertices;
        Graph_2 graph(vertices);
        readFile(infile, graph, size);
        graph.bfs(1, 5);
        //graph.printMatrix();
        //graph.~Graph_2();

    }   
    catch(...) {
        cerr << "Error in program. Please debug" << endl;
    }    

    return 0;
}

void readFile(ifstream& infile, Graph_2& graph, int size){
    char line[size];
    int vertex1, vertex2;
    char* temp;
    while(!infile.eof()){

            infile >> line[0];
            infile.getline(&line[1], size-1);
            int i = 0, j = 0;
            temp = new char[size];
            assert(temp!=nullptr);

            while(line[i]!='\n'){
                if(line[i]=='-'){
                    vertex1 = atoi(temp);
                    delete [] temp;
                    temp = new char[size];
                    assert(temp!=nullptr);
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
            temp = nullptr;
            graph.addEdge(vertex1, vertex2);
            i=0;
            j=0;
        }
        infile.close();
}