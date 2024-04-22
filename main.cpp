#include <iostream>
#include<string>
#include<vector>

using namespace std;

void printMenu(){
    cout<<"1: Print help"<<endl;
    cout<<"2: Print Exchange Stats"<<endl;
    cout<<"3: Make an offer"<<endl;
    cout<<"4: Make a Bid"<<endl;
    cout<<"5: Print Wallet"<<endl;
    cout<<"6: Continue"<<endl;
    cout<<"==================="<<endl;
       
}
int getuserOption(){
    cout<<"Select an Option Between 1 To 6"<<endl;
    int userOption;
    cin>>userOption;
    cout<<"Your Choice: "<<userOption<<endl;
    return userOption;
}
void printHelp(){
cout<<"Help - Make Money by analysing the market,Make bids and Offers "<<endl;
}
void printMarketStats(){
 cout<<"Market Looks Good"<<endl;
}
void enterOffer(){
    cout<<"Make an Offer"<<endl;
    }
void enterBid(){
     cout<<"Make a Bid"<<endl;

}
void pritWallet(){
    cout<<"Your Wallet:"<<endl;
}
void nextTimeFrame(){
     cout<<"Going to next step"<<endl;
}
void processUserOption(int userOption ){
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

int main() {
//making a enum class
enum class OderBookType{bid,ask};
OderBookType ordertype=OderBookType::ask;

    // Making a menu
    while(true){
        printMenu();
        int userOption=getuserOption();
        processUserOption(userOption);
    }
    return 0;
}
