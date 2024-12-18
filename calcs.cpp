#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include "calcs.hpp"


using namespace std;



void calculate_total_with_fixed_payments(double loan_amt, double interest_rate, double monthly_payments,
                                         bool print_years, bool daily_interest_used)
{

    // global calulation variables
    double total_interest = 0;
    int months = 1;
    double year_tot_paid = 0;
    double year_tot_interest = 0;
    double average_days_month = (365. / 12.);
    double loan_hold = loan_amt;

    while (loan_amt > 0) {

        // month by month calculation variables
        double holding_amount = loan_amt;
        double daily_interest = holding_amount * ((interest_rate / 100.0) / (daily_interest_used ? 365 : 12));
        double accumulated_interest = 0;

        // calculate interest every day for an 'average' month
        if (daily_interest_used)
        {
            for (int i = 0; i < average_days_month; i++) {
                accumulated_interest += daily_interest;
            }
        }
        else
        {
            accumulated_interest += daily_interest;
        }

        // Add 'average month' accumulated interest to total total interest
        total_interest += accumulated_interest;

        // Update load amount by first adding the interest and then subtracting payment
        // this is assuming that the payment is done at the end of the billing cycle
        loan_amt = holding_amount + accumulated_interest - monthly_payments;


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
            } else if (print_years && !daily_interest_used) {
                year_tot_paid += monthly_payments;
                year_tot_interest += daily_interest;
            }
        }
        months += 1;
    }
    cout << "Loan paid off in " << months - 1 << " months with total interest paid $" << total_interest << " on the initial $" << loan_hold << " loan" << endl;
    cout << "This equals a total repayment of: $" << total_interest + loan_hold << "." << endl;
}


void calculate_minimum_monthly_with_fixed_term(double loan_amt, double interest, double num_months)
{
    double top = 0;
    double bottom = 0;

    double decimal_interest = (interest / 100.) / 12.;

    top = decimal_interest * pow(1 + decimal_interest, num_months);
    bottom = pow(1 + decimal_interest, num_months) - 1;

    cout << "Minimum Monthly Payments to pay off $" << loan_amt << " at " << interest << "%  in " << num_months << " months is: $" << loan_amt * top / bottom << " per month." << endl;
}
