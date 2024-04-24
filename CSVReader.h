#pragma once

#include "OrderBookEntry.h"
#include<vector>

using namespace std;

class CSVReader
{
    public:
    CSVReader();
    // stateless function , not rely on anything being created before
   static vector<OrderBookEntry>ReadCSV(string csvFile);

   private:
   //creating a static tokenise function
   static vector<string>tokenise(string csvLine,char seperator);
   static OrderBookEntry stringsToOBE(vector<string>strings);
};
