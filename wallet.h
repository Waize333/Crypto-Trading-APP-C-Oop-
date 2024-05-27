#pragma once
#include<iostream>
#include<string>
#include<map>
#include"OrderBookEntry.h"
using namespace std;


class Wallet
{
    public:
        Wallet();
        void insertCurrency(string type,double amount);
        bool removeCurrency(string type,double amount);
        bool canFulfilOrder(OrderBookEntry order);
        bool containsCurrency(string type,double amount);
        string toString();
        //updates the contents of the wallet 
        //Assuming the order was made by the owner of the wallet 
        void processSale(OrderBookEntry& sale);
    private:
        map<string,double> currencies;
};