#pragma once

#include<string>

using namespace std;
enum class orderBookType{bid,ask};

class OrderBookEntry{
public:
OrderBookEntry(double price,
double amount,
string timeStamp,
string product,
orderBookType ordertype);

double price;
double amount;
string timeStamp;
string product;
orderBookType ordertype;

};

