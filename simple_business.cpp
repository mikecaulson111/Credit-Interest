#include <iostream>
#include <iomanip>
#include <string>
#include "simple_business.hpp"
#include "utils.hpp"


using namespace std;

void simple_business_initiate()
{
    bool running = true;
    string input;
    int choice = -1;
    string input2;

    Business* p_business = new Business();

    cout << "The main purpose of this is to show you your inventory, and costs on a per month basis" << endl;
    
    while (running) {
        cout << "What would you like to do:" << endl;
        cout << "[1] Add Item to Business Inventory" << endl;
        cout << "[2] Add Cost" << endl;
        cout << "[3] Print Business information" << endl;
        cout << "[4] Quit" << endl;

        getline(cin, input, '\n');
        if (is_numb(input, false)) {
            choice = stoi(input);
        }

        if (1 == choice) {
            // Add an item to inventory
            string name;
            double buy_price = 0.;
            double sell_price = 0.;
            int num_of_products = 0;
            cout << "Please enter the name of the item" << endl;
            getline(cin, input2, '\n');
            name =  input2;
            cout << "Enter the price you pay for each " << name << "\n$";
            getline(cin, input2, '\n');
            if (is_numb(input2, true)) {
                buy_price = stod(input2);
            }
            cout << "Enter the price you sell each " << name << " for:\n$";
            getline(cin, input2, '\n');
            if (is_numb(input2, true)) {
                sell_price = stod(input2);
            }
            cout << "Enter the number of " << name << " in stock\n#";
            getline(cin, input2, '\n');
            if (is_numb(input2, false)) {
                num_of_products = stoi(input2);
            }

            p_business->add_item(name, sell_price, buy_price, num_of_products);
        } else if (2 == choice) {
            // Add a fixed (expected) cost
            string name;
            double cost = 0.;
            cout << "Please enter the name of the cost:" << endl;
            getline(cin, input2, '\n');
            name = input2;
            cout << "Enter the cost of " << name << " per month:\n$";
            getline(cin, input2, '\n');
            if (is_numb(input2, true)) {
                cost = stod(input2);
            }

            p_business->add_cost(name, cost);
        } else if (3 == choice) {
            // Display the business overview
            p_business->print_business();
        } else if (4 == choice) {
            running = false;
            break;
        }
        choice = -1;
    }
}

void Business::add_item(string name, double sell_price, double buy_price, int num_of_items) {
    BUSINESS_ITEM_S item = {
        .name = name,
        .sell_price = sell_price,
        .buy_price = buy_price,
        .num_of_product = num_of_items
    };
    items.push_back(item);
}

void Business::add_cost(string name, double _cost) {
    BUSINESS_COST_S cost = {
        .name = name,
        .cost = _cost
    };
    costs.push_back(cost);
}

void Business::print_business() {
    double total_potential = 0.;
    double total_cost = 0.;
    double total_profit = 0.;
    cout << "\n\n\n" << endl;
    cout << "ITEMS: " << endl;
    cout << left << setw(25) << "NAME" << "|" << setw(15) << "PURCHASE PRICE" << "|" << setw(15) << "SELL PRICE" << "|" << setw(15) << "# in inventory" << "|" << setw(15) << "expected profit" << "|" << endl;
    for (size_t i = 0; i < items.size(); i++) {
        BUSINESS_ITEM_S item = items.at(i);
        double potential_profit = (item.sell_price - item.buy_price) * item.num_of_product;
        total_potential += potential_profit;
        cout << "-------------------------|---------------|---------------|---------------|---------------|" << endl;
        cout << left << setw(25) << item.name;
        cout << "|$";
        cout << setw(14) << item.buy_price;
        cout << "|$";
        cout << setw(14) << item.sell_price;
        cout << "|";
        cout << setw(15) << item.num_of_product;
        cout << "|$";
        cout << (potential_profit > 0 ? COLOR_GREEN : COLOR_RED) << setw(14) << potential_profit << COLOR_RESET;
        cout << "|" << endl;
        
    }
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(35) << "Total Potential/Expected Profit:";
    cout << "|$";
    cout << (total_potential > 0 ? COLOR_GREEN : COLOR_RED) << setw(14) << total_potential << COLOR_RESET << "|" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "\n\nCOSTS:" << endl;
    cout << left << setw(25) << "NAME" << "|" << setw(15) << "COST" << "|" << endl;
    for (size_t i = 0; i < costs.size(); i++) {
        BUSINESS_COST_S cost = costs.at(i);
        total_cost += cost.cost;
        // cout << cost.name << " $" << cost.cost << endl;
        cout << "-------------------------|---------------|" << endl;
        cout << left << setw(25) << cost.name;
        cout << "|$";
        cout << setw(14) << cost.cost;
        cout << "|" << endl;
    }
    total_profit = total_potential - total_cost;
    cout << "------------------------------------------" << endl;
    cout << left << setw(25) << "Total Cost:";
    cout << "|$" << COLOR_RED << setw(14) << total_cost << COLOR_RESET << "|" << endl;
    cout << "\n\n\n" << endl;
    cout << left << setw(40) << "Total profit if all items are sold:";
    cout << "|$" << (total_profit > 0 ? COLOR_GREEN : COLOR_RED) << setw(14) << total_profit << COLOR_RESET << "|" <<  endl;
    cout << "\n\n\n" << endl;
}

