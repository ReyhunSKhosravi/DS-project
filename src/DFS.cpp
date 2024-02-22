#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <limits>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<list<pair<int, int>>> adj; // Adjacency list
    map<string, int> verticesMap; // Map to store vertices as string to int

public:
    Graph() : V(0) {}

    // Function to add a new edge to the graph
    void addEdge(int v, int w, int weight) {
        adj[v].push_back(make_pair(w, weight));
    }

    // Function to add a new vertex to the graph
    void addVertex(string vertex) {
        if (verticesMap.find(vertex) == verticesMap.end()) {
            verticesMap[vertex] = V++;
            adj.resize(V);
        }
    }

    // Function to get the vertex number corresponding to the vertex name
    int getVertexNumber(string vertex) {
        if (verticesMap.find(vertex) != verticesMap.end()) {
            return verticesMap[vertex];
        }
        return -1;
    }

    // Depth-first search (DFS) algorithm to find the shortest path
    void DFSUtil(int v, int dest, vector<bool>& visited, vector<int>& path, vector<int>& shortestPath, int& shortestPathWeight) {
        visited[v] = true;
        path.push_back(v);

        if (v == dest) {
            int pathWeight = 0;
            for (int i = 0; i < path.size() - 1; ++i) {
                for (auto it = adj[path[i]].begin(); it != adj[path[i]].end(); ++it) {
                    if (it->first == path[i + 1]) {
                        pathWeight += it->second;
                        break;
                    }
                }
            }
            if (pathWeight < shortestPathWeight) {
                shortestPathWeight = pathWeight;
                shortestPath = path;
            }
        } else {
            for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
                if (!visited[i->first]) {
                    DFSUtil(i->first, dest, visited, path, shortestPath, shortestPathWeight);
                }
            }
        }

        path.pop_back();
        visited[v] = false;
    }

    // Function to find the shortest path between two vertices
    vector<int> findShortestPath(string srcStr, string destStr) {
        int src = verticesMap[srcStr];
        int dest = verticesMap[destStr];

        vector<bool> visited(V, false);
        vector<int> path, shortestPath;
        int shortestPathWeight = numeric_limits<int>::max();

        DFSUtil(src, dest, visited, path, shortestPath, shortestPathWeight);

        return shortestPath;
    }

    // Function to get the vertices map
    map<string, int> getVerticesMap() const {
        return verticesMap;
    }
};

int main() {
    // Create a graph instance
    Graph g;

    // Add vertices and edges to the graph
    g.addVertex("Meydan-e_Hazrat-e_ValiAsr");
    g.addVertex("Haftom-e_Tir");
    g.addVertex("Emam_Hossein");
    g.addVertex("Meydan-e_Shohada");
    g.addVertex("Shahid_Rezaei");
    g.addVertex("Haram-e_Hazrat-e_Abdolazim");

    g.addEdge(g.getVertexNumber("Meydan-e_Hazrat-e_ValiAsr"), g.getVertexNumber("Haftom-e_Tir"), 4);
    g.addEdge(g.getVertexNumber("Haftom-e_Tir"), g.getVertexNumber("Emam_Hossein"), 10);
    g.addEdge(g.getVertexNumber("Emam_Hossein"), g.getVertexNumber("Meydan-e_Shohada"), 4);
    g.addEdge(g.getVertexNumber("Meydan-e_Shohada"), g.getVertexNumber("Shahid_Rezaei"), 12);
    g.addEdge(g.getVertexNumber("Shahid_Rezaei"), g.getVertexNumber("Haram-e_Hazrat-e_Abdolazim"), 20);

    string srcStr = "Meydan-e_Hazrat-e_ValiAsr";
    string destStr = "Haram-e_Hazrat-e_Abdolazim";

    // Find the shortest path
    vector<int> shortestPath = g.findShortestPath(srcStr, destStr);

    // Display the shortest path
    cout << "Shortest path between " << srcStr << " and " << destStr << ":\n";
    for (int i = 0; i < shortestPath.size(); ++i) {
        for (auto it = g.getVerticesMap().begin(); it != g.getVerticesMap().end(); ++it) {
            if (it->second == shortestPath[i]) {
                cout << it->first << " ";
                break;
            }
        }
    }
    cout << endl;

    return 0;
}
