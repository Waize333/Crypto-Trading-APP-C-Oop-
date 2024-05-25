#include"OrderBook.h"
#include<map>


  // making a constructor to rad Csv data file
    OrderBook::OrderBook(string filename)
    {
        orders=CSVReader::ReadCSV(filename);
    }
    //vector OF ALL KNOW PRODUCTS IN DATASET
    vector<string>OrderBook::getKnownProducts()
    {
        vector<string>products;

        map<string,bool>prodMap;

        for(OrderBookEntry& elem : orders)
        {
            prodMap[elem.product]=true;
        }

        for(pair<const string, bool>& e:prodMap)
        {
            products.push_back(e.first);
        }
        return products;
    }
    // return the vector of order according to the filters
    vector<OrderBookEntry>OrderBook::getOrders(orderBookType type, 
                                    string product,
                                    string timeStamp )
                                   
    {
        vector<OrderBookEntry>orderSubs;
        for(auto const & e:orders)
        {
            if(e.ordertype==type &&
               e.product==product&&
               e.timeStamp==timeStamp)
            {
                orderSubs.push_back(e);
            }

        }
        return orderSubs;
    }
    double OrderBook::getHighPrice(vector<OrderBookEntry>& orders)
    {
        double max=orders[0].price;
        for(auto &elem : orders)
        {
            if(elem.price>max)max=elem.price;
        }
        return max;

    }
     double OrderBook::getMinPrice(vector<OrderBookEntry>& orders)
    {
        double min=orders[0].price;
        for(auto &elem : orders)
        {
            if(elem.price<min)min=elem.price;
        }
        return min;

    }
    string OrderBook::getEarliestTime()
    {
        return orders[0].timeStamp;
    }
