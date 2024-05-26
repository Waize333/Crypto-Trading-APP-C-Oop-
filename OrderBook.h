#pragma once
#include"OrderBookEntry.h"
#include"CSVReader.h"

class OrderBook
{
    public:
    // making a constructor to rad Csv data file
    OrderBook(string filename);
    //vector OF ALL KNOW PRODUCTS IN DATASET
    vector<string>getKnownProducts();
    // return the vector of order according to the filters
    vector<OrderBookEntry>getOrders(orderBookType type, 
                                    string product,
                                    string timeStamp );

    string getEarliestTime();
    string getNextTime(string timeStamp);
    void insertOrder(OrderBookEntry& order);
    vector<OrderBookEntry> matchAsksToBids(string product,string timeStamp);
    static double getHighPrice(vector<OrderBookEntry>& orders);
    static double getMinPrice(vector<OrderBookEntry>& orders);
    private :
    vector<OrderBookEntry>orders;  
                                 
                                






};