#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// bool findDuplicate(const string& filename, const string& mainline){
//     ifstream duplicate(filename);
//     string dupLine;
//     while (getline(duplicate, dupLine))
//     {
//        if(dupLine == mainline){
//         cout << "---> " << mainline << endl << "dupline:  " << dupLine << endl;
//         return false;
//        }
//     }
//     return true;
    
// }

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
    vector <string> linesoffile;
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
            string templine;
            bool havedup = false;
            if(j >= i){
                // cout << line2 << endl;
                istringstream iss2(line2);
                iss2 >> tempName >> tempDest >> tempWeight >> tempTran >> tempColor;
                // cout << tempName << tempDest << tempTran << tempColor << endl;
                string dupline = "";
              if(((preOrigin == tempName) && (preDest == tempDest)) ||  ( (preOrigin == tempDest) && (preDest == tempName))){
                    if(preTran == tempTran){
                        if(tempTran == "BUS"){
                            if(preColor != tempColor){
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4) + 15 )) + "\t" + tempTran + "\t" + tempColor );
                                linesoffile.push_back(templine);
                                for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                                if(!havedup){
                                inputTimeCost << preOrigin << "\t" << preDest << "\t" << to_string(((stoi(tempWeight) * 4) + 15 )) << "\t" << tempTran << "\t" << tempColor << "\n";
                                linesoffile.push_back(templine);
                            
                            }
                            }
                            else{
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4) + 0 )) + "\t" + tempTran + "\t" + tempColor);
                                cout << templine << endl;
                                for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                                if(!havedup){
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << to_string(((stoi(tempWeight) * 4) + 0 )) << "\t"<< tempTran << "\t" << tempColor << "\n";
                                linesoffile.push_back(templine);
                            
                            }
                            }
                        }
                        else if(tempTran == "SUBWAY"){
                            if(preColor != tempColor){
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 1) + 8 )) + "\t" + tempTran + "\t" + tempColor);
                                for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                                if(!havedup){
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << to_string(((stoi(tempWeight) * 1) + 8 )) << "\t"<< tempTran << "\t" << tempColor << "\n";
                                linesoffile.push_back(templine);
                            
                            }
                            }
                            else{
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 1) + 0 )) + "\t" + tempTran + "\t" + tempColor );
                                for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                                if(!havedup){
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << to_string(((stoi(tempWeight) * 1) + 0 )) << "\t"<< tempTran << "\t" << tempColor << "\n";
                                linesoffile.push_back(templine);
                            
                            }
                            }
                        }
                        else if(tempTran == "TAXI"){
                            if(preColor != tempColor){
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 2) + 5 )) + "\t" + tempTran + "\t" + tempColor);
                                for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                                if(!havedup){
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << to_string(((stoi(tempWeight) * 2) + 5 )) << "\t"<< tempTran << "\t" << tempColor << "\n";
                                linesoffile.push_back(templine);
                            
                            }
                            }
                            else{
                                templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 2) + 0 )) + "\t" + tempTran + "\t" + tempColor);
                                for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                                if(!havedup){
                                inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << to_string(((stoi(tempWeight) * 2) + 0 )) << "\t"<< tempTran << "\t" << tempColor << "\n";
                                linesoffile.push_back(templine);
                                }
                            }
                        }
                    }
                    else if(preTran != tempTran){
                        if(tempTran == "BUS"){
                            templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4) + 15 )) + "\t" + tempTran + "\t" + tempColor);
                            for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                            if(!havedup){
                            inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4) + 15 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
                            linesoffile.push_back(templine);
                            
                            }
                        }
                        else if(tempTran == "SUBWAY"){
                            templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 1) + 8 )) + "\t" + tempTran + "\t" + tempColor);
                            for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                                }
                            if(!havedup){
                            inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 1) + 8 ) <<"\t"<< tempTran << "\t" << tempColor << "\n";
                            linesoffile.push_back(templine);
                            
                            } 
                        }
                        else if(tempTran == "TAXI"){
                            templine =  (preOrigin + "\t" + preDest + "\t" + to_string(((stoi(tempWeight) * 4) + 5 )) + "\t" + tempTran + "\t" + tempColor);
                            for(auto it = linesoffile.rbegin(); it != linesoffile.rend(); ++it){
                                    if(*it == templine){
                                        havedup = true;
                                    }
                            }
                            if(!havedup){
                            inputTimeCost <<  preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4) + 5 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
                            linesoffile.push_back(templine);
                            
                            }
                        }
                    }
              }
            //   else if((preOrigin != tempName))
            //   {//yani faghat ye duneh masir hast in vasat!:
            //     if(tempTran == "BUS"){
            //             inputTimeCost << preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4) + 15 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
            //         }
            //         else if(tempTran == "SUBWAY"){
            //             inputTimeCost << preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 1) + 8 ) <<"\t"<< tempTran << "\t" << tempColor << "\n";
            //         }
            //         else if(tempTran == "TAXI"){
            //             inputTimeCost << preOrigin << "\t" << preDest << "\t" << ((stoi(tempWeight) * 4) + 5 ) << "\t"<< tempTran << "\t" << tempColor << "\n";
            //         }
            //   }
            
            }
            j++;
        }
        i++;
    }
    return 0;
}