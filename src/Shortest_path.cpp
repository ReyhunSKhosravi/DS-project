#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

// Enum برای نوع وسایل نقلیه
enum class TransportType {
    Metro,
    Bus,
    Taxi
};

// ساختار برای نمایش یک راس در گراف
struct Vertex {
    string name;
    unordered_map<Vertex*, pair<int, TransportType>> neighbors;

    explicit Vertex(const string& name) : name(name) {}
};

// خواندن گراف از فایل
vector<Vertex*> readGraphFromFile(const string& filename) {
    vector<Vertex*> vertices;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
    }
    unordered_map<string, Vertex*> vertexMap;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string sourceName, destName;
        int weight;
        string transportTypeStr;
        if (iss >> sourceName >> destName >> weight >> transportTypeStr) {
            if (vertexMap.find(sourceName) == vertexMap.end()) {
                Vertex* sourceVertex = new Vertex(sourceName);
                vertices.push_back(sourceVertex);
                vertexMap[sourceName] = sourceVertex;
            }
            if (vertexMap.find(destName) == vertexMap.end()) {
                Vertex* destVertex = new Vertex(destName);
                vertices.push_back(destVertex);
                vertexMap[destName] = destVertex;
            }
            TransportType transportType;
            if (transportTypeStr == "1") {
                transportType = TransportType::Metro;
            } else if (transportTypeStr == "2") {
                transportType = TransportType::Bus;
            } else if (transportTypeStr == "3") {
                transportType = TransportType::Taxi;
            } else {
                throw invalid_argument("Invalid transport type.");
            }
            vertexMap[sourceName]->neighbors[vertexMap[destName]] = make_pair(weight, transportType);
        }
    }
    file.close();
    return vertices;
}

// الگوریتم دکسترا برای یافتن کوتاه‌ترین مسیر
void dijkstra(const vector<Vertex*>& vertices, const string& sourceName, const string& destinationName) {
    Vertex* source = nullptr;
    Vertex* destination = nullptr;
    for (Vertex* vertex : vertices) {
        if (vertex->name == sourceName) {
            source = vertex;
        } else if (vertex->name == destinationName) {
            destination = vertex;
        }
    }
    if (!source) {
        cerr << "Error: Source vertex not found." << endl;
        return;
    }
    if (!destination) {
        cerr << "Error: Destination vertex not found." << endl;
        return;
    }
    unordered_map<Vertex*, int> distance;
    for (Vertex* vertex : vertices) {
        distance[vertex] = numeric_limits<int>::max();
    }
    distance[source] = 0;
    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<pair<int, Vertex*>>> pq;
    pq.push({0, source});
    unordered_map<Vertex*, Vertex*> parent;
    while (!pq.empty()) {
        Vertex* u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();
        if (u == destination) {
            break;
        }
        for (auto& neighbor : u->neighbors) {
            Vertex* v = neighbor.first;
            int weight = neighbor.second.first;
            if (dist + weight < distance[v]) {
                distance[v] = dist + weight;
                pq.push({distance[v], v});
                parent[v] = u;
            }
        }
    }
    if (distance[destination] == numeric_limits<int>::max()) {
        cout << "No path exists between " << sourceName << " and " << destinationName << endl;
    } else {
        cout << "Shortest path from " << sourceName << " to " << destinationName << ": ";
        vector<string> path;
        vector<TransportType> transportTypes;
        Vertex* current = destination;
        while (current) {
            path.push_back(current->name);
            if (parent.find(current) != parent.end()) {
                transportTypes.push_back(current->neighbors[parent[current]].second);
            }
            current = parent[current];
        }
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it;
            cout << " (";
            switch (transportTypes.back()) {
                case TransportType::Metro:
                    cout << "Metro";
                    break;
                case TransportType::Bus:
                    cout << "Bus";
                    break;
                case TransportType::Taxi:
                    cout << "Taxi";
                    break;
            }
            cout << ")";
            transportTypes.pop_back();
            if (it + 1 != path.rend()) {
                cout << " -> ";
            }
        }
        cout << ", Distance: " << distance[destination] << endl;
    }
}

int main() {
    try {
        string filename = "input.txt";
        vector<Vertex*> vertices = readGraphFromFile(filename);
        string sourceName = "Boostan-e_laleh";
        string destinationName = "Meydan-e_Azadi";
        dijkstra(vertices, sourceName, destinationName);
        for (Vertex* vertex : vertices) {
            delete vertex;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
