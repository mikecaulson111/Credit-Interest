#include <iostream>
#include <iomanip>
#include <string>
#include "assets.hpp"
#include "utils.hpp"

using namespace std;

void AssetsList::add_item(string name, bool is_equity, double amount)
{
    cout << name << is_equity << amount << endl;
}

void assets_initiate(AssetsList* p_list)
{
    bool running = true;
    string input;
    int choice = -1;

    // for asset
    string name;
    bool is_equity = false;
    double amount = 0.0;


    while (running)
    {
        cout << "What would you like to do:" << endl;
        cout << "[1] Add Item to assets list" << endl;
        cout << "[2] Edit Item on list" << endl;
        cout << "[3] Remove Item from list" << endl;
        cout << "[4] Print List of items" << endl;
        cout << "[5] Quit" << endl;

        getline(cin, input, '\n');
        if ( is_numb(input, false) )
        {
            choice = stoi(input);
        }

        if (1 == choice)
        {
            // something
            cout << "Please enter the name of the item here:" << endl;
            getline(cin, input, '\n');
            name = input;

            cout << "Please enter if it is equity or a liability:\n[1] Equity\n[2] Liability" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, false))
            {
                if (1 == stoi(input))
                {
                    is_equity = true;
                }
                else
                {
                    is_equity = false;
                }
            }

            cout << "Please enter the amount" << (is_equity ? " that it is worth:" : " that you owe:\n$");
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                amount = stod(input);
            }

            if (p_list == NULL)
            {
                p_list = new AssetsList();
            }

            p_list->add_item(name, is_equity, amount);
            
        }
        else if (2 == choice)
        {
            // something
        }
        else if (3 == choice)
        {
            // something
        }
        else if (4 == choice)
        {
            // something
        }
        else if (5 == choice)
        {
            running = false;
            break;
        }
        choice = -1;
    }
}
