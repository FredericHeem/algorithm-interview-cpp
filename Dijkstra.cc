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
        cout << "processing " << nodeDistance.id << endl;
        pq.pop();
        auto nodeIt = graph.nodes.find(nodeDistance.id);
        if(nodeIt == graph.nodes.end()){
            cerr << "cannot found  " << nodeDistance.id << endl;
            assert(0);
        }
        auto &node = nodeIt->second;
        for(auto neighbor : node.neighbors){
            auto isVisited = visitedSet.find(neighbor.id);
            if(isVisited != visitedSet.end()) continue;
            
            cout << "visiting " << neighbor.id << endl;
            visitedSet.emplace(neighbor.id);
            
            auto distanceIt = distanceMap.find(neighbor.id);
            if(distanceIt == distanceMap.end()){
                distanceMap[neighbor.id] = neighbor.weight;
            } else {
                auto oldDist = distanceIt->second;
                auto newDist = distanceMap[node.id] + neighbor.weight;
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
        for(auto neighbor : node.neighbors){
            cout << "    N " << neighbor.id << ", W " << neighbor.weight << endl;
        }
        cout << node.id << endl;
    }
    
    dikjstra<int>(graph, 1, 3);
    
}

/*

typedef pair<int, int> ii;   //The Only Macros I use...usually
typedef vector<int> vi;
vector<vector< ii > > graph;
 
int n;
vi dist;
 
void dijkstra(int s)
{
    dist.assign( graph.size() , 100000 ); dist[s] = 0;
    priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push({0, s});
 
    while(!pq.empty())
    {
        ii v = pq.top(); pq.pop();
 
        for(int i = 0 ; v.first < dist[v.second] && i < graph[v.second].size(); i++)
        {
            ii u = graph[v.second][i];
 
            if(dist[v.second] + u.second < dist[u.first])
                pq.push({dist[u.first] = dist[v.second] + u.second, u.first});
        }
 
    }
}
*/

//Implementation for Dijkstra's SSSP(Single source shortest path) algorithm
//This is an optimized algorithm running in O(E*log(V))

/*
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;
#define INF INT_MAX //Infinity

const int sz=10001; //Maximum possible number of vertices. Preallocating space for DataStructures accordingly
vector<pair<int,int> > a[sz]; //Adjacency list
int dis[sz]; //Stores shortest distance
bool vis[sz]={0}; //Determines whether the node has been visited or not

void Dijkstra(int source, int n) //Algorithm for SSSP
{
    for(int i=0;i<sz;i++) //Set initial distances to Infinity
        dis[i]=INF;
    //Custom Comparator for Determining priority for priority queue (shortest edge comes first)
    class prioritize{public: bool operator ()(pair<int, int>&p1 ,pair<int, int>&p2){return p1.second>p2.second;}};
    priority_queue<pair<int,int> ,vector<pair<int,int> >, prioritize> pq; //Priority queue to store vertex,weight pairs
    pq.push(make_pair(source,dis[source]=0)); //Pushing the source with distance from itself as 0
    while(!pq.empty())
    {
        pair<int, int> curr=pq.top(); //Current vertex. The shortest distance for this has been found
        pq.pop();
        int cv=curr.first,cw=curr.second; //'cw' the final shortest distance for this vertex
        if(vis[cv]) //If the vertex is already visited, no point in exploring adjacent vertices
            continue;
        vis[cv]=true;
        for(int i=0;i<a[cv].size();i++) //Iterating through all adjacent vertices
            if(!vis[a[cv][i].first] && a[cv][i].second+cw<dis[a[cv][i].first]) //If this node is not visited and the current parent node distance+distance from there to this node is shorted than the initial distace set to this node, update it
                pq.push(make_pair(a[cv][i].first,(dis[a[cv][i].first]=a[cv][i].second+cw))); //Set the new distance and add to priority queue
    }
}

int main() //Driver Function for Dijkstra SSSP
{
    int n,m,x,y,w;//Number of vertices and edges
    cout<<"Enter number of vertices and edges in the graph\n";
    cin>>n>>m;
    for(int i=0;i<m;i++) //Building Graph
    {
        cin>>x>>y>>w; //Vertex1, Vertex2, weight of edge
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    //cout<<"Enter source for Dijkstra's SSSP algorithm\n";
    int source;
    cin>>source;
    Dijkstra(source,n);//SSSP from source (Also passing number of vertices as parameter)
    cout<<"Source is: "<<source<<". The shortest distance to every other vertex from here is: \n";
    for(int i=1;i<=n;i++)//Printing final shortest distances from source
    {
        cout<<"Vertex: "<<i<<" , Distance: ";
        dis[i]!=INF? cout<<dis[i]<<"\n" : cout<<"-1\n";
    }
    return 0;
}
*/