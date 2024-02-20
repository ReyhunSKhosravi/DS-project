#include <iostream>
#include <list>
#include <vector>

using namespace std;

// Define graph using adjacency list
class Graph {
    int V;              // Number of vertices
    vector<list<int>> adj; // Adjacency list

public:
    Graph(int V) : V(V) {
        adj.resize(V);
    }

    // Add edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v's list
    }

    // Helper function for DFS to find all possible paths between two vertices
    void DFSUtil(int v, int dest, vector<bool>& visited, vector<int>& path) {
        visited[v] = true; // Mark current vertex as visited

        // Add current vertex to path
        path.push_back(v);

        // If destination vertex is reached, print the path and return
        if (v == dest) {
            for (int i = 0; i < path.size(); ++i)
                cout << path[i] << " ";
            cout << endl;
        } else {
            // If destination vertex is not reached, recursively traverse adjacent vertices and call DFS
            for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
                if (!visited[*i])
                    DFSUtil(*i, dest, visited, path);
        }

        // Remove current vertex from path and mark it as unvisited
        path.pop_back();
        visited[v] = false;
    }

    // Find all possible paths between two vertices
    void findAllPaths(int src, int dest) {
        // Mark all vertices as unvisited
        vector<bool> visited(V, false);

        // For storing paths
        vector<int> path;

        // Use a helper function to find all paths
        DFSUtil(src, dest, visited, path);
    }
};

int main() {
    // Define the graph
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

    int src = 2, dest = 3;
    cout << "Following are all paths between " << src << " and " << dest << ":\n";
    g.findAllPaths(src, dest);

    return 0;
}
