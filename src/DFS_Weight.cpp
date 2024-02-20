#include <iostream>
#include <list>
#include <vector>
#include <limits>

using namespace std;

// Define graph using adjacency list
class Graph {
    int V;              // Number of vertices
    vector<list<pair<int, int>>> adj; // Adjacency list

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Add weighted edge to the graph
    void addEdge(int v, int w, int weight) {
        adj[v].push_back(make_pair(w, weight)); // Add w to v's list with weight
    }

    // Helper function for DFS to find the shortest path between two vertices
    void DFSUtil(int v, int dest, vector<bool>& visited, vector<int>& path, vector<int>& shortestPath, int& shortestPathWeight) {
        visited[v] = true; // Mark current vertex as visited

        // Add current vertex to path
        path.push_back(v);

        // If destination vertex is reached
        if (v == dest) {
            // Calculate the weight of the current path
            int pathWeight = 0;
            for (int i = 0; i < path.size() - 1; ++i) {
                for (auto it = adj[path[i]].begin(); it != adj[path[i]].end(); ++it) {
                    if (it->first == path[i + 1]) {
                        pathWeight += it->second;
                        break;
                    }
                }
            }

            // If the weight of the current path is less than the weight of the shortest path found so far
            if (pathWeight < shortestPathWeight) {
                shortestPathWeight = pathWeight;
                shortestPath = path;
            }
        } else {
            // If destination vertex is not reached, recursively traverse adjacent vertices and call DFS
            for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
                if (!visited[i->first])
                    DFSUtil(i->first, dest, visited, path, shortestPath, shortestPathWeight);
        }

        // Remove current vertex from path and mark it as unvisited
        path.pop_back();
        visited[v] = false;
    }

    // Find the shortest path between two vertices
    vector<int> findShortestPath(int src, int dest) {
        // Mark all vertices as unvisited
        vector<bool> visited(V, false);

        // For storing the shortest path
        vector<int> path, shortestPath;

        // Initialize shortest path weight to maximum value
        int shortestPathWeight = numeric_limits<int>::max();

        // Use DFS to find the shortest path
        DFSUtil(src, dest, visited, path, shortestPath, shortestPathWeight);

        return shortestPath;
    }
};
int main() {
    // Define the graph
    Graph g(6);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 9);
    g.addEdge(3, 4, 7);
    g.addEdge(3, 5, 8);
    g.addEdge(4, 5, 4);

    int src = 0, dest = 5;
    cout << "Shortest path between " << src << " and " << dest << ":\n";
    vector<int> shortestPath = g.findShortestPath(src, dest);
    for (int i = 0; i < shortestPath.size(); ++i)
        cout << shortestPath[i] << " ";
    cout << endl;

    return 0;
}