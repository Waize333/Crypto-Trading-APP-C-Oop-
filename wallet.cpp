#include"wallet.h"
#include"CSVReader.h"

Wallet::Wallet()
{

}
void Wallet::insertCurrency(string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        throw std::exception{};
    }
    if (currencies.count(type) == 0) // not there yet
    {
        balance = 0;
    }
    else { // is there 
        balance = currencies[type];
    }
    balance += amount; 
    currencies[type] = balance; 
}

bool Wallet::removeCurrency(string type, double amount)
{
    if (amount < 0)
    {
        return false; 
    }
    if (currencies.count(type) == 0) // not there yet
    {
        //std::cout << "No currency for " << type << std::endl;
        return false;
    }
    else { // is there - do  we have enough
        if (containsCurrency(type, amount))// we have enough
        {
            //std::cout << "Removing " << type << ": " << amount << std::endl;
            currencies[type] -= amount;
            return true;
        } 
        else // they have it but not enough.
            return false; 
    }
}

bool Wallet::containsCurrency(string type, double amount)
{
    if (currencies.count(type) == 0) // not there yet
        return false;
    else 
        return currencies[type] >= amount;
    
}

string Wallet::toString()
{
    string s;
    for (pair<string,double> pair : currencies)
    {
        string currency = pair.first;
        double amount = pair.second;
        s += currency + " : " + to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::canFulfilOrder(OrderBookEntry order)
{
   vector<string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    if (order.ordertype == orderBookType::ask)
    {
        double amount = order.amount;
        string currency = currs[0];
        cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;

        return containsCurrency(currency, amount);
    }
    // bid
    if (order.ordertype == orderBookType::bid)
    {
        double amount = order.amount * order.price;
        string currency = currs[1];
        cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return containsCurrency(currency, amount);
    }


    return false; 
}
      

void Wallet::processSale(OrderBookEntry& sale)
{
    vector<string> currs = CSVReader::tokenise(sale.product, '/');
    // ask
    if (sale.ordertype == orderBookType::askSale)
    {
        double outgoingAmount = sale.amount;
        string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;

    }
    // bid
    if (sale.ordertype == orderBookType::bidSale)
    {
        double incomingAmount = sale.amount;
        string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}
ostream& operator<<(ostream& os,  Wallet& wallet)
{
    os << wallet.toString();
    return os;
}
