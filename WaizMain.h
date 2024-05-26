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
    void pritWallet();
    void nextTimeFrame();
    void processUserOption(int userOption );
    
    OrderBook orderBook{"tradingData.csv"};
    string currentTime;
    Wallet wallet;
};

