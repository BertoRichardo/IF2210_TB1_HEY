#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Inventory
{
private:
    vector<vector<T>> buffer;

public:
    Inventory(/* args */);
    ~Inventory();
    void print_inventory();
    void add_item(int col, int row);
    void remove_item(int col, int row);
    T info_item(int col, int row);
};
