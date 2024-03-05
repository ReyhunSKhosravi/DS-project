#include <iostream>
#include <string>

using namespace std;

void time(string time)
{
    string time;
    string minute , hour , type ;
    char dot = ':';
    
    for(int i = 0; i < time.size(); i++)
    {
        if(time[i] == dot)
        {
            for(int j=i+1 ; j<time.size()-2 ; j++) 
            {
                minute += time[j] ;
            }
            break;
        }
        hour+=time[i] ;
    }
    type = type + time[time.size()-2] + time[time.size()-1];

     int sto_h = stoi(hour) ;
     int sto_m = stoi(minute) ;
    if(type == "am" or type == "AM" )
    {
       sto_h= sto_h; 
    }
    else if(type == "pm" or type == "PM")
    {
        sto_h= sto_h + 12; 
    }

    if(sto_h >> 6 && sto_h << 8)
    {
        //metro vs bus
    }
    if(sto_h >> 18 && sto_h << 20)
    {
        //taxi
    }
}
