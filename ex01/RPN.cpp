/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:52:28 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/25 15:36:46 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/********************************************************************/
/*                     Constructors  and Destructor                 */
/********************************************************************/

RPN::RPN()
{
    //std::cout << "RPN Default constructor called" << std::endl;
}

RPN::RPN(std::string s):str(s)
{
    //std::cout << "RPN Parameter constroctur called" << std::endl;
    rpn_algo();
}

RPN::RPN(RPN const & ob)
{
    //std::cout << "RPN Copy constroctur called" << std::endl;
    *this = ob;
}

RPN::~RPN()
{
    //std::cout << "RPN Destructor called" << std::endl;
}

/********************************************************************/



/********************************************************************/
/*                    Assignment Operator Overload                  */
/********************************************************************/


RPN & RPN::operator=(RPN const & ob)
{
    //std::cout << "RPN Copy assignment operator called" << std::endl;
    rpn = ob.getRpn();
    str = ob.getS_Rpn();
    return *this;
}

/********************************************************************/




/********************************************************************/
/*                          Getters functions                       */
/********************************************************************/


std::stack<long int> RPN::getRpn(void) const
{
    return this->rpn;
}
std::string RPN::getS_Rpn(void) const
{
    return this->str;
}

/********************************************************************/



/********************************************************************/
/*                              Functions                           */
/********************************************************************/

void    RPN::rpn_method(std::stack<long int> &r, char c)
{
    long int n1, n2;
    if (r.empty())
        return ;
    n1 = rpn.top();
    rpn.pop();
    if (r.empty())
        return ;
    n2 = rpn.top();
    rpn.pop();
    switch (c)
    {
        case '+':
            rpn.push(n1 + n2);
            break;
        case '*':
            rpn.push(n1 * n2);
            break;
        case '/':
            rpn.push(n2 / n1);
            break;
        default:
            rpn.push(n2  - n1);
            break;
    }
}


void    RPN::rpn_algo(void)
{
    if (!str.size())
    {
        std::cout << "Error : your formula is empty" << std::endl;
        return ;
    }
    for (std::string::size_type i = 0; i < str.size(); i++)
    {
        if (std::string(EXP1).find(str[i]) == std::string::npos)
        {
            std::cout << ERR << std::endl;
            return ;
        }
        else if (str[i] == ' ')
            continue;
        else if(std::string(EXP2).find(str[i]) == std::string::npos)
            rpn.push(str[i] - 48);
        else
            RPN::rpn_method(rpn, str[i]);

    }
    if (rpn.empty())
        std::cout << "Error : invalid formula" << std::endl;
    else
        std::cout << rpn.top() << std::endl;
    
}

/********************************************************************/




/********************************************************************/
/*                             Exceptions                           */
/********************************************************************/


/********************************************************************/



