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


void calculate_total_with_fixed_payments();
// void calculate_total_with_fixed_term(double loan_amt, double interest, double num_months);
void calculate_minimum_monthly_with_fixed_term();
void calculate_worst_taxes();
void calculate_break_even_single();
void calculate_savings_goal();

#endif
