#include"WaizMain.h"
#include "OrderBookEntry.h"




WaizMain::WaizMain(){}

void WaizMain::init()
{
    loadOrderBook();
    int input;
    while(true){
        printMenu();
        input=getUserOption();
        processUserOption(input);
    }

}

void WaizMain::loadOrderBook() {
    orders.push_back(OrderBookEntry(100, 0.02, "2020/03/17 17:01:24.884492", "ETH/BTC", orderBookType::bid));
    orders.push_back(OrderBookEntry(500, 0.02, "2020/04/17 17:01:24.88492", "USDT/BTC", orderBookType::bid));
}

void WaizMain::printMenu(){
    cout<<"1: Print help"<<endl;
    cout<<"2: Print Exchange Stats"<<endl;
    cout<<"3: Make an offer"<<endl;
    cout<<"4: Make a Bid"<<endl;
    cout<<"5: Print Wallet"<<endl;
    cout<<"6: Continue"<<endl;
    cout<<"==================="<<endl;
       
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
 cout<<"Orderbook Contains:"<<orders.size()<<" :enteries"<<endl;
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
