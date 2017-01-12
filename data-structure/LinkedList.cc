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
        auto node = new Node<T>(value);
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
        auto current = head;
        while(current != nullptr){
            current = current->next;
            size++;
        }
        return size;
    }
    void clear(){
        auto current = head;
        while(current != nullptr){
            auto next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    
    void reverse(){
        tail = head;
        auto current = head;
        Node<T>* previous = nullptr;
        while(current != nullptr){
            auto next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        head = previous;
    }
    void deleteNodeByValue(const T& val){
        auto current = head;
        Node<T>* previous = nullptr;
        while(current != nullptr){
            auto next = current->next;
            if(current->value == val){
                if(previous != nullptr){
                    previous->next = next;
                } else {
                    head = next;
                }
                if(current == tail){
                    tail = previous;
                }
                delete current;
            }
            previous = current;
            current = next;
        }
    }
};

int main() {
    cout << "LinkedList" << endl;
    List<int> list;
    assert(list.head == nullptr);
    assert(list.size() == 0);
    list.push_back(1);
    assert(list.head->value == 1);
    assert(list.tail->value == 1);
    assert(list.size() == 1);
    list.push_back(2);
    assert(list.size() == 2);
    
    list.reverse();
    assert(list.size() == 2);
    assert(list.head->value == 2);
    
    list.deleteNodeByValue(1);
    assert(list.size() == 1);
    
    list.deleteNodeByValue(2);
    assert(list.size() == 0);
    
    list.clear();
    assert(list.size() == 0);
    assert(list.head == nullptr);
    assert(list.tail == nullptr);
    
}
