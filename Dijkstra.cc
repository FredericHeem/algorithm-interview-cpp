#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cassert>

using namespace std;

template <typename TNode>
struct Edge {
    TNode id;
    int weight;
    Edge(TNode id, int weight) : id(id), weight(weight){} 
};

template<typename TKey>
struct Node {
    TKey id;
    std::vector<Edge<TKey> > neighbors;
    Node(TKey id) : id(id){} 
};

template<typename TKey>
struct Graph {
    std::unordered_map<TKey, Node<TKey> > nodes;
};

template<typename TKey>
struct NodeDistance {
    TKey id;
    int distance;
    NodeDistance(TKey id, int distance) : id(id), distance(distance){} 
};

template<typename T>
void dikjstra(const Graph<T> &graph, T source, T target){
    std::unordered_map<T, int> distanceMap;
    std::unordered_set<T> visitedSet;
    struct prioritize{ bool operator ()(NodeDistance<T>& nd1, NodeDistance<T>& nd2){return nd1.distance > nd2.distance;}};
    std::priority_queue< NodeDistance<T>, vector<NodeDistance<T> >, prioritize > pq;
    pq.push({source, 0});
    
    while(!pq.empty())
    {
        auto nodeDistance = pq.top();
        cout << "processing " << nodeDistance.id << "#queues " << pq.size() << endl;
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
            if(distanceIt == distanceMap.end()){
                distanceMap[neighbor.id] = newDist;
                cout << "new distance" << newDist << ", #distances: " << distanceMap.size() << endl;
            } else {
                auto oldDist = distanceIt->second;
                if(newDist < oldDist){
                    distanceMap[neighbor.id] = newDist;
                    cout << "pushing " << neighbor.id << ", newDist " << newDist << endl;
                    pq.push({neighbor.id, newDist});
                }
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
    Graph<int> graph;
    auto& nodes = graph.nodes;
    Node<int> a(1);
    a.neighbors.push_back(Edge<int>(2, 5));
    a.neighbors.push_back(Edge<int>(3, 3));
    nodes.emplace(1, a);
    //nodes[1] = a;
    
    Node<int> b(2);
    b.neighbors.push_back(Edge<int>(1, 5));
    b.neighbors.push_back(Edge<int>(2, 4));
    nodes.emplace(2, b);
    
    Node<int> c(3);
    c.neighbors.push_back(Edge<int>(1, 5));
    nodes.emplace(3, c);

    auto nodeIt = graph.nodes.find(1);
    if(nodeIt == graph.nodes.end()){
        cerr << "cannot found  1" << endl;
        assert(0);
    }
        
    for(auto &kv: nodes){
        auto node = kv.second;
        cout << node.id << endl;
        for(auto neighbor : node.neighbors){
            cout << "    N " << neighbor.id << ", W " << neighbor.weight << endl;
        }
        
    }
    
    dikjstra<int>(graph, 1, 3);
    
}
