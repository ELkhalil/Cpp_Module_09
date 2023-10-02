/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:59:45 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/02 11:31:58 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void    displayError(std::string error)
{
    if (error.empty())
        return ;
    std::cerr << "Error: " << error << std::endl;
}

int main( int ac, char *av[] )
{
    if (ac != 2)
        return displayError("could not open file."), 1;
    
    std::string pathToInput = av[1];
    std::string pathToCsvData = "data.csv";
    
    BitcoinExchange btc(pathToInput, pathToCsvData);

    /*  Check ane verify CSV data */
    // btc.dispBitcoinPricesData();

    btc.executeInputFileData();
    return 0;
} 