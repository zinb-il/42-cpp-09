/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:37:26 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/21 17:43:06 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac > 2)
        std::cout << "Error: bad arguments." << std::endl;
    else if (ac < 2)
        std::cout << ERR << std::endl;
    else
    {
        try
        {
            BitcoinExchange b(av[1]);
            b.getCurrency();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    return 0;
}