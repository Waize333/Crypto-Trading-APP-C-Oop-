#include"WaizMain.h"
#include "OrderBookEntry.h"
#include"CSVReader.h"
#include"OrderBook.h"
#include<limits>

WaizMain::WaizMain(){}

void WaizMain::init()
{
 
    int input;
    currentTime=orderBook.getEarliestTime();
    wallet.insertCurrency("USDT",10000);
    
    while(true){
        printMenu();
        input=getUserOption();
        processUserOption(input);
    }

}


void WaizMain::printMenu() {
    cout << "====================================" << endl;
    cout << "|          Trading Platform        |" << endl;
    cout << "====================================" << endl;
    cout << "| 1: Print Help                    |" << endl;
    cout << "| 2: Print Exchange Stats          |" << endl;
    cout << "| 3: Make an Ask                   |" << endl;
    cout << "| 4: Make a Bid                    |" << endl;
    cout << "| 5: Print Wallet                  |" << endl;
    cout << "| 6: Continue                      |" << endl;
    cout << "====================================" << endl;
    cout << "| Current Time: " <<currentTime<<" |" << endl;
    cout << "====================================" << endl;
}


void WaizMain::printHelp() {
     cout <<"                                                  " << endl;
    cout << "==================================================" << endl;
    cout << "|                   Trading Help                 |" << endl;
    cout << "==================================================" << endl;
    cout << "| Help - Your aim is to make money by analyzing  |" << endl;
    cout << "| the market, making bids, and offers.           |" << endl;
    cout << "| Follow the instructions below to navigate      |" << endl;
    cout << "| through the trading platform.                  |" << endl;
    cout << "|                                                |" << endl;
    cout << "| 1. Print Help: Displays trading instructions.  |" << endl;
    cout << "| 2. Print Exchange Stats: Shows market data.    |" << endl;
    cout << "| 3. Make an Ask: Place an ask order.            |" << endl;
    cout << "| 4. Make a Bid: Place a bid order.              |" << endl;
    cout << "| 5. Print Wallet: Displays your current wallet. |" << endl;
    cout << "| 6. Continue: Proceed to the next time frame.   |" << endl;
    cout << "==================================================" << endl;
}

void WaizMain::printMarketStats() {
    cout << "==================================================" << endl;
    cout << "|                 Market Statistics               |" << endl;
    cout << "==================================================" << endl;
    
    for (auto const& p : orderBook.getKnownProducts()) {
        cout << "| Product: " << p << endl;
        
        vector<OrderBookEntry> entries = orderBook.getOrders(orderBookType::ask, p, currentTime);
        cout << "| Asks Seen: " << entries.size() << endl;
        
        if (!entries.empty()) {
            cout << "| Max Ask: " << OrderBook::getHighPrice(entries) << endl;
            cout << "| Min Ask: " << OrderBook::getMinPrice(entries) << endl;
        } else {
            cout << "| No asks available for this product." << endl;
        }
        
        cout << "--------------------------------------------------" << endl;
    }
}

void WaizMain::enterAsk(){
    cout<<" Make an Ask - Enter Product, Price, and Amount: [e.g. BTC/USDT, $200, 0.5]"<<endl;
    string input;
    getline(cin,input);
    vector<string>tokens=CSVReader::tokenise(input,',');
    if(tokens.size()!=3)
    {
        cout<<"Bad Input "<<input<<endl;
    }else
    {
        try{
        OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1],tokens[2],currentTime,
            tokens[0],orderBookType::ask
        );
        obe.username="simUser";
        if(wallet.canFulfilOrder(obe))
        {
            cout<<"Wallet is valid for transaction"<<endl;
            orderBook.insertOrder(obe);
        }else
        {cout<<"Wallet hass insufficient funds"<<endl;}
        }catch(const exception& e)
        {
            cout<<"WaizMain::enterAsk Bad Input"<<endl;
        }
    }
 }
void WaizMain::enterBid(){
      cout << " Place a Bid - Enter Product, Price, and Amount: [e.g. ETH/USDT, $200, 0.5]" << endl;

    string input;
    //The purpose of the function is to clear the input buffer up to the next newline character.
    getline(cin,input);
    vector<string>tokens=CSVReader::tokenise(input,',');
    if(tokens.size()!=3)
    {
        cout<<"Bad Input "<<input<<endl;
    }else
    {
        try{
        OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1],tokens[2],currentTime,
            tokens[0],orderBookType::bid
        );
       obe.username="simUser";
        if(wallet.canFulfilOrder(obe))
        {
            cout<<"Wallet is valid for Transaction"<<endl;
            orderBook.insertOrder(obe);
        }else
        {cout<<"Wallet hass insufficient funds"<<endl;}
        }catch(const exception& e)
        {
            cout<<"WaizMain::enterBid Bad Input"<<endl;
        }
    }
}

void WaizMain::printWallet()
{
    cout<<wallet.toString()<<endl;
}

void WaizMain::nextTimeFrame(){
    std::cout << "Moving to the Next Timeframe" << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "Matching :  " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale Price: $ " << sale.price << " | Amount: " << sale.amount << std::endl; 
            if (sale.username == "simUser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }

    currentTime = orderBook.getNextTime(currentTime);
}
int WaizMain::getUserOption(){
    cout<<"Select an Option Between 1 To 6"<<endl;
    int userOption=0;
    string line;
    getline(cin,line);
    try{
    userOption=stoi(line);
    }catch(const exception&e)
    {}
    cout<<"Your Choice: "<<userOption<<endl<<endl;
    return userOption;
}

void WaizMain::processUserOption(int userOption ){
    if (userOption<=0||userOption>6) {
        cout<<"Invalid Choice ,Choose between 1 to 6"<<endl;
    }
    if (userOption==1) {
        printHelp();
    }
    if (userOption==2) {
       printMarketStats();
    }
    if (userOption==3) {
        enterAsk();
    }
    if (userOption==4) {
       enterBid();
    }
    if (userOption==5) {
        printWallet();
    }   
    if (userOption==6) {
       nextTimeFrame();
    }
}
