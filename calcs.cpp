#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include "calcs.hpp"
#include "utils.hpp"


using namespace std;

#define NUM_BRACKETS 7
#define STANDARD_DEDUCTION_SINGLE 14600
#define STANDARD_DEDUCTION_JOINT 29200
#define STANDARD_DEDUCTION_HEAD 21900

/*
0 - 11,925        : 10%
11,925 - 48,475   : 12%
48,475 - 103,350  : 22%
103,350 - 197,300 : 24%
197,300 - 250,525 : 32%
250,525 - 626,350 : 35%
626,350+          : 37%
*/
TAX_BRACKET_S brackets[] = { {0, 11925, 10},
                             {11925, 48475, 12},
                             {48475, 103350, 22},
                             {103350, 197300, 24},
                             {197300, 250525, 32},
                             {250525, 626350, 35},
                             {626350, 1000000000000, 37}
                           };

AMORTIZATION_S amortization_print(double loan_amt, double interest_rate, double monthly_payments,
                          bool print_years, bool daily_interest_used, bool amortization)
{
    AMORTIZATION_S amortization_ret = {};

    // global calulation variables
    double total_interest = 0;
    int months = 1;
    double year_tot_paid = 0;
    double year_tot_interest = 0;
    double average_days_month = (365. / 12.);

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


        if (loan_amt <= 0) {
            loan_amt = 0;
        }
        if (daily_interest < 0) {
            daily_interest = 0;
        }

        // If we are printing
        if (amortization) {
            if (!print_years) {
                cout << "Month " << months << " Balance: $" << loan_amt << " Interest acrued: $" << accumulated_interest << " -> Paid: $" << ((loan_amt + accumulated_interest < monthly_payments) ? (loan_amt+accumulated_interest) : monthly_payments) << endl;
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
        }
        months += 1;
        if (loan_amt + accumulated_interest < monthly_payments)
        {
            break;
        }
    }
    amortization_ret.months       = months;
    amortization_ret.interest_amt = total_interest;

    return amortization_ret;
}

void calculate_total_with_fixed_payments()
{
    string input;
    double loan_amt = 0;
    double interest_rate = 0;
    double monthly_payments = 0;
    bool print_years = false;
    bool daily_interest_used = false;
    bool amortization = false;
    AMORTIZATION_S amort = {};


    cout << "Would you like the amortization schedule to display? (Y/N)" << endl;
    getline(cin, input, '\n');
    if (input == "Y" || input == "y" || input == "1")
    {
        amortization = true;
    }
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
        monthly_payments = stod(input);
    }

    cout << "$" << std::fixed << std::setprecision(2) << loan_amt << " at " << interest_rate << "% paying $" << monthly_payments << endl;

    // Calculate if loan can ever be paid off with current payments
    if ((loan_amt - monthly_payments) * ((interest_rate / 100.0) / 12) >= monthly_payments ) {
        cout << "*** PAYING THAT AMOUNT PER MONTH YOU WILL NEVER PAY OFF YOUR LOAN ***" << endl;
        return;
    }
    
    // if (argc > 1) {
    //     if (0 == strcmp(argv[1], "-y")) {
    //        print_years = true;
    //    } else if (0 == strcmp(argv[1], "-d")) {
    //        daily_interest_used = true;
    //    }
    //}

    amort = amortization_print(loan_amt, interest_rate, monthly_payments, print_years, daily_interest_used, amortization);

    
    cout << "\n\n--------------------------------------------------------------------------" << endl;
    cout << "Loan paid off in " << amort.months - 1 << " months with total interest paid $" << amort.interest_amt << " on the initial $" << loan_amt << " loan" << endl;
    cout << "This equals a total repayment of: $" << amort.interest_amt + loan_amt << "." << endl;
    cout << "--------------------------------------------------------------------------" << endl;
}


void calculate_minimum_monthly_with_fixed_term()
{
    double top = 0;
    double bottom = 0;
    double loan_amt = 0;
    double interest = 0;
    double num_months = 0;
    bool amortization = false;
    double decimal_interest = 0;
    string input;

    cout << "Would you like the amortization schedule to display? (Y/N)" << endl;
    getline(cin, input, '\n');
    if (input == "Y" || input == "y" || input == "1")
    {
        amortization = true;
    }
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
        interest = stod(input);
    }

    // Get input for amount paid each month
    cout << "Please enter the number of months that the loan term is for:" << endl;
    getline(cin, input, '\n');
    if (is_numb(input, true))
    {
        num_months = stod(input);
    }

    // get interest, loan and term
    cout << "$" << std::fixed << std::setprecision(2) << loan_amt << " at " << interest << "% for " << num_months << " months" << endl;

    decimal_interest = (interest / 100.) / 12.;


    top = decimal_interest * pow(1 + decimal_interest, num_months);
    bottom = pow(1 + decimal_interest, num_months) - 1;
    if (amortization)
    {
        amortization_print(loan_amt, interest, (loan_amt * top / bottom), false, false, amortization);
    }

    cout << "\n\n--------------------------------------------------------------------------" << endl;
    cout << "Minimum Monthly Payments to pay off $" << loan_amt << " at " << interest << "%  in " << num_months << " months is: $" << loan_amt * top / bottom << " per month." << endl;
    cout << "--------------------------------------------------------------------------" << endl;
}

void calculate_worst_taxes()
{
    // double tincome = income;
    double total_taxes = 0;
    double temp = 0;
    double income = 0;
    int filing_status = -1;
    string input;
    // Get the income number from user
    cout << "Please enter your annual income (without commas):" << endl;
    getline(cin, input, '\n');
    if (is_numb(input, true))
    {
        income = stod(input);
    }
    
    // Get filing status:
    cout << "Please enter your Filing Status:\n[1] Single\n[2] Joint\n[3] Head of Household" << endl;
    getline(cin, input, '\n');
    if (is_numb(input, false))
    {
        filing_status = stoi(input);
    }

    // standard decuction:
    switch (filing_status)
    {
        case 2:
            income -= STANDARD_DEDUCTION_JOINT;
            break;
        case 3:
            income -= STANDARD_DEDUCTION_HEAD;
            break;
        case 1:  /* fallthrough */
        default:
            income -= STANDARD_DEDUCTION_SINGLE;
            break;
    }

    for (int i = 0; i < NUM_BRACKETS; i++)
    {
        if (income > brackets[i].max)
        {
            // calculate total amount in this bracket and add to total
            temp = brackets[i].max - brackets[i].min;
            temp *= (brackets[i].percent / 100.);
            total_taxes += temp;
        }
        else
        {
            // calculate total up to the number minus min of this category
            temp = income - brackets[i].min;
            temp *= (brackets[i].percent / 100.);
            total_taxes += temp;
            break;
        }
    }
    // check that total_taxes is not less than 0, if so, set to 0:
    total_taxes = total_taxes < 0 ? 0 : total_taxes;

    cout << "\n\n--------------------------------------------------------------------------" << endl;
    cout << "Total in worst case taxes (with standard deduction): $" << total_taxes << endl;
    cout << "-------------------------------------------------------------------------" << endl;
}

void calculate_break_even_single()
{
    double cost_to_you = 0;
    double cost_to_consumer = 0;
    double profit = 0;
    double total_needed_to_sell = 0;
    double fixed_costs = 0;
    string input;

    cout << "Please enter the cost of the product that you have to pay:\n$";
    getline(cin, input, '\n');
    if (is_numb(input, true))
    {
        cost_to_you = stod(input);
    }
    else
    {
        cout << "Please enter a number next time. Returning..." << endl;
        return;
    }

    cout << "Please enter the price you sell the product for:\n$";
    getline(cin, input, '\n');
    if (is_numb(input, true))
    {
        cost_to_consumer = stod(input);
    }
    else
    {
        cout << "Please enter a number next time. Returning..." << endl;
        return;
    }

    cout << "Please enter the Fixed Costs (such as rent and manager salary etc):\n$";
    getline(cin, input, '\n');
    if (is_numb(input, true))
    {
        fixed_costs = stod(input);
    }
    else
    {
        cout << "Please enter a number next time. Returning..." << endl;
        return;
    }
    
    cout << "Please enter the profit you were hoping to get (if you want only break even, enter $0):\n$";
    getline(cin, input, '\n');
    if (is_numb(input, true))
    {
        profit = stod(input);
    }
    else
    {
        cout << "Invalid argument, assuming Profit = $0" << endl;
    }

    // Calculation:
    // profit = (fixed costs + profit) / (delta profit from item)
    total_needed_to_sell = (fixed_costs + profit) / (cost_to_consumer - cost_to_you );

    cout << "\n\n\nTotal number of units sold to cover fixed costs of $" << fixed_costs << " and get a profit of $" << profit << " is:" << endl;
    cout << (int)total_needed_to_sell + 1 << " units\n\n\n" << endl;

}

void calculate_savings_goal()
{
    string input;
    int choice;
    float goal;
    float amount; // this is the amount they could save each month
    float current = 0;
    int months; // This is the amount of months we have
    float interest = 0;

    cout << "What would you like to do:" << endl;
    cout << "[1] Calculate how long it will take to save x amount given a fixed amount to save every month" << endl;
    cout << "[2] Calculate how much you would have to save each month to save x amount in y months" << endl;
    getline(cin, input, '\n');
    if (is_numb(input, false))
    {
        choice = stoi(input);
    }
    else
    {
        cout << "Invalid argument, returning back to beginning" << endl;
        return;
    }

    while (true)
    {
        cout << "Please enter the total amount or goal you would like to save:" << endl;
        getline(cin, input, '\n');
        if (is_numb(input, true))
        {
            goal = stod(input);
            break;
        }
        else
        {
            cout << "Please only enter a number\n\n" << endl;
        }
    }

    if (goal <= 0)
    {
        cout << "Please enter a goal that is greater than 0" << endl;
        return;
    }

    cout << "Would you like to include interest in calculation (you are saving money into a savings account)? (Y/N)" << endl;
    getline(cin, input, '\n');
    if (input == "Y" || input == "y" || input == "1")
    {
        cout << "Please enter the interest rate on the savings account as a decimal (i.e. 3.5):" << endl;
        getline(cin, input, '\n');
        if (is_numb(input, true))
        {
            interest = stod(input);
            interest = interest / 100.0;
        }
        else
        {
            cout << "Invalid Argument, assuming interest of 0%" << endl;
        }
    }
    
    if (1 == choice)
    {
        // calc how long it will take to save x amount given fixed amount each month
        while (true)
        {
            cout << "Please enter the total amount of money you can save each month:" << endl;
            getline(cin, input, '\n');
            if (is_numb(input, true))
            {
                amount = stod(input);
                break;
            }
            else
            {
                cout << "Please only enter a number\n\n" << endl;
            }
        }

        while (current < goal)
        {
            current = current + amount;
            current = current + (current * interest / 12.0);
            months += 1;
        }
        
        cout << "\n\n\n" << endl;
        cout << "Paying $" << amount << " per month with " << interest * 100.0 << "% interest per year, it will take " << months << " months to save $" << goal << endl;
    }
    else
    {
        // calc how much to save each month to save x amount in y months
        cout << "Please enter the number of months you would like to save $" << goal << " in:" << endl;
        getline(cin, input, '\n');
        if (is_numb(input, false))
        {
            months = stoi(input);
        }
        else
        {
            cout << "Please only enter a number next time" << endl;
        }

        cout << "Note: currently this cannot factor in interest every month, so this will be the number of months if you dont include interest" << endl;

        cout << "\n\n\n" << endl;
        cout << "To save $" << goal << " in " << months << " months, you would need to save $" << goal / months << " per month" << endl;
    }
}





















