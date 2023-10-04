/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhali <aelkhali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:28:08 by aelkhali          #+#    #+#             */
/*   Updated: 2023/10/04 13:07:19 by aelkhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*  RPN constructors    */
RPN::RPN    ( void ) {}
RPN::~RPN   ( void ) {}
RPN::RPN    ( std::string const& exp ) : _expression(exp) 
{
    if (_expression.empty())
        _error();
    for (size_t i = 0; i < _expression.length(); i++)
    {
        char c = _expression[i];
        if (isdigit(c))
            continue;
        else if (c == ' ' || _isOperator(c))
            continue;
        else
            _error();
    }
}
RPN::RPN    ( RPN const& other)
{
    *this = other;
}

/*  RPN operators */
RPN& RPN::operator= ( RPN const& other )
{
    if (this != &other)
    {
        _expression = other._expression;
        _RPNstack = other._RPNstack;
    }
    return *this;
}

/*  RPN Methods */
int     RPN::calculateExpression( void )
{
    std::istringstream  iss(_expression);
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1 && isdigit(token[0]))
            _RPNstack.push(token[0] - '0');
        else if (token.size() == 1 && _isOperator(token[0]) && _RPNstack.size() >= 2)
        {
            int secondNum = _RPNstack.top();
            _RPNstack.pop();
            int firstNum = _RPNstack.top();
            _RPNstack.pop();
            if (token[0] == '+')
                _RPNstack.push(firstNum + secondNum);
            else if (token[0] == '-')
                _RPNstack.push(firstNum - secondNum);
            else if (token[0] == '*')
                _RPNstack.push(firstNum * secondNum);
            else if (token[0] == '/')
            {
                if (!secondNum)
                    _error();
                _RPNstack.push(firstNum / secondNum);
            }
            else
                _error();
        }
        else
            _error();
    }
    if (!(_RPNstack.size() == 1))
        _error();
    return _RPNstack.top();
}
bool    RPN::_isOperator( char c )
{
    return ( (c == '+') || ( c == '-') || (c == '*') || (c == '/'));
}
void    RPN::_error( void )
{
    std::cout << "Error" << std::endl;
    _exit(1);
}