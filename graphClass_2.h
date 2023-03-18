#ifndef graphClass_h
#define graphClass_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>

using namespace std;

class Graph{
public: 
    Graph();
    Graph(int); //paramerterized for # of vertices
    void addEdge(int, int);
    void bfs();
    int getV();
    void printVertexEdges(int);
    ~Graph();
private:
    int V; //number of vertices
    int** adjacency_matrix;
    bool* visited;
    int* shortestPath;
};

Graph::Graph(){
    V = 51;

    int** adjacency_matrix = new int*[V];
    for(int i = 0; i < V; i++){
        adjacency_matrix[i] = new int[V];
        for(int j = 0; j < V; j++)
            adjacency_matrix[i][j] = 0;
    }

    visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false; 

    shortestPath = new int[V];
    for(int i = 0; i < V; i++)
        shortestPath[i] = -1;
}

Graph::Graph(int V){
    this->V = V+1;

    int** adjacency_matrix = new int*[V];
    for(int i = 0; i < V; i++){
        adjacency_matrix[i] = new int[V];
        for(int j = 0; j < V; j++)
            adjacency_matrix[i][j] = 0;
    }

    visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;   

    shortestPath = new int[V];
    for(int i = 0; i < V; i++)
        shortestPath[i] = -1;
}

void Graph::addEdge(int row, int col){
    if(adjacency_matrix[row][col] != 1)
        adjacency_matrix[row][col] = 1;
}

void Graph::bfs(){
    
}

int Graph::getV(){
    return V;
}

void Graph::printVertexEdges(int row){
    for(int i = 0; i < V; i++)
        cout << adjacency_matrix[row][i] << endl;
}

Graph::~Graph(){
    for(int i = 0; i < V; i++){
        delete [] adjacency_matrix[i];   
        adjacency_matrix[i] = nullptr;     
    }

    delete [] adjacency_matrix;
    adjacency_matrix = nullptr;

    delete [] visited;
    visited = nullptr;
    delete [] shortestPath;
    shortestPath = nullptr;
}


#endif