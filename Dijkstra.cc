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
};

template<typename TKey = std::string, typename TWeight = int>
struct NodeDistance {
    TKey id;
    TWeight distance;
    NodeDistance(TKey id, TWeight distance) : id(id), distance(distance){} 
};

template<typename T = std::string, typename TWeight = int>
void dikjstra(const Graph<T, TWeight> &graph, const T &source, const T &target){
    std::unordered_map<T, TWeight> distanceMap;
    std::unordered_set<T> visitedSet;
    struct prioritize{ 
        bool operator ()(NodeDistance<T, TWeight>& nd1,
                         NodeDistance<T, TWeight>& nd2){
            return nd1.distance > nd2.distance;
        }
    };
    std::priority_queue< NodeDistance<T, TWeight>, vector<NodeDistance<T, TWeight> >, prioritize > pq;
    pq.push({source, 0});
    
    while(!pq.empty())
    {
        auto nodeDistance = pq.top();
        cout << "processing " << nodeDistance.id << ", #queues " << pq.size() << endl;
        pq.pop();
        auto nodeIt = graph.nodes.find(nodeDistance.id);
        if(nodeIt == graph.nodes.end()){
            cerr << "cannot found  " << nodeDistance.id << endl;
            assert(0);
            continue;
        }
        auto &node = nodeIt->second;
        for(auto neighbor : node.neighbors){
            auto isVisited = visitedSet.find(neighbor.id);
            if(isVisited != visitedSet.end()) continue;
            
            visitedSet.emplace(neighbor.id);
            
            auto newDist = distanceMap[node.id] + neighbor.weight;
            cout << "visiting neighbor " << neighbor.id << ", new dist: " << newDist << ", #visited: " << visitedSet.size() << endl;
            
            auto distanceIt = distanceMap.find(neighbor.id);
            if((distanceIt == distanceMap.end()) || (newDist < distanceIt->second)){
                distanceMap[neighbor.id] = newDist;
                cout << "pushing " << neighbor.id << ", newDist " << newDist << endl;
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
    std::cout << "******* Dijkstra , node with string as key\n";
    Graph<> graph;
    auto& nodes = graph.nodes;
    Node<> a("A", {{"B", 5}, {"C", 3}});
    nodes.emplace(a.id, a);
    
    Node<> b("B", {{"D", 5}});
    nodes.emplace(b.id, b);
    
    Node<> c("C", {{"D", 4}});
    nodes.emplace(c.id, c);

    Node<> d("D");
    nodes.emplace(d.id, d);
        
    displayNode<>(nodes);
    
    dikjstra<string, int>(graph, "A", "D");
}

void testGraphInt(){
    std::cout << "****** Dijkstra, node with int as key\n";
    Graph<int> graph;
    auto& nodes = graph.nodes;
    Node<int> a(1, {{2, 5}, {3, 3}});
    nodes.emplace(a.id, a);
    
    Node<int> b(2, {{4, 5}});
    nodes.emplace(b.id, b);
    
    Node<int> c(3, {{4, 4}});
    nodes.emplace(c.id, c);

    Node<int> d(4);
    nodes.emplace(d.id, d);
        
    displayNode<>(nodes);
    
    dikjstra<int, int>(graph, 1, 4);
}

int main()
{
    std::cout << "Dijkstra\n";
    testGraphString();
    testGraphInt();
}
