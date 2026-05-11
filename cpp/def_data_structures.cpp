#include <iostream>
#include <string>
#include "sales_data.h"


using namespace std;

int main(){

    double price = 3;

    // struct Sales_data{
    //     string bookNo;
    //     unsigned units_sold = 0;
    //     double revenue = 0.0;
    // };

    Sales_data my_data;
    my_data.bookNo = "0-201-78345-X";
    my_data.units_sold = 6;
    my_data.revenue = my_data.units_sold * price;

    cout << "bookNo: " << my_data.bookNo << endl;
    cout << "unit_sold: " << my_data.units_sold << endl;
    cout << "revenue: " << my_data.revenue << endl;

}