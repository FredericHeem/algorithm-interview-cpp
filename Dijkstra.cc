#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cassert>

using namespace std;

template <typename TKey = std::string, typename TWeight = int>
struct Edge {
    TKey id;
    TWeight weight;
    Edge(TKey id, TWeight weight) : id(id), weight(weight){} 
};

template<typename TKey = std::string, typename TWeight = int>
struct Node {
    TKey id;
    typedef std::vector<Edge<TKey, TWeight> > Neighbors;
    Neighbors neighbors;
    Node(TKey id) : id(id){};
    Node(TKey id, const Neighbors& neighbors) : id(id), neighbors(neighbors){};
};

template<typename TKey = std::string, typename TWeight = int>
struct Graph {
    typedef std::unordered_map<TKey, Node<TKey, TWeight> > Nodes;
    Nodes nodes;
    Graph() {}
    Graph(const Nodes& nodes): nodes(nodes){}
};

template<typename T = std::string, typename TWeight = int>
struct DikjstraVisitor {
    virtual void processNode(T id){};
    virtual void nodeNotFound(T id){};
    virtual void addNodeToVisit(T id){};
};

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


template<typename T = std::string, typename TWeight = int>
void dikjstra(const Graph<T, TWeight> &graph,
              const T &source,
              const T &target, 
              DikjstraVisitor<T, TWeight> &visitor){
    std::unordered_map<T, TWeight> distanceMap;
    std::unordered_set<T> visitedSet;
    struct prioritize{ 
        bool operator ()(Edge<T, TWeight>& e1,
                         Edge<T, TWeight>& e2){
            return e1.weight > e2.weight;
        }
    };
    std::priority_queue< Edge<T, TWeight>, vector<Edge<T, TWeight> >, prioritize > pq;
    pq.push({source, 0});
    
    while(!pq.empty())
    {
        auto nodeDistance = pq.top();
        pq.pop();
        visitor.processNode(nodeDistance.id);
        auto nodeIt = graph.nodes.find(nodeDistance.id);
        if(nodeIt == graph.nodes.end()){
            visitor.nodeNotFound(nodeDistance.id);
            continue;
        }
        auto &node = nodeIt->second;
        
        auto isVisited = visitedSet.find(node.id);
        if(isVisited != visitedSet.end()) continue;
        visitedSet.emplace(node.id);
            
        for(auto neighbor : node.neighbors){
            auto newDist = distanceMap[node.id] + neighbor.weight;
            auto distanceIt = distanceMap.find(neighbor.id);
            if((distanceIt == distanceMap.end()) || (newDist < distanceIt->second)){
                distanceMap[neighbor.id] = newDist;
                visitor.addNodeToVisit(neighbor.id);
                pq.push({neighbor.id, newDist});
            }
        }
    }
    
    for(auto &kv: distanceMap){
        cout << "distance  node: " << kv.first << ", dist " << kv.second << endl;
    }
}

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

void testGraphString(){
    std::cout << "******* Dijkstra , node with string as key, use initialization list\n";
    Graph<> graph({
        { "A", {"A", {{"B", 5}, {"C", 1}}} },
        { "B", {"B", {{"D", 2}}} },
        { "C", {"C", {{"D", 9}}} },
        { "D", {"D"} }
    });
    
    displayNode<>(graph.nodes);
    auto visitor = DikjstraVisitorLog<>();
    dikjstra<string, int>(graph, "A", "D", visitor);
}

void testGraphInt(){
    std::cout << "****** Dijkstra, node with int as key\n";
    Graph<int, int> graph({
        { 1, {1, {{2, 5}, {3, 3}}} },
        { 2, {2, {{4, 2}}} },
        { 3, {3, {{4, 1}}} },
        { 4, {4} }
    });
        
    displayNode<>(graph.nodes);
    auto visitor = DikjstraVisitorLog<int, int>();
    dikjstra<int, int>(graph, 1, 4, visitor);
}

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
    dikjstra<string, int>(graph, "A", "D", visitor);
}


int main()
{
    std::cout << "Dijkstra\n";
    testGraphString();
    //testGraphInt();
    //testGraphManualEmplace();
}
