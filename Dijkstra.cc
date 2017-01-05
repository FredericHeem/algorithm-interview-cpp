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
    std::vector<Edge<TKey, TWeight> > neighbors;
    Node(TKey id) : id(id){} 
};

template<typename TKey = std::string, typename TWeight = int>
struct Graph {
    std::unordered_map<TKey, Node<TKey, TWeight> > nodes;
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

int main() //Driver Function for Dijkstra SSSP
{
    std::cout << "Dijkstra\n";
    Graph<> graph;
    auto& nodes = graph.nodes;
    Node<> a("A");
    a.neighbors.push_back(Edge<>("B", 5));
    a.neighbors.push_back(Edge<>("C", 3));
    nodes.emplace(a.id, a);
    
    Node<> b("B");
    b.neighbors.push_back(Edge<>("D", 5));
    nodes.emplace(b.id, b);
    
    Node<> c("C");
    c.neighbors.push_back(Edge<>("D", 4));
    nodes.emplace(c.id, c);

    Node<> d("D");
    nodes.emplace(d.id, d);
    
    auto nodeIt = graph.nodes.find("A");
    if(nodeIt == graph.nodes.end()){
        cerr << "cannot found  1" << endl;
        assert(0);
    }
        
    for(auto &kv: nodes){
        auto node = kv.second;
        cout << node.id << endl;
        for(auto neighbor : node.neighbors){
            cout << " " << neighbor.id << " " << neighbor.weight << endl;
        }
    }
    
    dikjstra<string, int>(graph, "A", "D");
    
}
