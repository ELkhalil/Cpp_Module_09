/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:30:19 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/04 10:45:19 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*  BitcoinExchange */
BitcoinExchange::BitcoinExchange    ( void ) {}

BitcoinExchange::BitcoinExchange    ( std::string const& inputFilename, std::string const& pathTodata ) : _inputFile(inputFilename), _dataFilePath(pathTodata) 
{
    _setupBitcoinPricesData();
}
BitcoinExchange::~BitcoinExchange   ( void ) {}
BitcoinExchange::BitcoinExchange    (BitcoinExchange const& other)
{
    *this = other;
}

/*  BitcoinExchange Operators   */
BitcoinExchange&    BitcoinExchange::operator=( BitcoinExchange const& other )
{
    if (this != &other)
    {
        _inputFile = other._inputFile;
        _dataFilePath = other._dataFilePath;
        _BitcoinPrices = other._BitcoinPrices;
    }
    return *this;
}

/*  Reading The File That Contains Data*/
void    BitcoinExchange::_setupBitcoinPricesData( void )
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
double  BitcoinExchange::_stringToDouble( std::string const& input)
{
    if (input.empty() || input.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
        _displayError("_stringToDouble(): invalid input");

    std::istringstream iss(input);
    long double value = 0.0;
    iss >> value;

    if (iss.fail() || !iss.eof())
        _displayError("_stringToDouble(): failed converting the price");
    
    if (value > std::numeric_limits<double>::max() || value < -std::numeric_limits<double>::max())
        _displayError("_stringToDouble(): Overflow/Underflow during double conversion");
    return static_cast<double>(value);;
}
void    BitcoinExchange::dispBitcoinPricesData( void )
{
    if (_BitcoinPrices.empty())
        return ;
    std::map<std::string, double>::iterator it = _BitcoinPrices.begin();
    for (; it != _BitcoinPrices.end(); it++)
    {
        std::cout << "Date: " << it->first;
        std::cout << std::fixed << std::setprecision(2)
        << " | " << "Price= " << it->second << std::endl;
    }
}

/*  Input File  */
void    BitcoinExchange::executeInputFileData( void )
{
    if (_inputFile.empty())
        _displayError("could not open file.");

    std::ifstream   inputFile(_inputFile.c_str());
 
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
        if (line.empty() || line[0] == ' ' || line[0] == '\t')
        {
            std::cerr << "Error: empty line" << std::endl;
            continue;
        }
        _parseLine(line);
    }
    inputFile.close();
}
void    BitcoinExchange::_parseLine( std::string const& line)
{
    if (line.empty())
        _displayError("empty line in the input file.");

    std::istringstream  ss(line);
    std::string date;
    std::string delim;
    std::string value;
    std::string nothing;

    ss >> date >> delim >> value >> nothing;

    /*  Extracting the value if any */
    std::istringstream iss(value);
    double numValue;
    iss >> numValue;

    /*  parse date */
    if (!nothing.empty())
        std::cerr << "Error: bad input line => " << value << std::endl;
    else if (date.empty() || !_isValidDateFormat(date))
        std::cerr << "Error: bad input => " << date << std::endl;
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
        _calculateAndDisplayBtcPrice(date, numValue);
}
bool    BitcoinExchange::_isValidDateFormat( std::string const& date)
{
    std::istringstream  iss(date);

    int year;
    int month;
    int day;
    char tmp;
    char tmp2;

    iss >> year >> tmp >> month >> tmp2 >> day;
    
    if (iss.fail() || !iss.eof())
        return false;
    else if (tmp != '-' || tmp2 != '-')
        return false;
    else if (year < 0 || year > 2023 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    return true;
}
void    BitcoinExchange::_calculateAndDisplayBtcPrice( std::string const& date, double value)
{
    std::map<std::string, double>::iterator it = _BitcoinPrices.lower_bound(date);

    if (it == _BitcoinPrices.begin() || (it != _BitcoinPrices.end() && it->first != date))
    {
        if (it == _BitcoinPrices.begin())
            std::cerr << "Error: too old date => " << date << std::endl;
        else
        {
            --it;
            std::cout << date << " => " << value << " = " << (it->second * value) << std::endl;
        }
    }
    else if (it == _BitcoinPrices.end())
    {
        it--;
        std::cout << date << " => " << value << " = " << (it->second * value) << std::endl;
    }
    else
        std::cout << date << " => " << value << " = " << (it->second * value) << std::endl;
}

/*  Error Display + Exit the program    */
void    BitcoinExchange::_displayError(std::string error)
{
    if (!error.empty())
        std::cerr << "Error: " << error << std::endl;
    _exit(1);
}

