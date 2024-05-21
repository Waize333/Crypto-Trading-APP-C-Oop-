#pragma once

#include<string>

using namespace std;
enum class orderBookType{bid,ask,unknown};

class OrderBookEntry{
public:
OrderBookEntry(double price,
            double amount,
            string timeStamp,
            string product,
            orderBookType ordertype);

static orderBookType stringToOrderbookType(string s);

double price;
double amount;
string timeStamp;
string product;
orderBookType ordertype;

};

