#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <vector>
#include <string>

using namespace std;

typedef struct
{
    string name;
    bool is_equity; // true if equity, false if liability
    double amount;  // the cost/worth of the asset item
} ASSET_ITEM_S;

class AssetsList {
    private:
        vector<ASSET_ITEM_S> items;
    public:
        void add_item(string name, bool is_equity=false, double amount=0.0);
        void print_items();
};

void assets_initiate(AssetsList* p_list);

#endif /* ASSETS_HPP */
