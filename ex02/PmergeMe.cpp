/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:28:25 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/05 11:20:43 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*  PmergeMe constructor    */
PmergeMe::PmergeMe  ( void ) {}
PmergeMe::PmergeMe    ( std::vector<int> const& input )
{
    if (input.empty())
        _error();
    _inputData = input;
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
        _inputData = other._inputData;
        _sortedVector = other._sortedVector;
        _sortedList = other._sortedList;
    }
    return *this;
}

/*  PmeregeMe Methods   */
void    PmergeMe::_mergeInsertSort(std::vector<int>& intSequence)
{
    
}

void    PmergeMe::sortSequence( void )
{
    
}

void    PmergeMe::_error()
{
    std::cout << "Error" << std::endl;
    _exit(1);
}