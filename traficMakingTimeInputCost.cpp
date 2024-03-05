#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

bool findDuplicate(const string& filename, const string& mainline){
    ifstream duplicate(filename);
    string dupLine;
    while (getline(duplicate, dupLine))
    {
       if(dupLine == mainline){
        return true;
       }
    }
    return false;
    
}

int main(){
    ifstream file("input.txt");
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
    }
    ofstream inputTimeCost("inputtime.txt");
    if (!inputTimeCost.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
    }
    string line, line2;
    int i = 1, j = 1;
    string preOrigin, preDest, preTran, preColor;
    string tempName, tempDest, tempTran, tempColor;
    string preWeight, tempWeight;

    while(getline(file, line)){
        istringstream iss(line);
        // cout << "i:" << i << "\t" << line << endl;
        iss >> preOrigin >> preDest >> preWeight >> preTran >> preColor;
        ifstream file2("input.txt");
        if (!file.is_open()) {
        throw runtime_error("Error: Unable to open the file.");
        }
        j = 0;
        while(getline(file2, line2)){
            
            if(j >= i){
                cout << line2 << endl;
                istringstream iss2(line2);
                iss2 >> tempName >> tempDest >> tempWeight >> tempTran >> tempColor;
                cout << tempName << tempDest << tempTran << tempColor << endl;
                string templine = "";
              if(((preOrigin == tempName) && (preDest == tempDest)) ||  ( (preOrigin == tempDest) && (preDest == tempName))){
                    if(preTran == tempTran){
                        if(tempTran == "BUS"){
                            if(preColor != tempColor){
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4 * 2) + 15 )) + "\t" + tempTran + "\t" + tempColor );
                                if(!findDuplicate("inputtime", templine)){
                                inputTimeCost <<   preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4 * 2) + 15 ) << "\t" << tempTran << "\t" << tempColor << "\n";
                                }
                            }
                            else{
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4 * 2) + 0 )) + "\t" + tempTran + "\t" + tempColor);
                                if(!findDuplicate("inputtime", templine))
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4 * 2) + 0 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
                            }
                        }
                        else if(tempTran == "SUBWAY"){
                            if(preColor != tempColor){
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 1 * 3) + 8 )) + "\t" + tempTran + "\t" + tempColor);
                                if(!findDuplicate("inputtime", templine))
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 1 * 3) + 8 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
                            }
                            else{
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 1 * 3) + 0 )) + "\t" + tempTran + "\t" + tempColor );
                                if(!findDuplicate("inputtime", templine))
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 1 * 3) + 0 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
                            }
                        }
                        else if(tempTran == "TAXI"){
                            if(preColor != tempColor){
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 2 * 2) + 5 )) + "\t" + tempTran + "\t" + tempColor);
                                if(!findDuplicate("inputtime", templine))
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 2 * 2) + 5) << "\t"<< tempTran << "\t" << tempColor << "\n";
                            }
                            else{
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 2 * 2) + 0 )) + "\t" + tempTran + "\t" + tempColor);
                                if(!findDuplicate("inputtime", templine))
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 2 * 2) + 0 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
                            }
                        }
                    }
                    else if(preTran != tempTran){
                        if(tempTran == "BUS"){
                            templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4 * 2) + 15 )) + "\t" + tempTran + "\t" + tempColor);
                                if(!findDuplicate("inputtime", templine))
                            inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4 * 2) + 15 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
                        }
                        else if(tempTran == "SUBWAY"){
                            templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 1 * 3) + 8 )) + "\t" + tempTran + "\t" + tempColor);
                                if(!findDuplicate("inputtime", templine))
                            inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 1 * 3) + 8 ) <<"\t"<< tempTran << "\t" << tempColor << "\n";
                        }
                        else if(tempTran == "TAXI"){
                            templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4 * 2) + 5 )) + "\t" + tempTran + "\t" + tempColor);
                                if(!findDuplicate("inputtime", templine))
                            inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4 * 2) + 5 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
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