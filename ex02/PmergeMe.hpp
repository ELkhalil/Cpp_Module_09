/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:28:23 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/05 11:53:27 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <list>
#include <time.h>

class   PmergeMe
{
public:
    PmergeMe    ( std::vector<unsigned int> const& );
    PmergeMe    ( PmergeMe const& );
    ~PmergeMe   ( void );

    PmergeMe&   operator=( PmergeMe const& );    
    void        execute( void );

private:
    PmergeMe            ( void );
    /*  Private Attributes  */
    std::vector<unsigned int>    _inputData;
    std::vector<unsigned int>    _sortedVector;
    std::list<unsigned int>      _sortedList;

    /*  Private Methods */
    void    _error();
    void    _mergeInsertSort(std::vector<unsigned int>& );

    /*  Merge Insertion Sort For vector */
    void    _executeVectorSort( void );
    void    _executeListSort( void );


    /*  Template Function to Print Container Data    */
    template <typename  T>
    void        _printContainerData( T& container )
    {
        int i = 0;
        typename T::iterator it = container.begin();
        for(; it != container.end(); it++)
        {
            std::cout << *it << " ";
            i++;
            if (i >= 8)
            {
                std::cout << "[...]";
                break;
            }
        }
        std::cout << std::endl;
    }
};

#endif