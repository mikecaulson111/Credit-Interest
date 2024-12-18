#ifndef CALCS_HPP
#define CALCS_HPP

void calculate_total_with_fixed_payments(double loan_amt, double interest, double monthly_payments, bool print_years=false, bool daily_interest_used=false);
// void calculate_total_with_fixed_term(double loan_amt, double interest, double num_months);
void calculate_minimum_monthly_with_fixed_term(double loan_amt, double interest, double num_months);

#endif
