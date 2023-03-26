/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:33:40 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/25 23:45:38 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <iomanip> 
# include <string>
# include <stack>
# include <iterator>
# include <algorithm> 

# define ERR "Error"
# define EXP1 " +-*/0123456789"
# define EXP2 "+-*/"


class RPN
{
    private:
        std::stack<int>          rpn;
        std::string               str;
        RPN();
        void    rpn_algo(void);
    public:
        RPN(std::string s);
        RPN(RPN const & ob);
        ~RPN();
        RPN & operator=(RPN const & ob);
        std::stack<int> getRpn(void) const;
        std::string     getS_Rpn(void) const;
};

#   endif