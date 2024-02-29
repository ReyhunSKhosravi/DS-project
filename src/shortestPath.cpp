#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;


//------------------------------------------------------------------------------------------Enum for type of vehicles
enum class TransportType {
    Subway,
    Bus,
    Taxi,
};

//------------------------------------------------------------------------Structure to represent a vertex in the graph
struct Vertex {
    string name;
    unordered_map<Vertex*, pair<int, TransportType>> neighbors;
    
    explicit Vertex(const string& name) : name(name) {} // because one order in costructor->> explicit 
};

//--------------------------------------------------------------------------------------Read graph information from file
vector<Vertex*> readGraphFromFile(const string& filename) {
    vector<Vertex*> vertices;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
    }
    unordered_map<string, Vertex*> vertexMap;
    string line;
    int i = 0, j = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string originName, destName;
        int weight;
        string transportTypeStr; 
        if (iss >> originName >> destName >> weight >> transportTypeStr) {
            cout << "i: " << i << " & " << originName << " & " << destName << " & " << weight << " & " << transportTypeStr << endl;
            i++;
            
            if (vertexMap.count(originName) == 0) {
                cout << endl << "j: " << j << "   -----------> " << originName << endl;
                j++;
                Vertex* originVertex = new Vertex(originName);
                vertices.push_back(originVertex);
                vertexMap[originName] = originVertex;
            }
            if (vertexMap.count(destName) == 0) {
                cout << endl << "j: " << j << "   -----------> " << destName << endl;
                j++;
                Vertex* destVertex = new Vertex(destName);
                vertices.push_back(destVertex);
                vertexMap[destName] = destVertex;
            }
            // vertexMap.find(originName);
            TransportType transportType;
            if (transportTypeStr == "SUBWAY") {
                transportType = TransportType::Subway;
                // weight = 3267;
            } else if (transportTypeStr == "BUS") {
                transportType = TransportType::Bus;
                // weight = 2250;
            } else if (transportTypeStr == "TAXI") {
                transportType = TransportType::Taxi;
                // weight = weight * 6000;
            } else {
                throw invalid_argument("Invalid transport type.");
            }
            vertexMap[originName]->neighbors[vertexMap[destName]] = make_pair(weight, transportType);
        }
    }
    file.close();
    return vertices;
}

//----------------------------------------------------------------------------Algorithm (Dijkstra) to find the shortest path
void dijkstra(const vector<Vertex*>& vertices, const string& sourceName, const string& destinationName) {
    Vertex* origin = nullptr;
    Vertex* destination = nullptr;
    for (Vertex* vertex : vertices) {
        if (vertex->name == sourceName) {
            origin = vertex;
        } else if (vertex->name == destinationName) {
            destination = vertex;
        }
    }
    if (!origin) {
        cerr << "Error: origin vertex not found." << endl;
        return;
    }
    if (!destination) {
        cerr << "Error: Destination vertex not found." << endl;
        return;
    }
    //ye arraye baraye kotah tarin masir
    unordered_map<Vertex*, int> distance;
    int i = 0; // hame yal hayi ke bayad barresi shavad
    for (Vertex* vertex : vertices) {
        distance[vertex] = numeric_limits<int>::max();
        cout << "i" << i << " khat 93 : " << distance[vertex] << endl;
        i++;
    }
    cout << "size of vector: " << vertices.size() << endl;
    distance[origin] = 0; // node shorore dar ebteda 0
    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<pair<int, Vertex*>>> pq; //safe node hayi ke bayad barresi beshe
    pq.push({0, origin});
    unordered_map<Vertex*, Vertex*> parent;
    while (!pq.empty()) {
        Vertex* u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();
        if (u == destination) {
            break;
        }
        // barresi hame yal haye mojaver node
        for (auto& neighbor : u->neighbors) { 
            Vertex* v = neighbor.first; // maghsad
            int weight = neighbor.second.first;//vazne yal
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
            path.push_back(current->name); //be saf baraye barersi ezafemishavad
            if (parent.find(current) != parent.end()) {
                transportTypes.push_back(current->neighbors[parent[current]].second);
            }
            current = parent[current];
        }
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it;
            cout << " (";
            switch (transportTypes.back()) {
                case TransportType::Subway:
                    cout << "Metro ";
                    break;
                case TransportType::Bus:
                    cout << "Bus";
                    break;
                case TransportType::Taxi:
                    cout << "Metro/Taxi";
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
        string originName = "Bimeh";
        string destinationName = "Ostad_Mo'in";
        dijkstra(vertices, originName, destinationName);
        for (Vertex* vertex : vertices) {
            delete vertex;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}