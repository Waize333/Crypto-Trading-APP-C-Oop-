#pragma once

#include<string>

using namespace std;
enum class orderBookType{bid,ask,unknown,bidSale,askSale};

class OrderBookEntry{
public:
OrderBookEntry(double price,
            double amount,
            string timeStamp,
            string product,
            orderBookType ordertype,
            string username="dataset");
 static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.timeStamp < e2.timeStamp;
        }  
static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }

static orderBookType stringToOrderbookType(string s);
double price;
double amount;
string timeStamp;
string product;
orderBookType ordertype;
string username;
};

