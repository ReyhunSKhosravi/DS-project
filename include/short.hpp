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
    Subway,
    Bus,
    Taxi,
};

enum class Colour {
    RED ,
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
    explicit Vertex(const string& name, Colour colour) : name(name) , colour(colour){} // because one order in costructor->> explicit 
    };

class SHORT
{
private:
    /* data */
    

public:
    SHORT(/* args */);
    ~SHORT();
    vector<Vertex*> readGraphFromFile(const string& filename){};
    void shortest_way (const vector<Vertex*>& vertices, const string& sourceName, const string& destinationName){};
    void shortest_time (const vector<Vertex*>& vertices, const string& sourceName, const string& destinationName){};
    void lowestcost (const vector<Vertex*>& vertices, const string& sourceName, const string& destinationName){};
    
};

SHORT::SHORT(/* args */)                                    
{
}

SHORT::~SHORT()
{
}
