/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:28:25 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/04 14:50:58 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*  PmergeMe constructor    */
PmergeMe::PmergeMe  ( void ) {}
PmergeMe::PmergeMe  ( std::string const& input )
{
    if (input.empty())
        _error();
    for (size_t i = 0; i < input.size(); i++)
    {
        if (isdigit(input[i]) || input[i] == ' ')
            continue;
        else
            _error();
    }
    _intInputSequence = input;
    std::vector<int> test;
    if (_intInputSequence.empty())
        return ;
    std::istringstream  iss(_intInputSequence);
    int                 token;
    while (iss >> token)
        test.push_back(token);
    if (!test.size())
        _error();
}
PmergeMe::~PmergeMe ( void ) {}
PmergeMe::PmergeMe  ( PmergeMe const& other )
{
    *this = other;
}

/*  PmergeMe operators */
PmergeMe&   PmergeMe::operator=( PmergeMe const& other )
{
    if (this != &other)
    {
        /* deep copy */
    }
    return *this;
}

/*  PmeregeMe Methods   */
// void    PmergeMe::mergeInsertSort ( void )
// {
//     std::vector<int> test;
//     if (_intInputSequence.empty())
//         return ;
//     std::istringstream  iss(_intSequence);
//     int                 token;
//     while (iss >> token)
//         test.push_back(token);
//     if (!test.size())
//         _error();
// }

void    PmergeMe::_error()
{
    std::cout << "Error" << std::endl;
    _exit(1);
}