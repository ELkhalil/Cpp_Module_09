/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:28:23 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/04 14:49:33 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>

class   PmergeMe
{
public:
    PmergeMe    ( std::string const& );
    PmergeMe    ( PmergeMe const& );
    ~PmergeMe   ( void );

    PmergeMe&   operator=( PmergeMe const& );
    // void        mergeInsertSort ( void );
private:
    PmergeMe    ( void );
    std::string _intInputSequence;
    void        _error();
};

#endif