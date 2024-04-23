#include "OrderBookEntry.h"



OrderBookEntry::OrderBookEntry(double price,
                               double amount,
                               string timeStamp,
                               string product,
                               orderBookType ordertype)
    : price(price),
      amount(amount),
      timeStamp(timeStamp),
      product(product),
      ordertype(ordertype) // Colon indicates initialization of member variables
{
    // Constructor body
}
