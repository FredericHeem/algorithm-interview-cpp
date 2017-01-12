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
    std::priority_queue< Edge<T, TWeight>, std::vector<Edge<T, TWeight> >, prioritize > pq;
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

    auto parentIt = parentMap.find(target);

    paths.push_front(target);
    while(parentIt != parentMap.end()){
        const auto &parent = (*parentIt).second;
        parentIt = parentMap.find(parent);
        paths.push_front(parent);
    }
}
