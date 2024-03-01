#include "../include/app.hpp"
#include <iostream>
#include <string>
#include "time.hpp"
#include "ClassReq.hpp"
using namespace std;


void APP::start()
{
    RequestManager request_M;

    cin >> n;

    cin.ignore();
    while (n--)
    {
        getline(cin, hour);
        getline(cin, src);
        getline(cin, dst);

        request_M.addRequest(src, dst, hour);
    }

    while (!request_M.requestQueue.empty())
    {
        Request currentRequest = request_M.requestQueue.front();
        request_M.requestQueue.pop();

        Time time(currentRequest.input_time);
        
    }
}


