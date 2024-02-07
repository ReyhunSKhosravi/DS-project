#include <iostream>
using namespace std;

void Welcom() // mitonim bezarim toye constructor
{
    cout << "   |=|===================|=|      \n";
    cout << "   |=|===================|=|      \n";
    cout << "   |=|     _________     |=|      \n";
    cout << "   |=|    |Samhanesht|   |=|      \n";
    cout << "   |=|                   |=|      \n";
    cout << "   |=|===================|=|      \n";
    cout << "   |=|===================|=|      \n";
    cout << endl;
    cout << "[:)] "
         << "Enter <help> command to guide you\n"
         << endl;
}
//-------------------------------------------------------
void help()
{
    cout << "[:)] "
         << "app commands : (case insensitive)" << endl;

    cout << "for start Rauding enter :  S " << endl;
    cout << "for exit the program :  E " << endl;
}
//------------------------------lowers the progrom letters
void lowercase(string &str)
{
    if (cin.eof() || str.empty())
    {
        return;
    }

    for (char &ch : str)
    {
        ch = tolower(ch);
    }
}
// -------------------------------------------------------
int menu_request()
{

    string command;
    int rude;
    string Time, Origin, Destination; // ina bayad be private bere
    while (1)
    {
        try
        {
            cout << "> ";
            getline(cin, command);
            lowercase(command);

            if (cin.eof() || command == "s")
            {
                try
                {
                    cout << "1-Number of order\t";
                    cin >> rude;
                    if (rude < 1)
                    {
                        throw "the number of order must be greater than 1";
                    }
                    else
                    {
                        // tabe mizrim
                    }
                    cout << "\n2-Start time\t";
                    cin>>Time;
                    cout << "\n3-Origin\t";
                    cin>>Origin;
                    cout << "\n4-Destination\t";
                    cin>>Destination;
                    
                    if (cin.eof() || command == "e")
                    {
                        return 0;
                    }
                }
                catch (const std::exception &e)
                {
                    cerr << e.what() << endl;
                    cout << "press S to countinue";
                }
                catch (...)
                {
                    system("cls");
                    cerr << "app finished" << endl;
                    return EXIT_SUCCESS;
                }
            }
            else if (command == "help")
            {
                help();
            }
            else if (cin.eof() || command == "e")
            {
                return 0;
            }

            else if (command.empty())
            {
                // to prevent print undefined command in empty command
            }
            else
            {
                throw "undefined command";
            }
        }
        catch (const char *message)
        {
            cerr << "[:)] " << message << endl;
        }
        catch (const std::exception &e)
        {
            cerr << "[:)] " << e.what() << endl;
        }
        catch (...)
        {
            system("cls");
            cerr<<"try again"<<endl;
            cerr << "app finished" << endl;
            return EXIT_SUCCESS;
        }
    }
}

