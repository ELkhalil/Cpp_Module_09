/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:28:20 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/29 13:47:43 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <limits>

void    _errorExit( void )
{
    std::cout << "Error" << std::endl;\
    _exit(1);
}

unsigned int     _stringToInt( std::string const& input)
{
    std::istringstream iss(input);
    unsigned long value;

    iss >> value;

    if (iss.fail() || !iss.eof() || value < 0)
        _errorExit();
    if (value > std::numeric_limits<unsigned int>::max() || value < std::numeric_limits<unsigned int>::min())
        _errorExit();
    return static_cast<unsigned int>(value);
}

int main(int ac, char *av[])
{
    if (ac < 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    std::vector<unsigned int>    inputSequence;
    for (int i = 1; i < ac; i++)
    {
        std::string input = av[i];
        inputSequence.push_back(_stringToInt(input));
    }
    PmergeMe    mergeSort(inputSequence);
    mergeSort.execute();
    return 0;
}