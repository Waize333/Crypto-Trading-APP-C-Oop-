#pragma once

#include "OrderBookEntry.h"
#include<vector>
#include<iostream>

using namespace std;

class CSVReader
{
    public:
    CSVReader();
    // stateless function , not rely on anything being created before
   static vector<OrderBookEntry>ReadCSV(string csvFile);
    //creating a static tokenise function
   static vector<string>tokenise(string csvLine,char seperator);
   //custom function
   static OrderBookEntry stringsToOBE(string price,
                                    string amount,
                                    string timeStamp,
                                    string product,
                                    orderBookType ordertype);

   private:
  //converting strings to Objects
   static OrderBookEntry stringsToOBE(vector<string>strings);
};
