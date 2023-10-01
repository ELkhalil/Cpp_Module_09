#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <map>
#include <limits>
#include <iomanip>

    std::map<std::string, double>    _BitcoinPrices;
    std::string const& _dataFilePath = "testData.csv";

void    _displayError(std::string error)
{
    if (!error.empty())
        std::cerr << "Error: " << error << std::endl;
    _exit(1);
}
double  _stringToDouble( std::string const& input)
{
    if (input.empty() || input.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
        _displayError("_stringToDouble(): invalid input");

    std::istringstream iss(input);
    long double value;
    iss >> value;

    if (iss.fail() || !iss.eof())
        _displayError("_stringToDouble(): failed converting the price");
    
    if (value > std::numeric_limits<double>::max() || value < std::numeric_limits<double>::lowest())
        _displayError("_stringToDouble(): Overflow/Underflow during double conversion");
    double result = static_cast<double>(value);
    return value;
}
void    _setupBitcoinPricesData( void )
{
    if (_dataFilePath.empty())
        _displayError("empty path to (csv) data file.");

    std::ifstream   dataFile(_dataFilePath.c_str());
    if (!dataFile.is_open())
        _displayError("couldn't open (csv) data file.");
    bool is_empty = dataFile.peek() == std::ifstream::traits_type::eof();
    if (is_empty)
        _displayError("empty (csv) data file.");

    /*  Reading Data From data.csv */
    std::string line;
    std::string date;
    std::string price;
    double dprice;
    // init first line
    std::getline(dataFile, line);
    if (line != "date,exchange_rate")
        _displayError("invalid info line in (csv) data file.");
    while(std::getline(dataFile, line))
    {
        std::istringstream  ss(line);
        std::getline(ss, date, ',');
        std::getline(ss, price, ',');
        if (date.empty() || price.empty())
            _displayError("invalid line in (csv) data file.");
        dprice = _stringToDouble(price);
        _BitcoinPrices[date] = dprice;
    }
    if (_BitcoinPrices.empty())
        _displayError("invalid (csv) data file.");
    dataFile.close();
}


bool _isValidDateFormat(std::string const& date) {
    if (date.empty() || date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    
    int year, month, day;
    if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3) {
        return false;
    }

    // Detailed date validation
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    // Check for valid days in each month
    static const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > daysInMonth[month]) {
        return false;
    }

    return true;
}


double _calculateBtcPrice(std::string date, double price) {
    // Search for the closest past date in the map
    std::map<std::string, double>::iterator it = _BitcoinPrices.lower_bound(date);

    // If the iterator points to the beginning, it means there's no past date in the map
    if (it == _BitcoinPrices.begin()) {
        // Handle the case when there's no past date
        std::cerr << "Warning: No past date found in the database. Using the oldest available date." << std::endl;
        return price * _BitcoinPrices.begin()->second; // Use the earliest date's Bitcoin value
    }

    // Decrement the iterator to get the closest past date
    --it;

    // Calculate the price using the closest past date's Bitcoin value
    float calculatedPrice = price * it->second;

    // Format and print the result
    std::cout << it->first << " => " << price << " = " << calculatedPrice << std::endl;

    return calculatedPrice;
}

void    _parseLine( std::string const& line)
{
    if (line.empty())
        _displayError("empty line in the input file.");

    std::istringstream  ss(line);
    std::string date;
    std::string delim;
    std::string value;

    ss >> date >> delim >> value;

    /*  Extracting the value if any */
    std::istringstream iss(value);
    double numValue;
    iss >> numValue;

    /*  parse date */
    if (date.empty() || !_isValidDateFormat(date))
        std::cerr << "Error: bad date => " << date << std::endl;
    
    /*  parse delimiter */
    else if (delim.empty() || delim != "|")
        std::cerr << "Error: bad delimiter => " << delim << std::endl;

    /*  parse value */
    else if (value.empty())
        std::cerr << "Error: empty Value" << std::endl;
    else if (iss.fail() || !iss.eof())
        std::cerr << "Error: bad characters => " << value << std::endl;
    else if (numValue > 1000)
        std::cerr << "Error: too large a number." << std::endl;
    else if (numValue < 0 )
        std::cerr << "Error: not a positive number." << std::endl;
    else
    {
        _calculateBtcPrice(date, numValue);
    }
}

int main( void )
{
    bool    parsed = false;
    _setupBitcoinPricesData();
    if (_BitcoinPrices.empty())
        return 1;
    std::string path = "input.txt";

    std::ifstream   inputFile(path.c_str());
 
    if (!inputFile.is_open())
        _displayError("could not open file.");
    bool is_empty = inputFile.peek() == std::ifstream::traits_type::eof();
    if (is_empty)
        _displayError("empty input file.");

    /*  Parsing Input File Data */
    std::string line;
    std::getline(inputFile, line);
    if (line != "date | value")
        _displayError("invalid info line in input file.");
    while (std::getline(inputFile, line))
    {
        parsed = true;
        if (line.empty())
            _displayError("empty line.");
        _parseLine(line);
    }
    if (!parsed)
        _displayError("incomplete file content.");
    inputFile.close();
}