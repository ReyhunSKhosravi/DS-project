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
    RED,
    BLUE,
    YELLOW,
    PINK,
    GRAY,
    GREEN,
    BROWN,
    YELLOW_Dark,
    GREEN_Dark,
};

struct Vertex {
    string name;
    unordered_map<Vertex*, pair<int, TransportType>> neighbors;
    Colour colour;

    explicit Vertex(const string& name, Colour colour) : name(name), colour(colour) {}
};

struct PathResult {
    vector<pair<string, TransportType>> path;
    vector<int> weights;
    int distance;
};

Colour stringToColour(const string& colourStr) {
    int colourCode = stoi(colourStr);
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

string colourToString(Colour colour) {
    switch(colour) {
        case Colour::RED:
            return "Red";
        case Colour::BLUE:
            return "Blue";
        case Colour::YELLOW:
            return "Yellow";
        case Colour::PINK:
            return "Pink";
        case Colour::GRAY:
            return "Gray";
        case Colour::GREEN:
            return "Green";
        case Colour::BROWN:
            return "Brown";
        case Colour::YELLOW_Dark:
            return "Yellow_Dark";
        case Colour::GREEN_Dark:
            return "Green_Dark";
        default:
            return "Unknown";
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
        string originName, destName, colourstr;
        int weight;
        string transportTypeStr;
        if (iss >> originName >> destName >> weight >> transportTypeStr >> colourstr) {
            Colour colour = stringToColour(colourstr);
            if (vertices.find(originName) == vertices.end()) {
                vertices[originName] = new Vertex(originName, colour);
            }
            if (vertices.find(destName) == vertices.end()) {
                vertices[destName] = new Vertex(destName, colour);
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

PathResult findShortestPath(unordered_map<string, Vertex*>& vertices, const string& sourceName, const string& destinationName) {
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
    vector<int> weights;
    string current = destinationName;
    int totalDistance = distances[destinationName];
    while (current != sourceName) {
        Vertex* vertex = vertices.at(current);
        string prevName = previous.at(current);
        for (auto& neighbor : vertex->neighbors) {
            Vertex* prev = neighbor.first;
            if (prev->name == prevName) {
                shortestPath.push_back({current, neighbor.second.second});
                weights.push_back(neighbor.second.first);
                current = prevName;
                break;
            }
        }
    }
    reverse(shortestPath.begin(), shortestPath.end());
    reverse(weights.begin(), weights.end());
    return {shortestPath, weights, totalDistance};
}

void changeWeightsIfColourChanged(unordered_map<string, Vertex*>& vertices) {
    for (auto& vertex : vertices) {
        for (auto& neighbor : vertex.second->neighbors) {
            if (neighbor.first->colour != vertex.second->colour) {
                int originalWeight = neighbor.second.first;
                neighbor.second.first *= 2; // تغییر وزن یال
                cout << "Weight of edge between " << vertex.second->name << " and " << neighbor.first->name << " changed from " << originalWeight << " to " << neighbor.second.first << endl;
            }
        }
    }
}

void printShortestPath(const PathResult& result, const unordered_map<string, Vertex*>& vertices) {
    cout << "Shortest path:" << endl;
    for (size_t i = 0; i < result.path.size(); ++i) {
        string station1 = result.path[i].first;
        string station2 = i < result.path.size() - 1 ? result.path[i + 1].first : "";
        Vertex* vertex1 = vertices.at(station1);
        Vertex* vertex2 = vertices.at(station2);
        cout << station1 << " -> " << station2 << " (" << transportTypeToString(result.path[i].second) << ", " << colourToString(vertex1->colour) << " to " << colourToString(vertex2->colour) << ") - Weight: " << result.weights[i] << endl;
    }
    cout << "Total Distance: " << result.distance << endl;
}

int main() {
    try {
        string filename = "input.txt";
        unordered_map<string, Vertex*> vertices = readGraphFromFile(filename);
        string sourceName = "Meydan-e_Azadi";
        string destinationName = "Haftom-e_Tir";


        changeWeightsIfColourChanged(vertices);

        PathResult result = findShortestPath(vertices, sourceName, destinationName);
        printShortestPath(result, vertices);

      
        for (auto& vertex : vertices) {
            delete vertex.second;
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
