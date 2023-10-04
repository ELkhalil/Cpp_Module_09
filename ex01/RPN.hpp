/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:28:06 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/04 11:53:04 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <unistd.h>
#include <sstream>
#include <string>

class   RPN
{
public:
    RPN     ( std::string const& );
    RPN     ( RPN const& );
    ~RPN    ( void );
    RPN&    operator=( RPN const& );

    int     calculateExpression( void );
private:
    RPN                 ( void );
    std::string         _expression;
    std::stack<int>     _RPNstack;
    void                _error( void );
    bool                _isOperator( char c );
};

#endif