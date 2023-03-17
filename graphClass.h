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

struct Adj{
    int value = -1;
    int edges = 0;
    bool visited = false;
    Adj** adjacency;
};

class Graph{
public: 
    Graph();
    Graph(int); //paramerterized for # of vertices
    void addEdge(int, int);
    bool pointerPositionCheck(int);
    void bfs();
    int getV();
    void printVertexEdges(int);
    ~Graph();
private:
    int V; //number of vertices
    Adj* vertices;
    Adj* shortPath;
};

Graph::Graph(){
    V = 51;
    vertices = new Adj[V];
    //assert(*vertices!=nullptr);
    assert(vertices!=nullptr);
    //for(int i = 0; i < V; i++){
     //   vertices[i] = nullptr;
    //}
    shortPath = new Adj[V];
}

Graph::Graph(int V){
    this->V = V+1;
    vertices = new Adj[this->V];
    //assert(*vertices!=nullptr);
    assert(vertices!=nullptr);
   // for(int i = 0; i < this->V; i++){
    //    vertices[i] = nullptr;
    //}
    shortPath = new Adj[this->V];
}

void Graph::addEdge(int vertex1, int vertex2){
    try{
        Adj* node = new Adj;
        assert(node!=nullptr);
        node->value = vertex1;

// if nothing is at the vertex value pointer position
// then make an Adj node and assign it to pointer position

        if(vertices[vertex1].value == -1){ 
            node->edges++;
            *(node->adjacency) = new Adj[V];
            assert(node->adjacency!=nullptr);
                for(int i = 0; i < V; i++){ //initialize pointer array within node
                    node->adjacency[i] = nullptr;
        }
        vertices[vertex1] = *node;

        // same here but with the adjacent vertex
        if(vertices[vertex2].value == -1){ 
            Adj* node2 = new Adj;
            assert(node2!=nullptr);
            node2->value = vertex2;
            *(node2->adjacency) = new Adj[V];
            for(int i = 0; i < V; i++){
                node2->adjacency[i] = nullptr;
            }
            vertices[vertex2] = *node2;
            node2 = nullptr;
        }

        vertices[vertex1].adjacency[vertex2] = &vertices[vertex2];
        }
        else if(vertices != nullptr){
            if(vertices[vertex1].adjacency[vertex2] == &vertices[vertex2]){
                cout << "edge to " << vertex2 << " from " << vertex1 << " already exists\n";
                return;
            }
            else if(vertices[vertex2].value == -1){
                Adj* node2 = new Adj;
                assert(node2!=nullptr);
                node2->value = vertex2;
                *(node2->adjacency) = new Adj[V];
                for(int i = 0; i < V; i++){
                    node2->adjacency[i] = nullptr;
                }
            vertices[vertex2] = *node2;
            node2 = nullptr;
        }
        vertices[vertex1].adjacency[vertex2] = &vertices[vertex2];
        }

        if(pointerPositionCheck(vertex1)){
            cout << "value 1 position in pointer array does no match" << endl;
        }

        if(pointerPositionCheck(vertex2)){
            cout << "value 2 position in pointer array does no match" << endl;
        }

    }catch(bad_alloc ex){
        cerr << "allocation Error: " << ex.what() << endl;
    }

}

bool Graph::pointerPositionCheck(int num){
    if(vertices[num].value == num)
    return true;
    return false;
}

void Graph::bfs(){

}

int Graph::getV(){
    return V;
}

void Graph::printVertexEdges(int n){
    for(int i = 0; i < V; i++){
        if(vertices[n].adjacency[i] != nullptr)
            cout << vertices[n].adjacency[i]->value << " "; 
    }
}

Graph::~Graph(){
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
        delete vertices[i].adjacency;
    delete [] vertices;
    vertices = nullptr;
}

#endif