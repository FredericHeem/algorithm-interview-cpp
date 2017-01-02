#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

template<typename T>
struct Node {
    T value;
    Node* left;
    Node* right;
    Node(T v) : value(v), left(nullptr), right(nullptr){
    }
};

template<typename T>
struct Tree {
    Node<T>* root;
    Tree() : root(nullptr){
        
    }

    void insert(Node<T>& node, const T& value){
        if(value < node.value){
            if(node.left == nullptr){
                node.left = new Node<T>(value);
            } else {
                insert(*node.left, value);
            }
        } else {
            if(node.right == nullptr){
                node.right = new Node<T>(value);
            } else {
                insert(*node.right, value);
            }
        }
    }
    
    void insert(const T& value){
        if(root == nullptr){
            root = new Node<T>(value);
        } else {
            insert(*root, value);
        }
    }

    template<typename Callback>
    void traverseInOrder(Node<T> *node, Callback callback){
        if(!node){
            return;
        }
        
        traverseInOrder(node->left, callback);
        callback(node->value);
        traverseInOrder(node->right, callback);
    }
    
    template<typename Callback>
    void traverseInOrder(Callback callback){
        traverseInOrder(root, callback);
    }
    
    template<typename Callback>
    void breadthFirstSearch(Node<T> *node, Callback callback){
        if(!node){
            return;
        }
        std::queue<Node<T>* > queue;
        queue.push(node);
        
        while(!queue.empty()){
            auto current = queue.front();
            queue.pop();
            callback(current->value);
            if(current->left){
                queue.push(current->left);  
            }
            if(current->right){
                queue.push(current->right);  
            }
        }
    }
    
    template<typename Callback>
    void breadthFirstSearch(Callback callback){
        breadthFirstSearch(root, callback);
    }
    
};


template<typename T>
void print(const T &value){
    std::cout << value << " ";  
};

int main() {
    cout << "BinaryTree" << endl;
    Tree<int> tree;
    
    assert(tree.root == nullptr);
    tree.insert(1);
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.traverseInOrder(print<int>);
    cout << endl;
    tree.breadthFirstSearch(print<int>);
    cout << endl; 
    
}
