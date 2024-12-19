#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "calcs.hpp"
#include "utils.hpp"

using namespace std;



int main(int argc, char* argv[]) {

    // Global Variables for entire project
    string input = "";
    double loan_amt = 0;
    double interest_rate = 0.0;
    double month_payments = 0;
    double num_months = 0;
    bool print_years = false;
    bool daily_interest_used = false;
    int choice = 0;

    while (true)
    {
        cout << "Please choose one of these options to perform:" << endl;
        cout << "[1] Calculate total payoff amount" << endl;
        cout << "[2] Calculate minimum monthly payment with fixed term" << endl;
        cout << "[3] Quit" << endl;
        getline(cin, input, '\n');
        if (is_numb(input)) {
            choice = stod(input);
        }


        if (choice == 1)
        {
            // Get input for principle loan amount
            cout << "Please enter the current loan amount (can be integer or double):" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                loan_amt = stod(input);
            }
            
            // Get input for interest rate
            cout << "Please enter the interest rate (as a decimal i.e. 8.49):" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                interest_rate = stod(input);
            }

            // Get input for amount paid each month
            cout << "Please enter the amount you pay every month (can be integer or decimal):" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                month_payments = stod(input);
            }

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

            // Do the calculation
            calculate_total_with_fixed_payments( loan_amt, interest_rate, month_payments, print_years, daily_interest_used);
        }
        else if ( choice == 2 )
        {
            // Get input for principle loan amount
            cout << "Please enter the current loan amount (can be integer or double):" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                loan_amt = stod(input);
            }
            
            // Get input for interest rate
            cout << "Please enter the interest rate (as a decimal i.e. 8.49):" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                cout << "MJC MJC" << endl;
                interest_rate = stod(input);
            }

            // Get input for amount paid each month
            cout << "Please enter the number of months that the loan term is for:" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                num_months = stod(input);
            }

            // get interest, loan and term
            cout << "$" << std::fixed << std::setprecision(2) << loan_amt << " at " << interest_rate << "% for " << num_months << " months" << endl;

            // Perform calculation
            calculate_minimum_monthly_with_fixed_term( loan_amt, interest_rate, num_months );
        }
        else
        {
            if ( 0 != choice )
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
