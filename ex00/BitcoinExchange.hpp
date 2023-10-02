/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:29:10 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/02 11:03:10 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <map>
#include <limits>
#include <iomanip>


class   BitcoinExchange
{
public:
    BitcoinExchange     ( std::string const&, std::string const& );
    BitcoinExchange     ( BitcoinExchange const& );
    ~BitcoinExchange    ( void );
    BitcoinExchange&    operator=( BitcoinExchange const& );

    /*  main Exec Method    */    
    void                executeInputFileData( void );

    /*  Public Helper Functions */
    void                dispBitcoinPricesData( void );
private:
    BitcoinExchange ( void );
    std::string                      _inputFile;
    std::string                      _dataFilePath;
    std::map<std::string, double>    _BitcoinPrices;

    /*  Helper Private Functions    */
    void                _setupBitcoinPricesData( void );
    double              _stringToDouble( std::string const& );
    void                _displayError( std::string );
    void                _parseLine( std::string const& );
    bool                _isValidDateFormat( std::string const& date);
    void                _calculateAndDisplayBtcPrice (std::string const&, double );
};

#endif