#ifndef graphClass_2_h
#define graphClass_2_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>
#include "Queue.h"

using namespace std;

class Graph_2{
public: 
    Graph_2();
    Graph_2(int); //paramerterized for # of vertices
    void addEdge(int, int);
   long long int bfs(int, int);
    void printPath(int,ofstream&);
    int getV();
    void printVertexEdges(int);
    void printMatrix();
    void reinitalizer();
    ~Graph_2();
private:
    int V; //number of vertices
    int** adjacency_matrix;
    bool* visited;
    int* shortestPath;
    int* path;
    Queue<int> queue;
};

Graph_2::Graph_2(){
    V = 51;

    adjacency_matrix = new int*[V];
    assert(*adjacency_matrix!=nullptr);
    for(int i = 0; i < V; i++){
        adjacency_matrix[i] = new int[V];
        assert(adjacency_matrix[i]!=nullptr);
        for(int j = 0; j < V; j++){
            adjacency_matrix[i][j] = 0;
        }
            
    }

    visited = new bool[V];
    assert(visited!=nullptr); 

    shortestPath = new int[V];
    assert(shortestPath!=nullptr);

    path = new int[V];
    assert(path!=nullptr);
}

Graph_2::Graph_2(int V){

    this->V = V+1;

    adjacency_matrix = new int*[this->V];
    assert(adjacency_matrix!=nullptr);
    for(int i = 0; i < this->V; i++){
        adjacency_matrix[i] = new int[this->V];
        assert(adjacency_matrix[i]!=nullptr);
        for(int j = 0; j < this->V; j++){
            adjacency_matrix[i][j] = 0;
        }
    }

    visited = new bool[this->V];
    assert(visited!=nullptr); 

    shortestPath = new int[this->V];
    assert(shortestPath!=nullptr);

    path = new int[this->V];
    assert(path!=nullptr);
}

void Graph_2::addEdge(int row, int col){
    if(adjacency_matrix[row][col] != 1)
        adjacency_matrix[row][col] = 1;       
}

long long int Graph_2::bfs(int source, int destination){
    long long int r_Return = 0;

    int row;
    queue.enqueue(source);
    visited[source] = true;
    shortestPath[source] = 0;
    path[source] = destination;
    auto timeStart = chrono::high_resolution_clock::now();

    if(source == destination)
    {
        auto timeStop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(timeStop - timeStart);
        cout << "Source is destination" << endl;
        r_Return = duration.count();
    }

    while(!queue.isEmpty()){
        row = queue.getFirst();
        queue.dequeue();
        for(int i = 0; i < V; i++){
            if(adjacency_matrix[row][i] == 1 && visited[i] == false){
                queue.enqueue(i);
                visited[i] = true;                
                shortestPath[i] = shortestPath[row] + 1;
                path[i] = row;   
                if(i == destination){
                    auto timeStop = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::nanoseconds>(timeStop - timeStart);
                    r_Return = duration.count();
                    return r_Return;
                }
            }
        }
    }

    auto timeStop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(timeStop - timeStart);
    cout<< "no path found." << endl;
    r_Return = duration.count();
    
    return r_Return;
}

void Graph_2::printPath(int destination, ofstream& out){
    streambuf* stream_buffer_cerr = cerr.rdbuf();
    streambuf* stream_buffer_out = out.rdbuf();
    cerr.rdbuf(stream_buffer_out);

    cout << "The distance to destination is: " << endl;
    cout << shortestPath[destination] << endl;
    cout << "the path from source to destination: " << endl;

    cerr << "The distance to destination is: " << endl;
    cerr << shortestPath[destination] << endl;
    cerr << "the path from source to destination: " << endl;

    int x = destination, pathPrint[V], i = 0;
    pathPrint[i++]=destination;
    while(path[x]!=destination){
        pathPrint[i] = path[x];
        x = path[x];
        i++;
    }
    i--;
    for(;i >=0; i--){
        cout << pathPrint[i] << " ";
        cerr << pathPrint[i] << " ";
    }
    cout << endl;
    cerr << endl;
}

int Graph_2::getV(){
    return V;
}

void Graph_2::printVertexEdges(int row){
    for(int i = 0; i < V; i++)
        cout << adjacency_matrix[row][i] << " ";
    cout << endl;
}

void Graph_2::printMatrix(){
    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            cout << adjacency_matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph_2::reinitalizer(){
    queue.~Queue();
    for(int i = 0; i < V; i++)
        visited[i] = false; 
    for(int i = 0; i < V; i++)
        shortestPath[i] = -1;
    for(int i = 0; i < V; i++)
        path[i] = -1;
}

Graph_2::~Graph_2(){
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

    queue.~Queue();
}


#endif