// InitiativeTracker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include<unordered_map>
#include <map>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iterator>
using namespace std;


//A program meant to help me more quickly calculate and track initiatve order for combat in D&D 5e :)  If you enjoy using this please let me know! 
// TODO Add contact info above!


bool comp(pair<string, int>& a, pair<string, int>& b)
{
    return a.second > b.second;
}

string printInitiative(vector<pair<string, int>>& initiative)
{
    cout
        << "|====================================================|\n"
        << "|//////////////////Initiative Order//////////////////|\n"
        << "|====================================================|\n"
        << "\n"
        << "\n";

    int j = 1;

    for (auto i : initiative)
    {
        cout << "        ||   " << j << ".    " << i.first << " : " << i.second << endl;
        cout << "        ||   " << "----------------------------------" << endl;
        j++;
    }
}

int main()
{
    map<string, int> initOrder;
    vector<pair<string, int>> currentInitiative;
    vector<string> partyNames;
    string partyMember;
    string enemyName;
    bool enteringParty = true;
    bool enteringEnemies = false;
    bool inCombat = false;
    bool rollingPlayerInitiative = false;
    bool programRunning = true;
    bool calculateInitiative = false;
    bool progressTurn = false;
    int choice;
    int inCombatChoice;
    int playerInitiative;
    int initModifier;
    int turnCounter = 0;
    int deleteChoice;

    vector<pair<string, int>>::iterator initiativeIterator;


    //the color variable seems to change background with the first character (5), then font color with the second (e)
    system("Color 5e");

    cout 
        << "                    ____ \n"
        << "                  .'* *.'\n"
        << "               __/_*_*(_\n"
        << "              / _______ \\\n"
        << "             _\\_)/___\\(_/_ \n"
        << "            / _((\\- -/))_ \\\n"
        << "            \\ \\())(-)(()/ /\n"
        << "             ' \\(((()))/ '\n"
        << "            / ' \\)).))/ ' \\\n"
        << "           / _ \\ - | - /_  \\\n"
        << "          (   ( .;''';. .'  )\n"
        << "          _\\\"__ /    )\\ __\" / _\n"
        << "            \\/  \\   ' /  \\/\n"
        << "             .'  '...' ' )\n"
        << "              / /  |  \\ \\\n"
        << "             / .   .   . \\\n"
        << "            /   .     .   \\\n"
        << "           /   /   |   \\   \\\n"
        << "         .'   /    b    '.  '.\n"
        << "     _.-'    /     Bb     '-. '-._ \n"
        << " _.-'       |      BBb       '-.  '-. \n"
        << "(________mrf\____.dBBBb.________)____)\n"
        << "\n"
        << "\n"
        << "        __         _    _                     _     _    _      _      \n"
        << "       / /    ___ | |_ ( ) ___    __ _   ___ | |_  | |_ | |__  (_) ___ \n"
        << "      / /    / _ \\| __||/ / __|  / _` | / _ \| __| | __|| '_ \\ | |/ __|\n"
        << "     / /___ |  __/| |_    \\__ \\ | (_| ||  __/| |_  | |_ | | | || |\\__ \\\n"
        << "     \\____/  \\___| \\__|   |___/  \\__, | \\___| \\__|  \\__||_| |_||_||___/\n"
        << "                                 |___/                                 \n"
        << "\n"
        << "\n"
        << "   ___               _                 _                 _              _    _ \n"
        << "  / _ \\  __ _  _ __ | |_  _   _   ___ | |_   __ _  _ __ | |_   ___   __| |  / \\\n"
        << " / /_)/ / _` || '__|| __|| | | | / __|| __| / _` || '__|| __| / _ \\ / _` | /  /\n"
        << "/ ___/ | (_| || |   | |_ | |_| | \\__ \\| |_ | (_| || |   | |_ |  __/| (_| |/\\_/ \n"
        << "\\/      \\__,_||_|    \\__| \\__, | |___/ \\__| \\__,_||_|    \\__| \\___| \\__,_|\\/   \n"
        << "                          |___/                                                \n"
        << "\n"
        << "\n"
        << "\n"
        << "====================================================\n"
        << "////////////////////////////////////////////////////\n"
        << "====================================================\n"
        << "                Create your party!\n"
        << "====================================================\n"
        << "////////////////////////////////////////////////////\n"
        << "====================================================\n"
        << "\n"
        << "\n"
        << "\n"
        << "Please enter name of first party member: \n\n";

        do
        {
            cin >> partyMember;
            if (partyMember == "continue")
            {
                enteringParty = false;
                break;
            }
                
            cout << "\nAdding " << partyMember << " to the party!\n\n" << endl;
            partyNames.push_back(partyMember);
            cout << "Name of next party member (or enter 'continue' to move on):\n\n";
        } while (enteringParty == true);

        cout
            << "                                       Party Set!\n"
            << "\n                   <>---{============>       <============}---<>\n"
            << "\n"
            << "\n"
            << "\n";
        
        //Print out party
        for (auto member : partyNames) {
            cout << "                                        " << member << "\n" << endl;
        }
        cout << "\n                   <>---{============>       <============}---<>\n"
            << "\n"
            << "\n"
            << "\n"
            << "\n"
            << "\n"
            << "\n";


        //Start of main program, following initial party creation
        do
        {
            cout
                << "\n"
                << "           /\\                                                 /\\\n"
                << " _         )( ______________________   ______________________ )(         _\n"
                << "(_)///////(**)______________________> <______________________(**)\\\\\\\\\\\\\\(_)\n"
                << "           )(                                                 )(\n"
                << "           \\/                                                 \\/\n"
                << "\n"
                << "                 ___         _    _                    \n"
                << "                /___\\ _ __  | |_ (_)  ___   _ __   ___ \n"
                << "               //  //| '_ \\ | __|| | / _ \\ | '_ \\ / __|\n"
                << "              / \\_// | |_) || |_ | || (_) || | | |\__ \\\n"
                << "              \\___/  | .__/  \\__||_| \\___/ |_| |_||___/\n"
                << "                     |_|                               \n"
                << "\n"
                << "           /\\                                                 /\\\n"
                << " _         )( ______________________   ______________________ )(         _\n"
                << "(_)///////(**)______________________> <______________________(**)\\\\\\\\\\\\\\(_)\n"
                << "           )(                                                 )(\n"
                << "           \\/                                                 \\/\n"
                << "\n"
                
                /*<< "  .--.      .-'.      .--.      .--.      .--.      .--.      .`-.      .--.\n"
                << ":::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\\n"
                << "'      `--'      `.-'      `--'      `--'      `--'      `-.'      `--'      `\n"*/

                
                << "                 __________________________________________\n"
                << "               / \\                                         \\.\n"
                << "              |   |                                        |.\n"
                << "               \\_ |                                        |.\n"
                << "                  |                                        |.\n"
                << "                  |                                        |.\n"
                << "                  |     Please select an option:           |.\n"
                << "                  |       1. Begin Combat                  |.\n"
                << "                  |       2. Add Party Member              |.\n"
                << "                  |       3. Return to party creation      |.\n"
                << "                  |       4. Print current party           |.\n"
                << "                  |       5. ASCII Art                     |.\n"
                << "                  |       6. Exit Program                  |.\n"
                << "                  |                                        |.\n"
                << "                  |                                        |.\n"
                << "                  |   _____________________________________|___\n"
                << "                  |  /                                        /.\n"
                << "                  \\_/________________________________________/.\n"
                << "\n"
                << "\n"
                << "\n";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout 
                    << "\n\n\n"
                    << "|====================================================|\n"
                    << "|////////////////////////////////////////////////////|\n"
                    << "|====================================================|\n"
                    << "        Beginning Combat. Roll Initiative!\n"
                    << "|====================================================|\n"
                    << "|////////////////////////////////////////////////////|\n"
                    << "|====================================================|\n"
                    << "\n"
                    << "\n"
                    << "                        _-_.\n"
                    << "                     _-',^. `-_\n"
                    << "                 ._-' ,'   `.   `-\n"
                    << "                !`-_._________`-'::\n"
                    << "                !   /\        /\\::::\n"
                    << "                ;  /  \      /..\\:::\n"
                    << "                ! /    \    /....\\::\n"
                    << "                !/      \  /......\\:\n"
                    << "                ;--.___. \/_.__.--;;\n"
                    << "                 '-_    `:!;;;;;;;'\n"
                    << "                    `-_, :!;;;''\n"
                    << "                        `-!' \n"
                    << "\n"
                    << "\n"
                    << "\n"
                    << "  .--.      .-'.      .--.      .--.      .--.      .--.    \n"
                    << ":::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\::::::::.\\\n"
                    << "'      `--'      `.-'      `--'      `--'      `--'      `-.`\n"
                    << "\n";
                   
                

                inCombat = true;
                enteringEnemies = true;
                calculateInitiative = true;
                initOrder.clear();
                break;
            case 2:
                cout << "Please enter name of party member to add\n";
                cin >> partyMember;
                cout << "Adding " << partyMember << " to the party!";
                partyNames.push_back(partyMember);
                break;
            case 3:
                partyNames.clear();
                cout << "Returing to party creation...";
                enteringParty = true;
                break;
            case 4:
                for (auto member : partyNames)
                {
                    cout << member << endl;
                }
                break;
            case 5:
                cout << "Will build this function very soon!";
                break;
            case 6:
                programRunning = false;
                break;
            }


            //Used if user decides to reset party
            if (enteringParty == true)
            {
                cout << "Please enter name of first party member: \n";
                do
                {
                    cin >> partyMember;
                    if (partyMember == "continue")
                    {
                        enteringParty = false;
                        break;
                    }

                    cout << "Adding " << partyMember << " to the party!\n" << endl;
                    partyNames.push_back(partyMember);
                    cout << "Name of next party member (or enter 'continue' to move on):\n";
                } while (enteringParty == true);
           }


            //Enter this loop when user selects to enter combat
            while (inCombat == true)
            {
                
                //Loop to add enemies to the combat
                while(enteringEnemies == true)
                {
                    cout << "Please enter name of enemy to add: \n\n";
                    cin >> enemyName;

                    //Break here if user enters continue
                    if (enemyName == "continue")
                    {
                        cout << "Finished entering enemies!\n\n";
                        enteringEnemies = false;
                    }
                    else
                    {
                        //if enemy name is not already used, generate and record it's initiative
                        if (initOrder[enemyName] == NULL)
                        {
                            cout << "\nEnemy initiaitive modifier: \n\n";
                            cin >> initModifier;
                            if (cin.eof()) break;
                            if (!cin)
                            {
                                cerr << "Bad input" << endl;
                                cin.clear();
                                cin.ignore();
                                break;
                            }

                            initOrder[enemyName] = rand() % 20 + (1 + initModifier);
                            cout << enemyName << " added with initiative of: " << initOrder[enemyName] << "\n" << endl;
                        }
                        else
                        {
                            cout << "Enemy name is already in use this combat\n";
                        }
                    }

                    

                }
                //Finish loop to add enemies


                //Add all players rolls to initiative map first
            if (calculateInitiative == true)
                {
                for (auto player : partyNames)
                {
                    cout << "Please record initiative for " << player << endl;
                    cin >> playerInitiative;
                    initOrder[player] = playerInitiative;
                }

                for (auto creature : initOrder)
                {
                    currentInitiative.push_back(make_pair(creature.first, creature.second));
                }

                
                    sort(currentInitiative.begin(), currentInitiative.end(), comp);
                    printInitiative(currentInitiative);

                    calculateInitiative = false;
            }


                cout << "\nPlease select an option: \n"
                    << "1. Next turn\n"
                    << "2. Remove creature from initiative\n"
                    << "3. Add creature to initiative\n"
                    << "4. End Combat\n";

                cin >> inCombatChoice;

                if (progressTurn == true)
                {
                    if (turnCounter < currentInitiative.size() - 1)
                    {
                        turnCounter++;
                    }
                    else {
                        turnCounter = 0;
                    }
                    progressTurn = false;
                }

                switch (inCombatChoice)
                {
                case 1:
                    cout
                        << "|====================================================|\n"
                        << "|<////////////////}~~Current Turn~~{////////////////>|\n"
                        << "|====================================================|\n"
                        << "\n"
                        << "                  " << currentInitiative[turnCounter].first << "\n";
                    progressTurn = true;
                    break;
                case 2:
                    
                    cout << "Please select which creature to remove from combat: \n";
                    printInitiative(currentInitiative);
                    cout << "\n";
                    cin >> deleteChoice;
                    if (cin.eof()) break;
                    if (!cin)
                    {
                        cerr << "Bad input" << endl;
                        cin.clear();
                        cin.ignore();
                        break;
                    }

                    if (deleteChoice >= currentInitiative.size() + 1)
                    {
                        cout << "Out of bounds input (larger than size of initiative list)";
                        break;
                    }

                    cout << "Removed creature # " << deleteChoice << " from initiative, new initiative:\n";
                    currentInitiative.erase(next(currentInitiative.begin(), deleteChoice - 1));
                    sort(currentInitiative.begin(), currentInitiative.end(), comp);
                    printInitiative(currentInitiative);
                    
                    /*system("pause");*/
                    do
                    {
                        cout << "\n\nPress any key to continue///\n\n";
                    } while (cin.get() != '\n');
                    

                    break;
                case 3:
                    
                    
                    enteringEnemies = true;
                    do
                    {
                        cout << "Please enter name of enemy to add: \n\n";
                        cin >> enemyName;

                        //Break here if user enters continue
                        if (enemyName == "continue")
                        {
                            cout << "Finished entering enemies!\n\n";
                            enteringEnemies = false;
                        }
                        else
                        {
                            //if enemy name is not already used, generate and record it's initiative
                            if (initOrder[enemyName] == NULL)
                            {
                                cout << "\nEnemy initiaitive modifier: \n\n";
                                cin >> initModifier;
                                if (cin.eof()) break;
                                if (!cin)
                                {
                                    cerr << "Bad input" << endl;
                                    cin.clear();
                                    cin.ignore();
                                    break;
                                }

                                initOrder[enemyName] = rand() % 20 + (1 + initModifier);
                                for (auto creature : initOrder)
                                {
                                    currentInitiative.push_back(make_pair(creature.first, creature.second));
                                }
                                sort(currentInitiative.begin(), currentInitiative.end(), comp);
                                cout << enemyName << " added with initiative of: " << initOrder[enemyName] << "\n" << endl;
                            }
                            else
                            {
                                cout << "Enemy name is already in use this combat\n";
                                cin.clear();
                                cin.ignore();
                            }

                        }
                    } while (enteringEnemies != false);
                    
                    break;
                case 4:
                    cout << "Ending combat!\n\n";
                    inCombat = false;
                    break;
                }

               

            }
            //End of combat loop

        } while (programRunning == true);

        return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
