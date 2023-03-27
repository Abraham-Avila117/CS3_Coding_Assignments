#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>
//#include "graphClass.h"
#include "graphClass_3.h"
//#include "graphClass_2.h"

using namespace std;
using namespace chrono;

void readFile(ifstream&, Graph_3&, int);
bool checkNegative(int[], int);
bool checkRange(int[], int, int);
void printDestination(ofstream&, Graph_3&, int[], int);

int main(int argv, char* argc[]){

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
        Graph_3 graph(vertices);
        readFile(infile, graph, size);

        sizeSource = sizeof(sources)/sizeof(int);
        sizeDestination = sizeof(destinatons)/sizeof(int);

        cout << "Provide 3 sources: ";
        cin >> sources[0] >> sources[1] >> sources[2];
        cout << endl;

        cout.rdbuf(stream_buffer_outfile);
        cout << "Provide 3 sources: " 
        << sources[0] << " " << sources[1] << " " << sources[2] << endl;
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
                if(sources[i]>vertices)
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
            printDestination(outfile, graph, sources, destinatons[0]);
            cout << "\tDestination 2: ";
            cin >> destinatons[1];
            printDestination(outfile, graph, sources, destinatons[1]);
            cout << "\tDestination 3: ";
            cin >> destinatons[2];
            printDestination(outfile, graph, sources, destinatons[2]);
        }
    }   
    catch(...) {
        cerr << "Error in program. Please debug" << endl;
    }    

    return 0;
}

void readFile(ifstream& infile, Graph_3& graph, int size){

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

void printDestination(ofstream& outfile, Graph_3& graph, int sources[], int destination){

    streambuf* stream_buffer_cerr = cerr.rdbuf();
    streambuf* stream_buffer_outfile = outfile.rdbuf();
    cerr.rdbuf(stream_buffer_outfile);

    cout << "Shortest path from vertex " << sources[0] << " to " << destination << ":\n";
    auto start = high_resolution_clock::now();
    graph.bfs(sources[0], destination);
    auto stop = high_resolution_clock::now();
    auto duration_nano = duration_cast<nanoseconds>(stop - start);
    cerr << "The time from " << sources[0] << " to " << destination <<
    " is " << duration_nano.count() << "ns" << endl;

    cout << "Shortest path from vertex " << sources[1] << " to " << destination << ":\n"; 
    auto start2 = high_resolution_clock::now();
    graph.bfs(sources[1], destination);
    auto stop2 = high_resolution_clock::now();
    auto duration_nano2 = duration_cast<nanoseconds>(stop2 - start2);
    cerr << "The time from " << sources[1] << " to " << destination <<
    " is " << duration_nano2.count() << "ns" << endl;

    cout << "Shortest path from vertex " << sources[2] << " to " << destination << ":\n";
    auto start3 = high_resolution_clock::now(); 
    graph.bfs(sources[2], destination);
    auto stop3 = high_resolution_clock::now();
    auto duration_nano3 = duration_cast<nanoseconds>(stop3 - start3);
    cerr << "The time from " << sources[2] << " to " << destination <<
    " is " << duration_nano3.count() << "ns" << endl;
    cout << endl;
}

bool checkRange(int check[], int size, int vertices){
    
    for(int i = 0; i < size; i++){
        if(check[i]>vertices)
            return true;
    }
    return false;
}