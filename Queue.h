#ifndef Queue_h
#define Queue_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring> 
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <exception>

using namespace std;

template<class T>
struct Node{
    T item;
    Node<T>* next;
};

template<class T>
class Queue{
public:
    Queue();
    Queue(T);
    void enqueue(T);
    void dequeue();
    bool isEmpty() const;
    bool isInQueue(T) const;
    int getSize() const;
    T getFirst() const;
    T getLast() const;
    void printQueue() const;
    ~Queue();

private:
    Node<T>* first, *last;
    int size;
};

template<class T>
Queue<T>::Queue(){
    size = 0;
    first = last = nullptr;
}
    
template<class T>
Queue<T>::Queue(T item){
    size = 1;
    first = new Node<T>;
    first->item = item;
    first->next = nullptr;
    last = first;
}

template<class T>
void Queue<T>::enqueue(T item){
        if(isInQueue(item)){
        cout << "item already in queue" << endl;
        return;
    }
    else if(isEmpty()){
        first = new Node<T>;
        first->item = item;
        first->next = nullptr;
        last = first;
        size++;
        return;
    }
    else{
        Node<T>* temp;
        temp = new Node<T>;
        assert(temp!=nullptr);          
        temp->item = item;
        temp->next = nullptr;
        last->next = temp;
        last = temp;
        temp = nullptr;
        size++;
    }
}

template<class T>
void Queue<T>::dequeue(){
    if(!isEmpty()){
        Node<T>* temp = first;
        first = first->next;
        temp->next = nullptr;
        if(first == nullptr)
            last = nullptr;
        delete temp;
    }
}

template<class T>
bool Queue<T>::isEmpty() const{
    return (first == nullptr) && (last == nullptr);
}

template<class T>
bool Queue<T>::isInQueue(T search) const{
    Node<T>* temp = first;
    while (temp != nullptr){
        if(temp->item == search)
            return true;
        temp = temp->next;
    }
    return false;    
}

template<class T>
int Queue<T>::getSize() const{
    return size;
}

template<class T>
T Queue<T>::getFirst() const{
    return first->item;
}

template<class T>
T Queue<T>::getLast() const{
    return last->item;
}

template<class T>
void Queue<T>::printQueue() const{
    Node<T>* temp = first;
    if(isEmpty()){
        cout << "queue is empty" << endl;
        return;
    }
    while(temp != nullptr){
        cout << temp->item << " ";
        temp = temp->next;
    }
    cout << endl;
}

template<class T>
Queue<T>::~Queue(){
    while(!isEmpty())
        dequeue();
}

#endif