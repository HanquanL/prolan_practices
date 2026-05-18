#ifndef SALES_DATA_H
#define DALES_DATA_H

#include <string>
using namespace std;

double Sales_data::avg_price() const {
    if(units_sold){
        return revenue / units_sold;
    }else{
        return 0;
    }
}

Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;

}

struct Sales_data{
        string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;

        string isbn() {return bookNo;}
        Sales_data& combine (const Sales_data&);
        double avg_price() const;

    };
#endif