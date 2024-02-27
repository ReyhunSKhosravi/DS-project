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
    Subway = 3267,
    Bus = 2250,
    Taxi = 6000,
};

//------------------------------------------------------------------------Structure to represent a vertex in the graph
struct Vertex {
    string name;
    string TransportationType, ColorOfLine;
    unordered_map<Vertex*, pair<int, TransportType> > neighbors;

    explicit Vertex(const string& name, const string& ColorOfLine, const string& TransportationType) : name(name), ColorOfLine(ColorOfLine), TransportationType(TransportationType){} // because one order in costructor->> explicit 
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
    while (getline(file, line)) {
        istringstream iss(line);
        string originName, destName;
        int weight;
        string transportTypeStr, lineColor;
        if (iss >> originName >> destName >> weight >> transportTypeStr >> lineColor) {
            if (vertexMap.find(originName) == vertexMap.end()) {
                //if it cant find a vertex with originname, it will create that:
                Vertex* originVertex = new Vertex(originName, lineColor, transportTypeStr);
                vertices.push_back(originVertex);
                vertexMap[originName] = originVertex;
            }
            if (vertexMap.find(destName) == vertexMap.end()) {
                //if it cant find a vertex with destname, it will create that:
                Vertex* destVertex = new Vertex(destName, lineColor, transportTypeStr);
                vertices.push_back(destVertex);
                vertexMap[destName] = destVertex;
            }
            TransportType transportType;
            if (transportTypeStr == "SUBWAY") {
                transportType = TransportType::Subway;
                weight = 3267;
            } else if (transportTypeStr == "BUS") {
                transportType = TransportType::Bus;
                weight = 2250;
            } else if (transportTypeStr == "TAXI") {
                transportType = TransportType::Taxi;
                weight = weight * 6000;
            } else {
                throw invalid_argument("Invalid transport type.");
            }
            vertexMap[originName]->neighbors[vertexMap[destName]] = make_pair(weight, transportType);
        }
    }
    file.close();
    return vertices;
}

//----------------------------------------------------------------------------Algorithm (Dijkstra) to find the lowest cost
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
    unordered_map<Vertex*, int> moneyCost; // hame yal hayi ke bayad barresi shavad
    for (Vertex* vertex : vertices) {
        moneyCost[vertex] = numeric_limits<int>::max();
    }
    moneyCost[origin] = 0; // node shorore dar ebteda 0
    priority_queue<pair <int, Vertex*>, vector<pair<int, Vertex*> >, greater< pair<int, Vertex*> > > pq; //safe node hayi ke bayad barresi beshe
    pq.push({0, origin});
    unordered_map<Vertex*, Vertex*> parent;
    while (!pq.empty()) {
        Vertex* u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();
        if (u == destination) {
            break;
        }
        string tempColorSubLine = "None", tempColorBusLine = "None";
        // barresi hame yal haye mojaver node
        for (auto& neighbor : u->neighbors) {
            if(neighbor.first->TransportationType == "TAXI"){
                cout << "residam khat 115"  << endl;
                Vertex* v = neighbor.first; // maghsad
                int weight = neighbor.second.first;//vazne yal
                if (dist + weight < moneyCost[v]) {
                    moneyCost[v] = dist + weight;
                    pq.push({moneyCost[v], v});
                    parent[v] = u;
                }
            }
            else if(neighbor.first->TransportationType == "BUS"){
                cout << "residam khat 125"  << endl;
                cout << "color bus line: " << tempColorBusLine << endl;
                if(tempColorBusLine != neighbor.first->ColorOfLine){
                    tempColorBusLine = neighbor.first->ColorOfLine;
                    Vertex* v = neighbor.first; // maghsad
                    int weight = neighbor.second.first;//vazne yal
                    if (dist + weight < moneyCost[v]) {
                    moneyCost[v] = dist + weight;
                    pq.push({moneyCost[v], v});
                    parent[v] = u;
                    }
                }
            }
            else if(neighbor.first->TransportationType == "SUBWAY"){
                cout << "residam khat 139"  << endl;
                cout << "color subway line: " << tempColorSubLine << endl;
                if(neighbor.first->ColorOfLine != tempColorSubLine){
                    tempColorSubLine = neighbor.first->ColorOfLine;
                    Vertex* v = neighbor.first; // maghsad
                    int weight = neighbor.second.first;//vazne yal
                    if (dist + weight < moneyCost[v]) {
                    moneyCost[v] = dist + weight;
                    pq.push({moneyCost[v], v});
                    parent[v] = u;
                    }
                }
            }
            
        }
    }
    if (moneyCost[destination] == numeric_limits<int>::max()) {
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
                    cout << "Subway ";
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
        cout << ", Distance: " << moneyCost[destination] << endl;
    }
}

int main() {
    try {
        string filename = "input.txt";
        vector<Vertex*> vertices = readGraphFromFile(filename);
        string originName = "Ferdowsi";
        string destinationName = "Ebn-e_Sina";
        dijkstra(vertices, originName, destinationName);
        for (Vertex* vertex : vertices) {
            delete vertex;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}