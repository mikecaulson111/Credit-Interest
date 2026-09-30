#ifndef SIMPLE_BUSINESS_HPP
#define SIMPLE_BUSINESS_HPP

#include <vector>
#include <string>

using namespace std;

typedef struct {
    string name;
    double sell_price; // this is how much the item is selling for
    double buy_price; // this is what the business incurs to have the item
    int num_of_product; // this is how many there are in inventory
} BUSINESS_ITEM_S;

typedef struct {
    string name;
    double cost; // this is the cost per month of the cost (i.e. employee paid $1000, rent $3500)
} BUSINESS_COST_S;

class Business {
private:
    vector<BUSINESS_ITEM_S> items;
    vector<BUSINESS_COST_S> costs;
public:
    void add_item(string name, double sell_price, double buy_price, int num_of_product=0);
    void add_cost(string name, double cost);
    void print_business();
};

void simple_business_initiate();

#endif /* SIMPLE_BUSINESS_HPP */
