#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "calcs.hpp"
#include "assets.hpp"
#include "utils.hpp"

using namespace std;



int main() {

    // Global Variables for entire project
    string input = "";
    int choice = 0;

    AssetsList* p_list = new AssetsList();

    while (true)
    {
        cout << "Please choose one of these options to perform:" << endl;
        cout << "[1] Calculate total payoff amount" << endl;
        cout << "[2] Calculate minimum monthly payment with fixed term" << endl;
        cout << "[3] Worst case tax case (only standard deduction)" << endl;
        cout << "[4] Assets list and calculation" << endl;
        cout << "[5] Calculate break even for single product" << endl; // TODO: would like to expand this to class with each having component parts
        cout << "[6] Savings goal calculator" << endl;
        cout << "[7] Quit" << endl;
        getline(cin, input, '\n');
        if (is_numb(input)) {
            choice = stod(input);
        }


        if (choice == 1)
        {
            calculate_total_with_fixed_payments();
        }
        else if ( choice == 2 )
        {
            calculate_minimum_monthly_with_fixed_term();
        }
        else if (3 == choice)
        {
            calculate_worst_taxes();
        }
        else if (4 == choice)
        {
            assets_initiate(p_list);
        }
        else if (5 == choice)
        {
            calculate_break_even_single();
        }
        else if (6 == choice)
        {
            calculate_savings_goal();
        }
        else
        {
            if ( 7 == choice )
            {
                break;
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }

    return 0;
}
