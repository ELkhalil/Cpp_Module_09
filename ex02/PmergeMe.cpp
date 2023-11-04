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
PmergeMe::PmergeMe    ( std::vector<unsigned int> const& input )
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
void    PmergeMe::execute( void )
{
    std::cout << "Before:   ";
    _printContainerData(_inputData);
    std::cout << "After:   ";
    {
        clock_t start, end;
        start = clock();
        _executeVectorSort();
        end = clock();
        _printContainerData(_sortedVector);
        double time_taken = double(end - start);
        std::cout << "Time to process a range of " << _inputData.size() << " elements with std::vector : " 
                  << time_taken << "ms" << std::endl;
    }
}

void    PmergeMe::_executeVectorSort( void )
{
    if (_inputData.size() <= 1)
        return ;
    std::vector<unsigned int> initialData = _inputData;
    int unpaired_element = -1;
    std::vector<unsigned int > X;
    std::vector<unsigned int > S;
    std::pair<unsigned int, unsigned int> tmpPair;

    if (initialData.size() % 2 != 0)
    {
        unpaired_element = initialData.back();
        initialData.pop_back();
    }

    /*  Step 1 && 2 : split data into pairs and compare to swap */
    for (size_t i = 0; i < initialData.size() ; i+=2)
    {
        if (i + 1 <= initialData.size())
        {
            tmpPair = std::make_pair(initialData[i], initialData[i + 1]);
            if (tmpPair.first > tmpPair.second)
                std::swap(tmpPair.first, tmpPair.second);
            X.push_back(tmpPair.first);
            S.push_back(tmpPair.second);
        }
    }

    /* step 3: sort the bigger elements vector */
    std::vector<unsigned int>::iterator it_begin = S.begin();
    std::vector<unsigned int>::iterator it_end = S.end();
    std::sort(it_begin, it_end);

    /* step 4: insert elements from the initial X to the new sequence at it's position */
    for(size_t i = 0; i < X.size(); i++)
    {
        std::vector<unsigned int>::iterator it_pos = std::lower_bound(S.begin(), S.end(), X[i]);
        S.insert(it_pos, X[i]);
    }
    /* step 5: insert the odd element if any */
    if (unpaired_element != -1)
    {
        std::vector<unsigned int>::iterator it_pos = std::lower_bound(S.begin(), S.end(), unpaired_element);
        S.insert(it_pos, unpaired_element);
    }
    _sortedVector = S;
}

// void    PmergeMe::_executeListSort( void )
// {
//     std::list <unsigned int>    initialList;
//     int unpaired_element = -1;
//     std::pair<unsigned int, unsigned int> tmpPair;
//     std::list<unsigned int > X;
//     std::list<unsigned int > S;

//     /* copy data to the list */
//     for (size_t i = 0; i < _inputData.size(); i++)
//         initialList.push_back(_inputData[i]);
//     if (_inputData.size() <= 1)
//     {
//         _sortedList = initialList;
//         return ;
//     }
//     if (_inputData.size() % 2 != 0)
//     {
//         unpaired_element = initialList.back();
//         initialList.pop_back();
//     }
//     {
//         std::list<unsigned int>::iterator it = initialList.begin();
//         std::list<unsigned int>::iterator next_it = it;
//         for(; it != initialList.end(); it++)
//         {
//             next_it++;
//             if (next_it != initialList.end())
//             {
//                 tmpPair = std::make_pair(*it, *next_it);
//                 if (tmpPair.first > tmpPair.second)
//                     std::swap(tmpPair.first, tmpPair.second);
//                 X.push_back(tmpPair.first);
//                 S.push_back(tmpPair.second);
//             }
//         }
//     }

//     std::list<unsigned int>::iterator it_begin = S.begin();
//     std::list<unsigned int>::iterator it_end = S.end();
//     std::sort(it_begin, it_end);

//     {
//         std::list<unsigned int>::iterator it = X.begin();
//         for( ; it != X.end(); it++)
//         {
//             std::list<unsigned int>::iterator it_pos = std::lower_bound(S.begin(), S.end(), *it);
//             S.insert(it_pos, *it);
//         }
//     }

//     if (unpaired_element != -1)
//     {
//         std::list<unsigned int>::iterator it_pos = std::lower_bound(S.begin(), S.end(), unpaired_element);
//         S.insert(it_pos, unpaired_element);
//     }
//     _sortedList = S;
// }

void    PmergeMe::_error()
{
    std::cout << "Error" << std::endl;
    _exit(1);
}