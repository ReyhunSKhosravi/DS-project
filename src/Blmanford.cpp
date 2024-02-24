#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

enum class TransportType {
    Metro,
    Bus,
    Taxi,
};

struct Vertex {
    string name;
    unordered_map<Vertex*, pair<int, TransportType>> neighbors;

    explicit Vertex(const string& name) : name(name) {}
};

unordered_map<string, Vertex*> readGraphFromFile(const string& filename) {
    unordered_map<string, Vertex*> vertices;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string originName, destName;
        int weight;
        string transportTypeStr;
        if (iss >> originName >> destName >> weight >> transportTypeStr) {
            if (vertices.find(originName) == vertices.end()) {
                vertices[originName] = new Vertex(originName);
            }
            if (vertices.find(destName) == vertices.end()) {
                vertices[destName] = new Vertex(destName);
            }
            TransportType transportType;
            switch (stoi(transportTypeStr)) {
                case 1:
                    transportType = TransportType::Metro;
                    break;
                case 2:
                    transportType = TransportType::Bus;
                    break;
                case 3:
                    transportType = TransportType::Taxi;
                    break;
                default:
                    throw invalid_argument("Invalid transport type.");
            }
            vertices[originName]->neighbors[vertices[destName]] = make_pair(weight, transportType);
        }
    }
    file.close();
    return vertices;
}

void bellmanFord(unordered_map<string, Vertex*>& vertices, const string& sourceName) {
    unordered_map<string, int> distances;
    for (auto& vertex : vertices) {
        distances[vertex.first] = numeric_limits<int>::max();
    }
    distances[sourceName] = 0;

    for (size_t i = 0; i < vertices.size() - 1; ++i) {
        for (auto& vertex : vertices) {
            for (auto& neighbor : vertex.second->neighbors) {
                int weight = neighbor.second.first;
                if (distances[vertex.first] != numeric_limits<int>::max() && distances[vertex.first] + weight < distances[neighbor.first->name]) {
                    distances[neighbor.first->name] = distances[vertex.first] + weight;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (auto& vertex : vertices) {
        for (auto& neighbor : vertex.second->neighbors) {
            int weight = neighbor.second.first;
            if (distances[vertex.first] != numeric_limits<int>::max() && distances[vertex.first] + weight < distances[neighbor.first->name]) {
                throw runtime_error("Error: Graph contains negative weight cycle.");
            }
        }
    }

    // Print distances
    cout << "Shortest distances from " << sourceName << ":\n";
    for (auto& distance : distances) {
        cout << distance.first << ": " << distance.second << endl;
    }
}

int main() {
    try {
        string filename = "input.txt";
        unordered_map<string, Vertex*> vertices = readGraphFromFile(filename);
        string sourceName = "Yadegar-e_Emam";
        bellmanFord(vertices, sourceName);

        // Free allocated memory
        for (auto& vertex : vertices) {
            delete vertex.second;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
