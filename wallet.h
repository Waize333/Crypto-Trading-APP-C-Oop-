
#include<string>
#include<map>
#ifndef WALLET_H
#define WALLET_H
#endif //WALLET_H
using namespace std;

class wallet {
public:
    wallet();
    void insertCurrency(string type, double amount);//insert currency to the wallet
    bool ContainsCurrency (string type, double amount);//check if thewallet contains this much currency or more
    string toString();//generate a string representation

private:
    map<string,double>currencies;//declares a map container

};
