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

orderBookType OrderBookEntry::stringToOrderbookType(string s)
{
  if(s=="ask")
  {
    return orderBookType::ask;
  }
  if(s=="bid")
  {
    return orderBookType::bid;
  }
  return orderBookType::unknown;

}
 bool OrderBookEntry::compareByTimeStamp(OrderBookEntry& e1,OrderBookEntry& e2)
{
  return e1.timeStamp<e2.timeStamp;
}
