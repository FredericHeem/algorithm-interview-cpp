#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
struct Node {
    T value;
    Node* next;
    Node(T v) : value(v), next(nullptr){
        
    }
};

template<typename T>
struct List {
    Node<T>* head;
    Node<T>* tail;
    List() : head(nullptr), tail(nullptr){
        
    }
    void push_back(const T& value){
        Node<T>* node = new Node<T>(value);
        if(head == nullptr){
            head = node;
            tail = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    int size(){
        int size = 0;
        Node<T>* current = head;
        while(current != nullptr){
            current = current->next;
            size++;
        }
        return size;
    }
};

int main() {
    cout << "LinkedList" << endl;
    List<int> list;
    assert(list.head == nullptr);
    assert(list.size() == 0);
    list.push_back(1);
    assert(list.size() == 1);
    
    
}
