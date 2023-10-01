/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:59:45 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/01 13:44:40 by aelkhali         ###   ########.fr       */
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

    
    return 0;
} 