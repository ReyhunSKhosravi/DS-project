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
    string originName, destName, transportTypeStr, colorOfLine;
    string weightAslis, weights;
    int weightAsli, weight;

    while(getline(file, line)){
        istringstream iss(line);
// cout << "i:" << i << "\t" << line << endl;
        iss >> originNameAsli >> destNameAsli >> weightAslis >> transportTypeStrAsli >> colorOfLineAsli;
        ifstream file2("input.txt");
        if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
        }
        j = 0;
        while(getline(file2, line2))
        {
            if(j >= i)
            {
                cout << line2 << endl;
                istringstream iss2(line2);
                iss2 >> originName >> destName >> weights >> transportTypeStr >> colorOfLine;
                cout << originName << destName << transportTypeStr << colorOfLine << endl;
                weight = stoi(weights);
                weight = stoi(weightAslis);
                                if((transportTypeStr == transportTypeStrAsli))
                {
                    
                    cout << line2 << endl;
                    if(transportTypeStr == "BUS")
                        {
                            busInFile << originNameAsli << "\t" <<originName << "\t" << (weight*4)+15 << "\t" << transportTypeStr << "\t" << colorOfLine << "\n";
                                busInFile << originName  << "\t" << originNameAsli << "\t" << (weightAsli*4)+15 << "\t" << transportTypeStr << "\t" << colorOfLine << "\n";
                                
                            }
                            else if(transportTypeStr == "SUBWAY")
                            {
                                busInFile << originNameAsli << "\t" <<originName << "\t" << (weight * 1)+8 << "\t" << transportTypeStr << "\t" << colorOfLine << "\n";
                                busInFile <<originName  << "\t" <<originNameAsli << "\t" << (weightAsli * 1)+8 << "\t" << transportTypeStr << "\t" << colorOfLine << "\n";
                            }
                             else if(transportTypeStr == "TAXI")
                            {
                                busInFile << originNameAsli << "\t" <<originName << "\t" << (weight * 2)+5 << "\t" << transportTypeStr << "\t" << colorOfLine << "\n";
                                busInFile <<originName  << "\t" <<originNameAsli << "\t" << (weightAsli * 2)+5 << "\t" << transportTypeStr << "\t" << colorOfLine << "\n";
                            }
                        
                }

                }
            
            
            }
            j++;
        }
        // cout << "----> oomadam khat 37" << endl;
        i++;
    
    return 0;
}
                    