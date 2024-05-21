#include "CSVReader.h"
#include <fstream>


CSVReader::CSVReader() {
   
}

vector<OrderBookEntry> CSVReader::ReadCSV(string csvFileName) {
    // Read CSV file and return vector of OrderBookEntry objects
    vector<OrderBookEntry> entries;
    
    ifstream csvFile{csvFileName};
	string line;
    if(csvFile.is_open())
    {
		while (getline(csvFile,line))
		{
			try{
		OrderBookEntry obe = stringsToOBE(tokenise(line,','));
		entries.push_back(obe);
		}catch(const exception& e)
		{
			cout<<"CSVReader::readcsv Bad data"<<endl;

		}
		}
		cout<<"CSVReader::readcsv "<<entries.size()<<endl;
    
    }
	
    return entries;
}

vector<string> CSVReader::tokenise(string csvLine, char separator) {
    // Tokenise csvLine using the separator and return vector of tokens
 
    vector<string>tokens;
	signed int start, end;
	string token;
	
	start = csvLine.find_first_not_of(separator, 0);
	do {
		end = csvLine.find_first_of(separator, start);
		if (start == csvLine.length() || start == end)break;
		if (end >= 0)
		{
			token = csvLine.substr(start, end - start);
		}
		else
		{
			token = csvLine.substr(start, csvLine.length() - start);
		}
		tokens.push_back(token);
		start = end + 1;

	} while (end>0);

		return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(vector<string> tokens) {
    // Convert vector of strings to OrderBookEntry object
    double price,amount;
	if (tokens.size() != 5) 
			{
				cout << "Bad Line" << endl;
                throw exception();
			
			}
			try {
				price = stod(tokens[3]);
				amount = stod(tokens[4]);
			}
			catch (const exception& e) {
				cout << "Bad Float" << tokens[3] << endl;
				cout << "Bad Float" << tokens[4] << endl;
                throw;
			}


    
    OrderBookEntry obe{price,
                        amount,
                        tokens[0],
                        tokens[1],
                         OrderBookEntry::stringToOrderbookType(tokens[2])};
    // Implementation here
    return obe;
}
