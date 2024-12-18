#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "calcs.hpp"

using namespace std;



int main(int argc, char* argv[]) {

    // Global Variables for entire project
    string input = "";
    double loan_amt = 0;
    double interest_rate = 0.0;
    double month_payments = 0;
    bool print_years = false;
    bool daily_interest_used = false;

    // Get input for principle loan amount
    cout << "Please enter the current loan amount (can be integer or double):" << endl;
    getline(cin, input, '\n');
    loan_amt = stod(input);
    
    // Get input for interest rate
    cout << "Please enter the interest rate (as a decimal i.e. 8.49):" << endl;
    getline(cin, input, '\n');
    interest_rate = stod(input);

    // Get input for amount paid each month
    cout << "Please enter the amount you pay every month (can be integer or decimal):" << endl;
    getline(cin, input, '\n');
    month_payments = stod(input);

    cout << "$" << std::fixed << std::setprecision(2) << loan_amt << " at " << interest_rate << "% paying $" << month_payments << endl;

    // Calculate if loan can ever be paid off with current payments
    if ((loan_amt - month_payments) * ((interest_rate / 100.0) / 12) >= month_payments ) {
        cout << "*** PAYING THAT AMOUNT PER MONTH YOU WILL NEVER PAY OFF YOUR LOAN ***" << endl;
        return 0;
    }

    if (argc > 1) {
        if (0 == strcmp(argv[1], "-y")) {
            print_years = true;
        } else if (0 == strcmp(argv[1], "-d")) {
            daily_interest_used = true;
        }
    }

    calculate_total_with_fixed_payments( loan_amt, interest_rate, month_payments, print_years, daily_interest_used);
    calculate_minimum_monthly_with_fixed_term( 1083, 28.99, 72);

    return 0;
}
