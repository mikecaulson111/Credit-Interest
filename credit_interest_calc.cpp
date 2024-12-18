#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;



int main(int argc, char* argv[]) {

    // Global Variables for entire project
    string input = "";
    double loan_amt = 0;
    double interest_rate = 0.0;
    double month_payments = 0;
    double loan_hold = 0.0;
    double average_days_month = ((31*7)+(30*4)+(28)) / 12;
    bool print_years = false;
    bool daily_interest = false;

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
    loan_hold = loan_amt;

    // Calculate if loan can ever be paid off with current payments
    if ((loan_amt - month_payments) * ((interest_rate / 100.0) / 12) >= month_payments ) {
        cout << "*** PAYING THAT AMOUNT PER MONTH YOU WILL NEVER PAY OFF YOUR LOAN ***" << endl;
        return 0;
    }

    if (argc > 1) {
        if (0 == strcmp(argv[1], "-y")) {
            print_years = true;
        } else if (0 == strcmp(argv[1], "-d")) {
            daily_interest = true;
        }
    }

    // global calulation variables
    double total_interest = 0;
    int months = 1;
    double year_tot_paid = 0;
    double year_tot_interest = 0;

    while (loan_amt > 0) {

        // month by month calculation variables
        double holding_amount = loan_amt;
        double daily_interest = holding_amount * ((interest_rate / 100.0) / 365);
        double accumulated_interest = 0;

        // calculate interest every day for an 'average' month
        for (int i = 0; i < average_days_month; i++) {
            accumulated_interest += daily_interest;
        }

        // Add 'average month' accumulated interest to total total interest
        total_interest += accumulated_interest;

        // Update load amount by first adding the interest and then subtracting payment
        // this is assuming that the payment is done at the end of the billing cycle
        loan_amt = holding_amount + accumulated_interest - month_payments;


        if (loan_amt < 0) {
            loan_amt = 0;
        }
        if (daily_interest < 0) {
            daily_interest = 0;
        }

        // If we are printing
        if (!print_years) {
            cout << "Month " << months << " Balance: $" << loan_amt << " Interest acrued: $" << accumulated_interest << endl;
        } else {
            if (months % 12 == 0) {
                cout << "Year " << months / 12 << " Balance: $" << loan_amt << " Interest acrued throught the year: $" << year_tot_interest << " Total paid off throught the year: $" << year_tot_paid << endl;
                year_tot_paid = 0;
                year_tot_interest = 0;
            } else if (print_years && !daily_interest) {
                year_tot_paid += month_payments;
                year_tot_interest += daily_interest;
            }
        }
        months += 1;
    }
    cout << "Loan paid off in " << months - 1 << " months with total interest paid $" << total_interest << " on the initial $" << loan_hold << " loan" << endl;

    return 0;
}
