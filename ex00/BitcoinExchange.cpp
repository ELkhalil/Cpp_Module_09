/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:30:19 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/01 21:49:52 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*  BitcoinExchange */
BitcoinExchange::BitcoinExchange    ( void ) {}

BitcoinExchange::BitcoinExchange    ( std::string const& inputFilename, std::string const& pathTodata ) : _inputFile(inputFilename), _dataFilePath(pathTodata) 
{
    _setupBitcoinPricesData();
    _setupInputFileData();
    
}

BitcoinExchange::~BitcoinExchange   ( void ) {}
BitcoinExchange::BitcoinExchange    (BitcoinExchange const& other) {}

/*  BitcoinExchange Operators   */
BitcoinExchange&    BitcoinExchange::operator=( BitcoinExchange const& other )
{
    
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
    long double value;
    iss >> value;

    if (iss.fail() || !iss.eof())
        _displayError("_stringToDouble(): failed converting the price");
    
    if (value > std::numeric_limits<double>::max() || value < std::numeric_limits<double>::lowest())
        _displayError("_stringToDouble(): Overflow/Underflow during double conversion");
    double result = static_cast<double>(value);
    return value;
}
void    BitcoinExchange::_dispBitcoinPricesData( void )
{
    if (_BitcoinPrices.empty())
        return ;
    std::map<std::string, double>::iterator it = _BitcoinPrices.begin();
    for (it ; it != _BitcoinPrices.end(); it++)
    {
        std::cout << "Date: " << it->first;
        std::cout << std::fixed << std::setprecision(1)
        << " | " << "Price= " << it->second << std::endl;
    }
}

/*  Input File  */
void    BitcoinExchange::_setupInputFileData( void )
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

    ss >> date >> delim >> value;

    /*  parse date */
    if (date.empty() || !_isValidDateFormat(date))
        std::cerr << "Error: bad input => " << date << std::endl;
    
    /*  parse delimiter */
    if (delim.empty() || delim != "|")
        std::cerr << "Error: bad delimiter => " << delim << std::endl;

    /*  parse value */
    if (value.empty())
        std::cerr << "Error: empty Value" << std::endl;
    
    std::istringstream iss(value);
    int numValue;
    iss >> numValue;

    if (iss.fail() || !iss.eof())
        std::cerr << "Error: bad characters => " << value << std::endl;
    if (numValue > 1000)
        std::cerr << "Error: too large a number." << std::endl;
    if (numValue < 0 )
        std::cerr << "Error: not a positive number." << std::endl;
}

int     BitcoinExchange::_stringToInt( std::string const& value )
{
    
}

/*  Ceck if date have valid digits  */
bool    BitcoinExchange::_isValidDateFormat( std::string const& date)
{
    if (date.empty() || date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    int year, month, day;
    if (sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3)
        return false;
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;
    return true;
}

/*  Error Display + Exit the program    */
void    BitcoinExchange::_displayError(std::string error)
{
    if (!error.empty())
        std::cerr << "Error: " << error << std::endl;
    _exit(1);
}

