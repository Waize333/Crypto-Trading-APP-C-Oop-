#include<vector>
#include<iostream>
#include"OrderBookEntry.h"
using namespace std;
class WaizMain
{
private:

public:
    WaizMain();
    void init();
    private:
    void loadOrderBook();
    void printMenu();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterOffer();
    void enterBid();
    void pritWallet();
    void nextTimeFrame();
    void processUserOption(int userOption );
    vector<OrderBookEntry> orders;
   
};

