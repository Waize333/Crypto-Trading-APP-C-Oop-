#pragma once

#include<string>

using namespace std;
enum class orderBookType{bid,ask,unknown,sale};

class OrderBookEntry{
public:
OrderBookEntry(double price,
            double amount,
            string timeStamp,
            string product,
            orderBookType ordertype);

static orderBookType stringToOrderbookType(string s);
static bool compareByTimeStamp(OrderBookEntry& e1,OrderBookEntry& e2);
double price;
double amount;
string timeStamp;
string product;
orderBookType ordertype;

};

