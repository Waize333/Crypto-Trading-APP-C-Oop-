#include"WaizMain.h"
#include "OrderBookEntry.h"
#include"CSVReader.h"
#include"OrderBook.h"

WaizMain::WaizMain(){}

void WaizMain::init()
{
 
    int input;
    currentTime=orderBook.getEarliestTime();
    while(true){
        printMenu();
        input=getUserOption();
        processUserOption(input);
    }

}


void WaizMain::printMenu(){
    cout<<"1: Print help"<<endl;
    cout<<"2: Print Exchange Stats"<<endl;
    cout<<"3: Make an offer"<<endl;
    cout<<"4: Make a Bid"<<endl;
    cout<<"5: Print Wallet"<<endl;
    cout<<"6: Continue"<<endl;
    cout<<"==================="<<endl;
    cout<<"THe Current Time is:"<<currentTime<<endl;
       
}
int WaizMain::getUserOption(){
    cout<<"Select an Option Between 1 To 6"<<endl;
    int userOption;
    cin>>userOption;
    cout<<"Your Choice: "<<userOption<<endl;
    return userOption;
}
void WaizMain::printHelp(){
cout<<"Help - Make Money by analysing the market,Make bids and Offers "<<endl;
}
void WaizMain::printMarketStats(){

    for(auto const& p:orderBook.getKnownProducts())
    {
        cout<<"Products : "<<p<<endl;
        vector<OrderBookEntry>entries=orderBook.getOrders(orderBookType::ask,p,"2020/03/17 17:01:30.099017");
        cout<<"Asks Seens Are: "<<entries.size()<<endl;
        cout<<"Max Ask: "<<OrderBook::getHighPrice(entries)<<endl;
        cout<<"Min Ask: "<<OrderBook::getMinPrice(entries)<<endl;

    }
//  cout<<"Orderbook Contains:"<<orders.size()<<" :enteries"<<endl;
//  unsigned int bids = 0;
//  unsigned int asks =0;
//  for(OrderBookEntry&e : orders)
//  {
//     if(e.ordertype==orderBookType::ask)
//     {
//         asks ++;
//     }
//     if(e.ordertype==orderBookType::bid)
//     {
//         bids ++;
//     }
//  }
// cout<<"OrdersBook Asks"<<asks<<endl<<"OrderBook bids"<<bids<<endl;
}
void WaizMain::enterOffer(){
    cout<<"Make an Offer"<<endl;
    }
void WaizMain::enterBid(){
     cout<<"Make a Bid"<<endl;

}
void WaizMain::pritWallet(){
    cout<<"Your Wallet:"<<endl;
}
void WaizMain::nextTimeFrame(){
     cout<<"Going to next step"<<endl;
}
void WaizMain::processUserOption(int userOption ){
    if (userOption==0) {
        cout<<"Invalid Choice ,Choose between 1 to 6"<<endl;
    }
    if (userOption==1) {
        printHelp();
    }
    if (userOption==2) {
       printMarketStats();
    }
    if (userOption==3) {
        enterOffer();
    }
    if (userOption==4) {
       enterBid();
    }
    if (userOption==5) {
        pritWallet();
    }   
    if (userOption==6) {
       nextTimeFrame();
    }
}
