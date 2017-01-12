#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cassert>
#include "Dijkstra.h"

using namespace std;

template<typename T = std::string, typename TWeight = int>
struct DikjstraVisitorLog : public DikjstraVisitor<T, TWeight> {
    virtual void processNode(T id){
        cout << "Visiting node " << id << endl;
    };
    virtual void nodeNotFound(T id){
        cerr << "node not found: " << id << endl;
    };
    virtual void addNodeToVisit(T id){
        cerr << "addNodeToVisit: " << id << endl;
    };
};

template <class Nodes>
void displayNode(const Nodes &nodes){
      for(auto &kv: nodes){
        auto node = kv.second;
        cout << node.id << endl;
        for(auto neighbor : node.neighbors){
            cout << " " << neighbor.id << " " << neighbor.weight << endl;
        }
    }
}
template <class T = std::string>
void displayPath(const std::list<T> &path){
    for(auto &element: path){
        cout << element << " ";
    }
    cout << endl;
}

void testGraphString(){
    std::cout << "******* Dijkstra , one node\n";

    Graph<> graph({
      {"A", {{"B", 5}, {"C", 1}}},
      {"B", {{"D", 2}}} ,
      {"C", {{"D", 9}}} ,
      {"D"}
    });

    displayNode<>(graph.nodes);
    auto visitor = DikjstraVisitorLog<>();
    std::list<string> paths;
    dikjstra<string, int>(graph, "A", "A", paths, visitor);
    displayPath<>(paths);
}

void testGraphNoPath(){
    std::cout << "******* Dijkstra , no path\n";
    Graph<> graph({
        {"A", {{"B", 5}, {"C", 1}}},
        {"B", {{"C", 2}}},
        {"C", {{"B", 9}}},
        {"D"}
    });

    displayNode<>(graph.nodes);
    auto visitor = DikjstraVisitorLog<>();
    std::list<string> paths;
    dikjstra<string, int>(graph, "A", "D", paths, visitor);
    displayPath<>(paths);
}

void testGraphInt(){
    std::cout << "****** Dijkstra, node with int as key\n";
    Graph<int, int> graph({
        {1, {{2, 5}, {3, 3}}},
        {2, {{4, 2}}},
        {3, {{4, 1}}},
        {4 }
    });

    displayNode<>(graph.nodes);
    auto visitor = DikjstraVisitorLog<int, int>();
    std::list<int> paths;
    dikjstra<int, int>(graph, 1, 4, paths, visitor);
    displayPath<int>(paths);
}

/*
void testGraphManualEmplace(){
    std::cout << "******* Dijkstra , node with string as key, use emplace to add nodes\n";

    Graph<> graph;
    auto& nodes = graph.nodes;
    Node<> a("A", {{"B", 5}, {"C", 3}});
    nodes.emplace(a.id, a);

    Node<> b("B", {{"D", 1}});
    nodes.emplace(b.id, b);

    Node<> c("C", {{"D", 4}});
    nodes.emplace(c.id, c);

    Node<> d("D");
    nodes.emplace(d.id, d);

    displayNode<>(graph.nodes);
    auto visitor = DikjstraVisitor<>();
    std::list<string> paths;
    dikjstra<string, int>(graph, "A", "D", paths, visitor);
    displayPath<>(paths);

}

*/
int main()
{
    std::cout << "Dijkstra\n";
    testGraphString();
    testGraphNoPath();
    testGraphInt();
    //testGraphManualEmplace();
}
