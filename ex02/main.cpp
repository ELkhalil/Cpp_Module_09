/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:28:20 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/04 14:34:19 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
    if (ac != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    std::string input = av[1];
    PmergeMe    mereMe(input);
    
    return 0;
}