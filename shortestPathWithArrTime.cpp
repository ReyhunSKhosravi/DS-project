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
            // cout << "i: " << i << " & " << originName << " & " << destName << " & " << weight << " & " << transportTypeStr << endl;
            // i++;
            
            if (vertexMap.count(originName) == 0) {
                // cout << endl << "j: " << j << "   -----------> " << originName << endl;
                // j++;
                Vertex* originVertex = new Vertex(originName);
                vertices.push_back(originVertex);
                vertexMap[originName] = originVertex;
            }
            if (vertexMap.count(destName) == 0) {
                // cout << endl << "j: " << j << "   -----------> " << destName << endl;
                // j++;
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
        // cout << "i" << i << " khat 93 : " << distance[vertex] << endl;
        // i++;
    }
    // cout << "size of vector: " << vertices.size() << endl;
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
        int time = 0;
        while (current) {
            path.push_back(current->name); //be saf baraye barersi ezafemishavad
            if (parent.find(current) != parent.end()) {
                transportTypes.push_back(current->neighbors[parent[current]].second);
            }
            current = parent[current];
        }
        int i = 0;
        string preTran = "none", preColor = "none";
        for (auto it = path.rbegin(), it2 = path.rbegin() + 1; it != path.rend(); ++it, ++it2) {
            ifstream findfile("input.txt");
            string linefile;
            string tempName, tempDes, tempWeight, tempTran, tempColor;
            cout << *it;
            // cout << "is it the next one? ---> " << *it2 << endl;
            cout << " (";
            switch (transportTypes.back()) {
                case TransportType::Subway:
                    cout << "Metro ";
                    while (getline(findfile, linefile))
                    {
                        istringstream iss(linefile);
                        iss >> tempName >> tempDes >> tempWeight >> tempTran >> tempColor;
                        if((tempName == *it) && (tempDes == *it2) && (tempTran == "SUBWAY")){
                            time += ( stoi(tempWeight) * 1);
                            if(preTran != tempTran){
                                if(tempTran == "BUS"){
                                    time += 15;
                                    preTran = tempTran;
                                }
                                if(tempTran == "SUBWAY"){
                                    time += 8;
                                    preTran = tempTran;
                                }
                                if(tempTran == "TAXI"){
                                    time += 5;
                                    preTran = tempTran;
                                }
                            }
                            if(preTran == "SUBWAY"){
                                if((tempTran == "SUBWAY") && (preColor != tempColor)){
                                    time += 8;
                                    preColor = tempColor;
                                }
                            }
                            else if(preTran == "BUS"){
                                if((tempTran == "BUS") && (preColor != tempColor)){
                                    time += 15;
                                    preColor = tempColor;
                                }
                            }
                            else if(preTran == "TAXI"){
                                if((tempTran == "TAXI") && (preColor != tempColor)){
                                    time += 15;
                                    preColor = tempColor;
                                }
                            }
                            
                            cout << " (dis : "<< stoi(tempWeight) << " / time: " << stoi(tempWeight) * 1 << ") ";
                        }
                    }
                    break;

                case TransportType::Bus:
                    cout << "Bus";
                    while (getline(findfile, linefile))
                    {
                        istringstream iss(linefile);
                        iss >> tempName >> tempDes >> tempWeight >> tempTran >> tempColor;
                        if((tempName == *it) && (tempDes == *it2) && (tempTran == "BUS")){
                            time += ( stoi(tempWeight) * 4);
                            if(preTran != tempTran){
                                if(tempTran == "BUS"){
                                    time += 15;
                                    preTran = tempTran;
                                }
                                if(tempTran == "SUBWAY"){
                                    time += 8;
                                    preTran = tempTran;
                                }
                                if(tempTran == "TAXI"){
                                    time += 5;
                                    preTran = tempTran;
                                }
                            }
                            if(preTran == "SUBWAY"){
                                if((tempTran == "SUBWAY") && (preColor != tempColor)){
                                    time += 8;
                                    preColor = tempColor;
                                }
                            }
                            else if(preTran == "BUS"){
                                if((tempTran == "BUS") && (preColor != tempColor)){
                                    time += 15;
                                    preColor = tempColor;
                                }
                            }
                            else if(preTran == "TAXI"){
                                if((tempTran == "TAXI") && (preColor != tempColor)){
                                    time += 15;
                                    preColor = tempColor;
                                }
                            }
                            cout << " (dis : "<< stoi(tempWeight) << " / time: " << stoi(tempWeight) * 4 << ") ";
                        }
                    }
                    break;

                case TransportType::Taxi:
                    cout << "Taxi";
                    while (getline(findfile, linefile))
                    {
                        istringstream iss(linefile);
                        iss >> tempName >> tempDes >> tempWeight >> tempTran >> tempColor;
                        if((tempName == *it) && (tempDes == *it2) && (tempTran == "TAXI")){
                            time += ( stoi(tempWeight) * 2);
                            if(preTran != tempTran){
                                if(tempTran == "BUS"){
                                    time += 15;
                                    preTran = tempTran;
                                }
                                if(tempTran == "SUBWAY"){
                                    time += 8;
                                    preTran = tempTran;
                                }
                                if(tempTran == "TAXI"){
                                    time += 5;
                                    preTran = tempTran;
                                }
                            }
                            if(preTran == "SUBWAY"){
                                if((tempTran == "SUBWAY") && (preColor != tempColor)){
                                    time += 8;
                                    preColor = tempColor;
                                }
                            }
                            else if(preTran == "BUS"){
                                if((tempTran == "BUS") && (preColor != tempColor)){
                                    time += 15;
                                    preColor = tempColor;
                                }
                            }
                            else if(preTran == "TAXI"){
                                if((tempTran == "TAXI") && (preColor != tempColor)){
                                    time += 15;
                                    preColor = tempColor;
                                }
                            }
                            cout << " (dis : "<< stoi(tempWeight) << " / time: " << stoi(tempWeight) * 2 << ") ";
                        }
                    }
                    break;
            }
            cout << ")";
            if (it + 1 != path.rend()) {
                cout << " -> ";
            }
            cout << endl;
            i++;
            transportTypes.pop_back();
        }
        cout << "Distance: " << distance[destination] << " km ~~~ and arriving time:" << time << " mins" << endl;
    }
}

int main() {
    try {
        string filename = "input.txt";
        vector<Vertex*> vertices = readGraphFromFile(filename);
        string originName = "Kashani";
        string destinationName = "Bimeh";
        dijkstra(vertices, originName, destinationName);
        for (Vertex* vertex : vertices) {
            delete vertex;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}