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
#include "Queue.h"

using namespace std;

struct Vertex{
    int value = -1;
    int edges = 0;
    bool visited = false;
    Vertex* adjacency;
};

class Graph_3{
public: 
    Graph_3();
    Graph_3(int); //paramerterized for # of vertices
    void addEdge(int, int);
    bool positionCheck(int);
    void bfs(int, int);
    int getV();
    void printVertexEdges(int);
    void printEverything();
    void printPath(int);
    ~Graph_3();
private:
    int V; //number of vertices
    Vertex* vertices;
    int* shortPath;
    int* parent;
    Queue<int> queue;
    void reinitalizer();
};

Graph_3::Graph_3(){
    V = 51;

    vertices = new Vertex[V];
    assert(vertices!=nullptr);

    shortPath = new int[V];
    assert(shortPath!=nullptr);

    parent = new int[V];
    assert(parent!=nullptr);
}

Graph_3::Graph_3(int V){
    this->V = V;

    vertices = new Vertex[this->V];
    assert(vertices!=nullptr);

    shortPath = new int[this->V];
    assert(shortPath!=nullptr);

    parent = new int[this->V];
    assert(parent!=nullptr);
}

void Graph_3::addEdge(int vertex1, int vertex2){

    try{
        Vertex* node = new Vertex;
        assert(node!=nullptr);
        node->value = vertex1;

        if(vertices[vertex1].value == -1){ 
            node->adjacency = new Vertex[V];
            assert(node->adjacency!=nullptr);
            node->adjacency[node->edges++].value = vertex2;
            vertices[vertex1] = *node;
            node = nullptr;

            // same here but with the adjacent vertex
            if(vertices[vertex2].value == -1){ 
                Vertex* node2 = new Vertex;
                assert(node2!=nullptr);
                node2->value = vertex2;
                node2->adjacency = new Vertex[V];
                assert(node2->adjacency!=nullptr);
                vertices[vertex2] = *node2;
                node2 = nullptr;
            }

        }
        else if(vertices[vertex2].value == -1){
            Vertex* node2 = new Vertex;
            assert(node2!=nullptr);
            node2->value = vertex2;
            node2->adjacency = new Vertex[V];
            assert(node2->adjacency!=nullptr);
            vertices[vertex2] = *node2;
            node2 = nullptr;
            vertices[vertex1].adjacency[vertices[vertex1].edges++].value = vertex2;
            
        }
        else if(vertices[vertex1].adjacency[vertex2].value == vertices[vertex2].value){
            cout << "edge to " << vertex2 << " from " << vertex1 << " already exists\n";
            return;
        }
        else if(vertices[vertex1].adjacency[vertex2].value != vertices[vertex2].value){
            vertices[vertex1].adjacency[vertices[vertex1].edges++].value = vertex2;
        }
    }catch(bad_alloc ex){
        cerr << "allocation Error: " << ex.what() << endl;
    }

    if(!positionCheck(vertex1)){
        cout << "value 1 position in adjacency array does no match" << endl;
    }

    if(!positionCheck(vertex2)){
        cout << "value 2 position in adjacency array does no match" << endl;
    }
    reinitalizer();
}


bool Graph_3::positionCheck(int num){
    if(vertices[num].value == num)
        return true;
    return false;
}

void Graph_3::reinitalizer(){

    for(int i = 0; i < V; i++){
        vertices[i].visited = false;
    }

    for(int i = 0; i < V; i++)
        shortPath[i] = -1;
    
    for(int i = 0; i < V; i++)
        parent[i] = -1;
}

void Graph_3::bfs(int source, int destination){
    int vertex;
    reinitalizer();
    queue.enqueue(source);
    vertices[source].visited = true;
    parent[source] = destination;
    shortPath[source] = 0;

    while(!queue.isEmpty()){
        vertex = queue.getFirst();
        queue.dequeue();
        if(vertices[vertex].edges == 0){
            vertices[vertex].visited = true;
        }   
        else if(vertices[vertex].edges != 0){
            for(int j = 0; j < vertices[vertex].edges; j++){
                if(vertices[vertices[vertex].adjacency[j].value].visited == false){
                vertices[vertices[vertex].adjacency[j].value].visited = true;
                shortPath[vertices[vertex].adjacency[j].value] = shortPath[vertex] + 1;
                queue.enqueue(vertices[vertex].adjacency[j].value);
                parent[vertices[vertex].adjacency[j].value] = vertex;
                // if(vertices[vertex].adjacency[j].value == destination)
                //     printPath(destination);                    
                }
            }
        }
    }
    printPath(destination);
}

int Graph_3::getV(){
    return V;
}

void Graph_3::printVertexEdges(int n){
    for(int i = 0; i < V; i++){
        if(vertices[n].adjacency[i].value != -1)
            cout << vertices[n].adjacency[i].value << " "; 
    }
}

void Graph_3::printEverything(){
        for(int i = 0; i < V; i++){
            cout << "vertex: " << vertices[i].value << endl;
            cout << "with following edges: " << endl;
            for(int j = 0; j < vertices[i].edges; j++){
                cout << vertices[i].adjacency[j].visited << " " << endl;
            }
        }

}

void Graph_3::printPath(int destination){
    cout << "distance to " << destination << " is: ";
    cout << shortPath[destination] << endl;
    if(shortPath[destination]==-1){
        cout << "No path to destination" << endl;
        return;
    }
    else if(shortPath[destination]==0){
        cout << "Destination is itself" << endl;
        return;
    }

    cout << "Path to destination is: \n";

    int x = destination, path[V], i = 0;
    path[i++] = destination;
    while(parent[x]!=destination){
        path[i] = parent[x];
        x = parent[x];
        i++;
    }
    i--;
    for(;i >= 0; i--){
        cout << path[i] << " ";
    }
    cout << endl;
}

Graph_3::~Graph_3(){
    // fun fact: if you get the free(): double free detected in tcache 2 error, this
    // means that the deconstructor is not deleting stuff correctly. The
    // code below is the correct way to deconstruct the data structure
    for(int i = 0; i < V; i++){
        delete [] vertices[i].adjacency;
        vertices[i].adjacency = nullptr;
    } 
    delete [] vertices;
    vertices = nullptr;
}

#endif