#ifndef CALCS_HPP
#define CALCS_HPP

typedef struct
{
    int months;
    double interest_amt;
} AMORTIZATION_S;

typedef struct
{
    double min;
    double max;
    double percent;
} TAX_BRACKET_S;


void calculate_total_with_fixed_payments(double loan_amt, double interest, double monthly_payments, bool print_years=false, bool daily_interest_used=false, bool amortization=false);
// void calculate_total_with_fixed_term(double loan_amt, double interest, double num_months);
void calculate_minimum_monthly_with_fixed_term(double loan_amt, double interest, double num_months, bool amortization=false);
void calculate_worst_taxes(double income, int filing_status=1);

#endif
