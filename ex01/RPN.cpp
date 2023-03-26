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


std::stack<int> RPN::getRpn(void) const
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

void    RPN::rpn_algo(void)
{
    long int n1, n2;

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
        {
            n1 = rpn.top();
            rpn.pop();
            n2 = rpn.top();
            rpn.pop();
            switch (str[i])
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

    }
    std::cout << rpn.top() << std::endl;
    
}

/********************************************************************/




/********************************************************************/
/*                             Exceptions                           */
/********************************************************************/


/********************************************************************/



