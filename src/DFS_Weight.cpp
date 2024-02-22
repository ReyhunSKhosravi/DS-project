#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <limits>

using namespace std;

enum class TransportType
{
    Metro,
    Bus,
    Taxi,
};

enum class Colour
{
    RED,
    BLUE,
    YELLOW,
    PINK,
    GRAY,
    GREEN,
    BROWN,
};

struct Vertex
{
    string name;
    unordered_map<Vertex *, pair<int, TransportType>> neighbors;

    explicit Vertex(const string &name) : name(name) {}
};

vector<Vertex *> readGraphFromFile(const string &filename)
{
    vector<Vertex *> vertices;
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Error: Unable to open the file.");
    }
    unordered_map<string, Vertex *> vertexMap;
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string originName, destName;
        int weight;
        string transportTypeStr, colourstr;
        if (iss >> originName >> destName >> weight >> transportTypeStr >> colourstr)
        {
            if (vertexMap.find(originName) == vertexMap.end())
            {
                Vertex *originVertex = new Vertex(originName);
                vertices.push_back(originVertex);
                vertexMap[originName] = originVertex;
            }
            if (vertexMap.find(destName) == vertexMap.end())
            {
                Vertex *destVertex = new Vertex(destName);
                vertices.push_back(destVertex);
                vertexMap[destName] = destVertex;
            }
            TransportType transportType;
            switch (stoi(transportTypeStr))
            {
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
            vertexMap[originName]->neighbors[vertexMap[destName]] = make_pair(weight, transportType);
        }
    }
    file.close();
    return vertices;
}

void dfs(Vertex *current, Vertex *destination, vector<vector<pair<string, TransportType>>> &allPaths, vector<pair<string, TransportType>> &currentPath, unordered_map<Vertex *, bool> &visited)
{
    visited[current] = true;
    if (current == destination)
    {
        allPaths.push_back(currentPath);
    }
    else
    {
        for (auto &neighbor : current->neighbors)
        {
            Vertex *next = neighbor.first;
            if (!visited[next])
            {
                currentPath.push_back({current->name, neighbor.second.second}); // نوع وسیله نقلیه را از مقدار مورد نظر در فایل ورودی بگیرید
                dfs(next, destination, allPaths, currentPath, visited);
                currentPath.pop_back();
            }
        }
    }
    visited[current] = false;
}

void printShortestPath(const vector<vector<pair<string, TransportType>>> &allPaths, const unordered_map<string, int> &distances)
{
    if (allPaths.empty())
    {
        cout << "No path exists." << endl;
        return;
    }
    int shortestDistance = numeric_limits<int>::max();
    int shortestPathIndex = -1;
    for (size_t i = 0; i < allPaths.size(); ++i)
    {
        int pathDistance = 0;
        for (size_t j = 0; j < allPaths[i].size() - 1; ++j)
        {
            string edgeName = allPaths[i][j].first + "-" + allPaths[i][j + 1].first;
            pathDistance += distances.at(edgeName);
        }
        if (pathDistance < shortestDistance)
        {
            shortestDistance = pathDistance;
            shortestPathIndex = i;
        }
    }
    cout << "Shortest path: ";
    for (size_t i = 0; i < allPaths[shortestPathIndex].size(); ++i)
    {
        cout << allPaths[shortestPathIndex][i].first << " (";
        switch (allPaths[shortestPathIndex][i].second)
        {
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
        if (i + 1 < allPaths[shortestPathIndex].size())
        {
            cout << " -> ";
        }
    }
    cout << ", Distance: " << shortestDistance << endl;
}

void findPaths(const vector<Vertex *> &vertices, const string &sourceName, const string &destinationName)
{
    Vertex *source = nullptr;
    Vertex *destination = nullptr;
    unordered_map<Vertex *, bool> visited;
    for (Vertex *vertex : vertices)
    {
        visited[vertex] = false;
        if (vertex->name == sourceName)
        {
            source = vertex;
        }
        else if (vertex->name == destinationName)
        {
            destination = vertex;
        }
    }
    if (!source || !destination)
    {
        cerr << "Error: Source or destination vertex not found." << endl;
        return;
    }
    vector<vector<pair<string, TransportType>>> allPaths;
    vector<pair<string, TransportType>> currentPath;
    dfs(source, destination, allPaths, currentPath, visited);

    unordered_map<string, int> distances;
    for (Vertex *vertex : vertices)
    {
        for (auto &neighbor : vertex->neighbors)
        {
            string edgeName = vertex->name + "-" + neighbor.first->name;
            distances[edgeName] = neighbor.second.first;
        }
    }

    printShortestPath(allPaths, distances);
}

int main()
{
    try
    {
        string filename = "input.txt";
        vector<Vertex *> vertices = readGraphFromFile(filename);
        string originName = "Boostan-e_laleh";
        string destinationName = "Meydan-e_Azad";
        findPaths(vertices, originName, destinationName);
        for (Vertex *vertex : vertices)
        {
            delete vertex;
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}
