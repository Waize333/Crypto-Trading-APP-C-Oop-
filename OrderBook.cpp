#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <iostream>


  // making a constructor to read Csv data file
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
string OrderBook::getNextTime(string timeStamp)
{
    
    string nextTimeStamp = "";
    for (const auto& e : orders) {
        if (e.timeStamp > timeStamp) {
            nextTimeStamp = e.timeStamp;
            break;
        }
    }
    if (nextTimeStamp == "") 
    {
        nextTimeStamp = orders[0].timeStamp;
    }
    return nextTimeStamp;
}
//using a lambda function for Sorting
auto comp = [](const OrderBookEntry& e1, const OrderBookEntry& e2) {
    return e1.timeStamp < e2.timeStamp;
};


void OrderBook::insertOrder(OrderBookEntry& order)
{
   orders.push_back(order);
   sort(orders.begin(),orders.end(),comp);
}
/** Match asks to bids and return the sales */
vector<OrderBookEntry> OrderBook::matchAsksToBids(string product, string timestamp) {
    // Get all asks and bids for the given product and timestamp
    vector<OrderBookEntry> asks = getOrders(orderBookType::ask, product, timestamp);
    vector<OrderBookEntry> bids = getOrders(orderBookType::bid, product, timestamp);
    vector<OrderBookEntry> sales;

    // Check if there are bids and asks to process
    if (asks.size() == 0 || bids.size() == 0) {
        cout << " OrderBook::matchAsksToBids no bids or asks" << endl;
        return sales;
    }
auto Asc = [](const OrderBookEntry& e1, const OrderBookEntry& e2) {
    return e1.price < e2.price;
};

    // Sort asks lowest first
    sort(asks.begin(), asks.end(),Asc);
    
auto Dsc = [](const OrderBookEntry& e1, const OrderBookEntry& e2) {
    return e1.price > e2.price;
};

    // Sort bids highest first
    sort(bids.begin(), bids.end(),Dsc);

    // Iterate through asks and bids to match and generate sales
    // for each ask in asks:
    for (OrderBookEntry& ask : asks) {
        // for each bid in bids:
        for (OrderBookEntry& bid : bids) {
            // if bid.price >= ask.price, we have a match
            if (bid.price >= ask.price) {
                // Create a sale entry
                OrderBookEntry sale{ask.price, 0, timestamp, product, orderBookType::askSale};

                // Determine usernames and order types
                if (bid.username == "simUser") {
                    sale.username = "simUser";
                    sale.ordertype = orderBookType::bidSale;
                }
                if (ask.username == "simUser") {
                    sale.username = "simUser";
                    sale.ordertype = orderBookType::askSale;
                }

                // Now calculate how much was sold or not
                if (bid.amount == ask.amount) {
                    // Bid completely clears ask
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0; // Make sure the bid is not processed again
                    break; // Can do no more with this ask, go onto the next ask
                }
                if (bid.amount > ask.amount) {
                    // Ask is completely gone, slice the bid
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount -= ask.amount; // Adjust the bid in place for next ask
                    break;
                }
                if (bid.amount < ask.amount && bid.amount > 0) {
                    // Bid is completely gone, slice the ask
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount -= bid.amount; // Update the ask for further bids
                    bid.amount = 0; // Make sure the bid is not processed again
                    continue; // Some ask remains, go to the next bid
                }
            }
        }
    }
    return sales;
}