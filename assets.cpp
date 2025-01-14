#include <iostream>
#include <iomanip>
#include <string>
#include "assets.hpp"
#include "utils.hpp"

using namespace std;

int AssetsList::is_item_in_list(string name)
{
    for (long unsigned int i = 0; i < items.size(); i++)
    {
        if (name == items.at(i).name)
        {
            return (int)i;
        }
    }
    return -1;
}

void AssetsList::calculate_total_assets()
{
    double temp = 0;
    for (long unsigned int i = 0; i < items.size(); i++)
    {
        temp += ((items.at(i).is_equity ? 1 : -1) * items.at(i).amount);
    }
    total_assets = temp;
}

void AssetsList::add_item(string name, bool is_equity, double amount)
{
    // cout << name << is_equity << amount << endl;
    ASSET_ITEM_S asset = {.name = name,
                          .is_equity = is_equity,
                          .amount = amount};

    items.push_back(asset);
    calculate_total_assets();
}

void AssetsList::edit_item(string name)
{
    string input;
    double temp_amount;
    int pos = -1;

    pos = is_item_in_list(name);
    if (-1 != pos)
    {
        cout << "What would you like to do with " << name  << "?" << endl;
        cout << "[1] Edit name\n[2] Edit equity\n[3] Edit amount" << endl;
        getline(cin, input, '\n');
        if (is_numb(input))
        {
            int temp = stoi(input);

            if (1 == temp)
            {
                cout << "Enter the new name now:" << endl;
                getline(cin, input, '\n');
                items.at(pos).name = input;
            }
            else if (2 == temp)
            {
                cout << "Enter the new value for equity/liability\n[1] Equity\n[2] Liability" << endl;
                getline(cin, input, '\n');
                if (is_numb(input))
                {
                    if (1 == stoi(input))
                    {
                        items.at(pos).is_equity = true;
                    }
                    else if (2 == stoi(input))
                    {
                        items.at(pos).is_equity = false;
                    }
                    else
                    {
                        cout << "Not a valid option: " << stoi(input) << " enter only 1 or 2 next time" << endl;
                    }
                }
            }
            else if (3 == temp)
            {
                cout << "Please enter the new amount\n$";
                getline(cin, input, '\n');
                if (is_numb(input, true))
                {
                    temp_amount = stod(input);
                    items.at(pos).amount = temp_amount;
                }
                else
                {
                    cout << "Please only enter a number (double) for the amount" << endl;
                }
            }

        }
        else
        {
            cout << "Please only enter a number next time" << endl;
        }
        calculate_total_assets();
    }
    else
    {
        cout << name << " is not in the list of items" << endl;
    }
}

void AssetsList::delete_item(string name)
{
    int pos = -1;
    string input;
    
    pos = is_item_in_list(name);
    if (-1 != pos)
    {
        cout << "\n\nPlease confirm you would like to remove " << name << " from the list of items (Y/N)" << endl;
        getline(cin, input, '\n');
        if (input == "Y" || input == "y" || input == "Yes" || input == "YES" || input == "yes")
        {
            cout << "Removing from list......" << endl;
            items.erase(items.begin() + pos);
        }
        else
        {
            cout << "Not removing..." << endl;
        }
    }

    calculate_total_assets();
}

void AssetsList::print_items()
{
    cout << "\n\n\n" << endl;
    cout << left << setw(25) << "NAME" << "|" << setw(10) << "EQUITY" << "|" << setw(18) << "AMOUNT" << " |" << endl;
    for (long unsigned int i = 0; i < items.size(); i++)
    {
        cout << "-------------------------|----------|-------------------|" << endl;
        cout << left << setw(25) << items.at(i).name;
        cout << "|";
        cout << setw(10) << (items.at(i).is_equity ? "Equity" : "Liability");
        cout << "|$";
        cout << setw(18) << items.at(i).amount;
        cout << "|" << endl;
    }
    cout << "--------------------------------------------------------|" << endl;
    cout << left << setw(25) << "Total Assets" << " " << setw(10) << " " << " $" << (total_assets > 0 ? "\033[32m" : "\033[31m") << total_assets << "\033[0m" << endl;
    cout << "\n\n\n" << endl;
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
            // Add item to list
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

            cout << "Please enter the amount" << (is_equity ? " that it is worth:\n$" : " that you owe:\n$");
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
            // Edit item in list
            cout << "Please enter the name of the item you would like to change" << endl;
            getline(cin, input, '\n');

            name = input;
            p_list->edit_item(name);
        }
        else if (3 == choice)
        {
            // Remove item from list
            cout << "Please enter the name of the item you would like to remove:" << endl;
            getline(cin, input, '\n');

            name = input;
            p_list->delete_item(name);
        }
        else if (4 == choice)
        {
            // Print Items
            p_list->print_items();
        }
        else if (5 == choice)
        {
            running = false;
            break;
        }
        choice = -1;
    }
}
