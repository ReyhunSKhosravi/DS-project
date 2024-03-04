#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


int main(){
    ifstream file("input.txt");
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
    }
    ofstream busInFile("busInput.txt");
    if (!busInFile.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
    }
    string line, line2;
    int i = 1, j = 1;
    string originNameAsli, destNameAsli, transportTypeStrAsli, colorOfLineAsli;
    string originNameBus, destNameBus, transportTypeStrBus, colorOfLineBus;
    string weightAsli, weightBus;

    while(getline(file, line)){
        istringstream iss(line);
        // cout << "i:" << i << "\t" << line << endl;
        iss >> originNameAsli >> destNameAsli >> weightAsli >> transportTypeStrAsli >> colorOfLineAsli;
        ifstream file2("input.txt");
        if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
        }
        j = 0;
        while(getline(file2, line2)){
            if(j >= i){
                cout << line2 << endl;
                istringstream iss2(line2);
                iss2 >> originNameBus >> destNameBus >> weightBus >> transportTypeStrBus >> colorOfLineBus;
                cout << originNameBus << destNameBus << transportTypeStrBus << colorOfLineBus << endl;
                if((transportTypeStrBus == "BUS" && transportTypeStrAsli == "BUS") || (transportTypeStrBus == "SUBWAY" && transportTypeStrAsli == "SUBWAY")){
                    cout << line2 << endl;
                    if((originNameAsli != originNameBus) && (colorOfLineAsli == colorOfLineBus))
                        {
                            if(transportTypeStrBus == "BUS"){
                                busInFile << originNameAsli << "\t" <<originNameBus << "\t" << "2250" << "\t" << transportTypeStrBus << "\t" << colorOfLineBus << "\n";
                                busInFile << originNameBus  << "\t" << originNameAsli << "\t" << "2250" << "\t" << transportTypeStrBus << "\t" << colorOfLineBus << "\n";
                                
                            }
                            else if(transportTypeStrBus == "SUBWAY"){
                                busInFile << originNameAsli << "\t" <<originNameBus << "\t" << "3267" << "\t" << transportTypeStrBus << "\t" << colorOfLineBus << "\n";
                                busInFile <<originNameBus  << "\t" <<originNameAsli << "\t" << "3267" << "\t" << transportTypeStrBus << "\t" << colorOfLineBus << "\n";
                            }
                            
                        }
                }
            
            
            }
            j++;
        }
        // cout << "----> oomadam khat 37" << endl;
        i++;
    }
    return 0;
}