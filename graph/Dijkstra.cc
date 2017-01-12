#include <iostream>
#include <vector>
#include <list>
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
    typedef std::vector<Node<TKey, TWeight> > Vertices;
    Nodes nodes;
    Graph() {}
    Graph(const Vertices& vertices){
      for(const auto& vertex: vertices){
        nodes.emplace(vertex.id, vertex);
      }
    }
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
              std::list<T> &paths,
              DikjstraVisitor<T, TWeight> &visitor){
    std::unordered_map<T, TWeight> distanceMap;
    std::unordered_map<T, T> parentMap;
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

        visitedSet.emplace(node.id);

        for(auto neighbor : node.neighbors){
            auto newDist = distanceMap[node.id] + neighbor.weight;
            auto distanceIt = distanceMap.find(neighbor.id);
            if((distanceIt == distanceMap.end()) || (newDist < distanceIt->second)){
                distanceMap[neighbor.id] = newDist;
                visitor.addNodeToVisit(neighbor.id);
                parentMap[neighbor.id] = node.id;
                if(visitedSet.find(neighbor.id) == visitedSet.end()){
                    pq.push({neighbor.id, newDist});
                }
            }
        }
    }

    for(auto &kv: distanceMap){
        cout << "distance  node: " << kv.first << ", dist " << kv.second << endl;
    }

    auto parentIt = parentMap.find(target);

    paths.push_front(target);
    while(parentIt != parentMap.end()){
        const auto &parent = (*parentIt).second;
        parentIt = parentMap.find(parent);
        paths.push_front(parent);
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
