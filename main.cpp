#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main()
{
    struct query
    {
        string originname;
        string destinationname;
        string date;
    };
    
    queue<query> requestQueue;

    int n ;
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        query q1;
        cin >> q1.originname >> q1.destinationname >> q1.date;
        requestQueue.push_back(q1);
    }

    
    for(size_t i =0; i < n ; i++)
    {
        requestQueue.pop_back();
    }
}