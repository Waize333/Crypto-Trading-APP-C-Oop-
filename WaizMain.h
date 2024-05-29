#pragma once
#include<vector>
#include<iostream>
#include"OrderBookEntry.h"
#include"OrderBook.h"
#include"wallet.h"
using namespace std;
class WaizMain
{
private:

public:
    WaizMain();
    void init();
    private:
    void printMenu();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void nextTimeFrame();
    void processUserOption(int userOption );
    
    OrderBook orderBook{"live_data.csv"};
    string currentTime;
    Wallet wallet;
};

