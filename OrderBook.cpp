#include"OrderBook.h"
#include<map>
#include<algorithm>

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
string OrderBook::getNextTime(string timeStamp)
{
    
    string nextTimeStamp = "";
    for (const auto& e : orders) {
        if (e.timeStamp > timeStamp) {
            nextTimeStamp = e.timeStamp;
            break;
        }
    }
    if (nextTimeStamp == "" && !orders.empty()) {
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
vector<OrderBookEntry> OrderBook::matchAsksToBids(string product,string timeStamp)
{
// asks = orderbook.asks in this timeframe
vector<OrderBookEntry>asks =getOrders(orderBookType::ask ,
                                    product,
                                    timeStamp );
// bids = orderbook.bids in this timeframe
vector<OrderBookEntry>bids =getOrders(orderBookType::bid ,
                                    product,
                                    timeStamp );

// sales = []
vector<OrderBookEntry>sales;

// sort asks lowest first
//using the custom lambda
auto Asc = [](const OrderBookEntry& e1, const OrderBookEntry& e2) {
    return e1.price < e2.price;
};
    sort(asks.begin(),asks.end(),Asc);
// sort bids highest first
auto Dsc = [](const OrderBookEntry& e1, const OrderBookEntry& e2) {
    return e1.price > e2.price;
};
    sort(bids.begin(),bids.end(),Dsc);

    cout << "max ask " << asks[asks.size()-1].price << std::endl;
    cout << "min ask " << asks[0].price << std::endl;
    cout << "max bid " << bids[0].price << std::endl;
    cout << "min bid " << bids[bids.size()-1].price << std::endl;
    
// for ask in asks:
for(OrderBookEntry& ask :asks){
//     for bid in bids:
for(OrderBookEntry& bid :bids){
//         if bid.price >= ask.price # we have a match
        if(bid.price>=ask.price){
//         sale = new orderbookentry()
//         sale.price = ask.price

        OrderBookEntry sale{ask.price,0,
                        timeStamp,product,
                        orderBookType::askSale};

     
        if(bid.username=="simUser"){
            sale.username="simUser";
            sale.ordertype=orderBookType::bidSale;
        }
         if(ask.username=="simUser")
        {
            sale.username="simUser";
            sale.ordertype=orderBookType::askSale;
        }

// # now calculating how much was sold or not
//         if bid.amount == ask.amount:
        if(bid.amount==ask.amount)
        {
        // # bid completely clears ask
        // sale.amount = ask.amount
        sale.amount=ask.amount;
        //sales.append(sale)
        sales.push_back(sale);
        // bid.amount = 0 # make sure the bid is not processed again
        bid.amount=0;
        // # can do no more with this ask
        // # go onto the next ask
           break;

        }
        if(bid.amount>ask.amount)
        {
        // if bid.amount > ask.amount: 
        // # ask is completely gone slice the bid
        // sale.amount = ask.amount
        sale.amount=ask.amount;   
        // sales.append(sale)
         sales.push_back(sale);
        // # we adjust the bid in place
        // # so it can be used to process the next ask
        // bid.amount = bid.amount - ask.amount
        bid.amount = bid.amount - ask.amount;
        // # ask is completely gone, so go to next ask
        break;
        }
        if(bid.amount<ask.amount && bid.amount>0)
        {
        // if bid.amount < ask.amount 
        // # bid is completely gone, slice the ask
        // sale.amount = bid.amount
        sale.amount=bid.amount;
        // sales.append(sale)
        sales.push_back(sale);
        // # update the ask
        // # and allow further bids to process the remaining amount
        // ask.amount = ask.amount - bid.amount
        ask.amount = ask.amount - bid.amount;
        // bid.amount = 0 # make sure the bid is not processed again
        bid.amount=0;
        // # some ask remains so go to the next bid
           continue;
        }
            }
        }
    }
    return sales;
}