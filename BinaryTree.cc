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
    ~Tree(){
        clear();
    }
    
    void clear(){
        clear(root);
        root = nullptr;
    }
    
    void clear(Node<T> *node){
        if(!node){
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
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

    Node<T>* minNode(Node<T>* node){
        Node<T>* minNode = node;
        while(minNode->left){
            minNode = minNode->left;
        }
        return minNode;
    }
    
    Node<T>* remove(const T& value, Node<T>* node){
        cout << "remove " << value << " node value " << node->value << endl;
        if(node == nullptr){
            return nullptr;
        }
        if(value < node->value){
            node->left = remove(value, node->left);
        } else if(value > node->value){
            node->right = remove(value, node->right);
        } else {
            if(node->left && node->right){
                //Find the min value from the right node
                auto minNode = this->minNode(node->right);
                //Swap the value
                auto nodeValue = node->value;
                node->value = minNode->value;
                minNode->value = nodeValue;
                
                node->right = remove(nodeValue, node->right);
            } else {
                Node<T>* newChild = nullptr;
                if(node->left){
                     newChild = node->left;
                } else if(node->right){
                     newChild = node->right;
                }
                
                delete node;
                return newChild; 
            }
        }
        
        return node;
    }
    
    void remove(const T& value){
        root = remove(value, root);
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
    void breadthFirstSearch(Callback callback){
        if(!root){
            return;
        }
        std::queue<Node<T>* > queue;
        queue.push(root);
        
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
};


template<typename T>
void print(const T &value){
    std::cout << value << " ";  
};

int main() {
    cout << "BinaryTree" << endl;
    Tree<int> tree;
    
    assert(tree.root == nullptr);
    tree.insert(9);
    tree.insert(8);
    tree.insert(5);
    tree.insert(3);
    tree.insert(6);
    //tree.traverseInOrder(print<int>);
    cout << endl;
    //tree.breadthFirstSearch(print<int>);
    cout << endl; 

    int size = 0;
    auto count = [&size](const int &value){
        size++;
        std::cout << value << " ";
    };
    
    tree.traverseInOrder(count);
    cout << endl;
    
    tree.remove(5);
    tree.remove(9);
    tree.remove(8);
    tree.traverseInOrder(count);
    cout << endl; 
}
