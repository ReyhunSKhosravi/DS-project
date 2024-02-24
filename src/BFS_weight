#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

enum class TransportType {
    Metro,
    Bus,
    Taxi,
};

enum class Colour {
    RED = 1,
    BLUE = 2,
    YELLOW = 3,
    PINK = 4,
    GRAY = 5,
    GREEN = 6,
    BROWN = 7,
    YELLOW_Dark = 8,
    GREEN_Dark = 9,
};

struct Vertex {
    string name;
    unordered_map<Vertex*, pair<int, TransportType>> neighbors;
    Colour colour;

    explicit Vertex(const string& name, Colour colour) : name(name), colour(colour) {}
};

struct PathResult {
    vector<pair<string, TransportType>> path;
    int distance;
};

Colour intToColour(int colourCode) {
    switch(colourCode) {
        case 1:
            return Colour::RED;
        case 2:
            return Colour::BLUE;
        case 3:
            return Colour::YELLOW;
        case 4:
            return Colour::PINK;
        case 5:
            return Colour::GRAY;
        case 6:
            return Colour::GREEN;
        case 7:
            return Colour::BROWN;
        case 8:
            return Colour::YELLOW_Dark;
        case 9:
            return Colour::GREEN_Dark;
        default:
            throw invalid_argument("Invalid colour code.");
    }
}

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
        int weight, transportTypeCode, colourCode;
        if (iss >> originName >> destName >> weight >> transportTypeCode >> colourCode) {
            Colour colour = intToColour(colourCode);
            if (vertices.find(originName) == vertices.end()) {
                vertices[originName] = new Vertex(originName, colour);
            }
            if (vertices.find(destName) == vertices.end()) {
                vertices[destName] = new Vertex(destName, colour);
            }
            TransportType transportType;
            switch (transportTypeCode) {
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

PathResult findShortestPath(const unordered_map<string, Vertex*>& vertices, const string& sourceName, const string& destinationName) {
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;
    for (auto& vertex : vertices) {
        distances[vertex.first] = numeric_limits<int>::max();
    }
    distances[sourceName] = 0;
    queue<string> q;
    q.push(sourceName);
    while (!q.empty()) {
        string currentName = q.front();
        q.pop();
        Vertex* current = vertices.at(currentName);
        if (currentName == destinationName) {
            break;
        }
        for (auto& neighbor : current->neighbors) {
            Vertex* next = neighbor.first;
            int weight = neighbor.second.first;
            int newDist = distances[currentName] + weight;
            if (newDist < distances[next->name]) {
                distances[next->name] = newDist;
                q.push(next->name);
                previous[next->name] = currentName;
            }
        }
    }
    vector<pair<string, TransportType>> shortestPath;
    string current = destinationName;
    int totalDistance = distances[destinationName];
    while (current != sourceName) {
        Vertex* vertex = vertices.at(current);
        string prevName = previous.at(current);
        for (auto& neighbor : vertex->neighbors) {
            Vertex* prev = neighbor.first;
            if (prev->name == prevName) {
                shortestPath.push_back({current, neighbor.second.second});
                current = prevName;
                break;
            }
        }
    }
    reverse(shortestPath.begin(), shortestPath.end());
    return {shortestPath, totalDistance};
}

string transportTypeToString(TransportType type) {
    switch(type) {
        case TransportType::Metro:
            return "Metro";
        case TransportType::Bus:
            return "Bus";
        case TransportType::Taxi:
            return "Taxi";
        default:
            return "Unknown";
    }
}

int main() {
    try {
        string filename = "input.txt";
        unordered_map<string, Vertex*> vertices = readGraphFromFile(filename);
        string sourceName = "Yadegar-e_Emam";
        string destinationName = "Haftom-e_Tir";
        PathResult result = findShortestPath(vertices, sourceName, destinationName);
        cout << "Shortest path: ";
        for (auto& step : result.path) {
            cout << step.first << " (" << transportTypeToString(step.second) << ", " << static_cast<int>(vertices.at(step.first)->colour) << "), ";
        }
        cout << "\nTotal Distance: " << result.distance << endl;
        for (auto& vertex : vertices) {
            delete vertex.second;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
