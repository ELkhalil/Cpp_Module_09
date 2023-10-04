/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:27:45 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/04 13:08:21 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main( int ac, char *av[] )
{
    if (ac != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    std::string input = av[1];
    RPN     rpn(input);
    std::cout << rpn.calculateExpression() << std::endl;
    return 0;
}