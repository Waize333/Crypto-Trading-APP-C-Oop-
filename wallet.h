#include<iostream>
#include<string>
#include<map>
using namespace std;


class Wallet
{
    public:
        Wallet();
        void insertCurrency(string type,double amount);
        bool containsCurrency(string type,double amount);
        string toString();
    private:
        map<string,double> currency;
};