#include <iostream>
using namespace std;
class Taxi
{
private:
    /* data */
    
public:
    static const int MoneyCost = 6000; //cost in money per line
    static const int TimeCost = 2; //cost in time per kilometer
    static int HourTime;
    Taxi(/* args */);
    ~Taxi();
};