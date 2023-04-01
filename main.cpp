/*
Program designed and developed by Abraham Avila, Arin Hartung, and Connor Thomas

Class: Intro To Algorithms (CS3)

Professor: Antoun Sherine

Description:
The following program takes in a txt-file with highest vertex plus one and 
takes in the adjacency list below into an adjacency matrix. The adjacency 
matrix tracks the entire graph. The class Graph_2 stores the adjacency matrix 
along with three other array to track when a node is visited, the shorest distance
(shortestPath), and the shorest path (path). All of these are dynamically allocated and 
the function bfs within the class retreieve shortest path and distance from on source
to a destination using queues to accomplish the task. The program takes in three inputs
from the user then outputs every time the user provides a desired destination to the 
screen and to a file.  

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>
#include "graphClass_2.h"

using namespace std;
using namespace chrono;

void readFile(ifstream&, Graph_2&, int);
bool checkNegative(int[], int);
bool checkRange(int[], int, int);
void printDestination(ofstream&, Graph_2&, int[], int);

int main(int argv, char* argc[]){
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "The local date and time is: " << dt << endl;

    try{
        auto start = high_resolution_clock::now();
        int vertices, size = 10, sources[3], sizeSource, destinatons[3], sizeDestination;

        ifstream infile(argc[1]);
        ofstream outfile;
        if(infile.bad()){
            cerr << "File could not be read" << endl;
        }        
        outfile.open("log.txt", ios::out);
        streambuf* stream_buffer_cout = cout.rdbuf();
        streambuf* stream_buffer_cerr = cerr.rdbuf();
        streambuf* stream_buffer_outfile = outfile.rdbuf();
        cerr.rdbuf(stream_buffer_outfile);
        
        infile >> vertices;
        Graph_2 graph(vertices);
        readFile(infile, graph, size);

        sizeSource = sizeof(sources)/sizeof(int);
        sizeDestination = sizeof(destinatons)/sizeof(int);
        
        cerr << "The local date and time is: " << dt << endl;
        
        cout << "Provide 3 sources: ";
        cin >> sources[0] >> sources[1] >> sources[2];
        cout << endl;

        cout.rdbuf(stream_buffer_outfile);
        cout << "Provide 3 sources: " 
        << sources[0] << " " << sources[1] << " " << sources[2] << endl << endl;
        cout.rdbuf(stream_buffer_cout);

        if(checkNegative(sources, sizeSource)){
            cout << "Input error: look into log.txt in your local directory" << endl;
            cerr << endl << "Invalid input: negative value" << endl;
            for(int i = 0; i < sizeSource; i++){
                if(sources[i]<0)
                    cerr << " {" << sources[i] << "} ";
                else
                    cerr << " " << sources[i];
            }
        auto stop = high_resolution_clock::now();
        auto duration_sec = duration_cast<seconds>(stop - start);
        cerr << endl << "Overall runtime of program: " << duration_sec.count() << "s" << endl;

        }else if(checkRange(sources, sizeDestination, vertices)){
            cout << "Input error: look into log.txt in your local directory" << endl;
            cerr << "Invalid input: out of node range" << endl;
            for(int i = 0; i < sizeSource; i++){
                if(sources[i]>=vertices)
                    cerr << " [" << sources[i] << "] ";
                else
                cerr << " " << sources[i];
            }
        auto stop = high_resolution_clock::now();
        auto duration_sec = duration_cast<seconds>(stop - start);
        cerr << endl << "Overall runtime of program: " << duration_sec.count() << "s" << endl;

        }else{
            cout << "\tDestination 1: ";
            cin >> destinatons[0];
            cerr << "First Destination: " << destinatons[0] << endl;
            printDestination(outfile, graph, sources, destinatons[0]);
            cout << "\tDestination 2: ";
            cin >> destinatons[1];
            cerr << "Second Destination: " << destinatons[1] << endl;
            printDestination(outfile, graph, sources, destinatons[1]);
            cout << "\tDestination 3: ";
            cin >> destinatons[2];
            cerr << "Third Destination: " << destinatons[2] << endl;
            printDestination(outfile, graph, sources, destinatons[2]);
            auto stop = high_resolution_clock::now();
            auto duration_sec = duration_cast<seconds>(stop - start);
            cerr << endl << "Overall runtime of program: " << duration_sec.count() << "s" << endl;

        }
    }   
    catch(...) {
        cerr << "Error in program. Please debug" << endl;
    }    

    return 0;
}

void readFile(ifstream& infile, Graph_2& graph, int size){

    char* str1, *str2;
    str1 = new char[size];
    str2 = new char[size];
    assert(str1!=nullptr);
    assert(str2!=nullptr);
    int vertex1, vertex2;

    while(!infile.eof()){
        infile >> str1[0];
        infile.getline(&str1[1], size, '-');
        vertex1 = atoi(str1);
        infile >> str2[0];
        infile.getline(&str2[1], size, '\n');
        vertex2 = atoi(str2);

        graph.addEdge(vertex1, vertex2);
        delete [] str1;
        delete [] str2;
        str1 = new char[size];
        str2 = new char[size];
        assert(str1!=nullptr);
        assert(str2!=nullptr);
    }
    delete [] str1;
    delete [] str2;
    str1 = nullptr;
    str2 = nullptr;
    infile.close();
}

bool checkNegative(int check[], int size){

    for(int i = 0; i < size; i++){
        if(check[i]<0)
            return true;
    }
    return false;
}

void printDestination(ofstream& outfile, Graph_2& graph, int sources[], int destination){

    streambuf* stream_buffer_cerr = cerr.rdbuf();
    streambuf* stream_buffer_outfile = outfile.rdbuf();
    cerr.rdbuf(stream_buffer_outfile);

    cout << "Shortest path from vertex " << sources[0] << " to " << destination << ":\n";
    graph.reinitalizer();
    long long int Time_nano1 = graph.bfs(sources[0], destination);
    graph.printPath(destination, outfile);
    cout << "The time from " << sources[0] << " to " << destination <<
    " is " << Time_nano1 << "ns" << endl;
    cerr << "The time from " << sources[0] << " to " << destination <<
    " is " << Time_nano1 << "ns" << endl;

    cout << "Shortest path from vertex " << sources[1] << " to " << destination << ":\n";
    graph.reinitalizer();
    long long int Time_nano2 = graph.bfs(sources[1], destination);
    graph.printPath(destination, outfile);
    cout << "The time from " << sources[1] << " to " << destination <<
    " is " << Time_nano2 << "ns" << endl;
    cerr << "The time from " << sources[1] << " to " << destination <<
    " is " << Time_nano2 << "ns" << endl;

    cout << "Shortest path from vertex " << sources[2] << " to " << destination << ":\n";
    graph.reinitalizer();
    long long int Time_nano3 = graph.bfs(sources[2], destination);
    graph.printPath(destination, outfile);
    cout << "The time from " << sources[2] << " to " << destination <<
    " is " << Time_nano3 << "ns" << endl;
    cerr << "The time from " << sources[2] << " to " << destination <<
    " is " << Time_nano3 << "ns" << endl << endl;
    cout << endl;
}

bool checkRange(int check[], int size, int vertices){
    
    for(int i = 0; i < size; i++){
        if(check[i]>=vertices)
            return true;
    }
    return false;
}
