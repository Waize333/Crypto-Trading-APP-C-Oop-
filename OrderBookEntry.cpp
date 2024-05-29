#include "OrderBookEntry.h"



OrderBookEntry::OrderBookEntry(double price,
                               double amount,
                               string timeStamp,
                               string product,
                               orderBookType ordertype,
                               string username)
    : price(price),
      amount(amount),
      timeStamp(timeStamp),
      product(product),
      ordertype(ordertype),
      username(username)
      
{
    
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
 

