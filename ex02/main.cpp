/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:37:26 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/26 22:45:44 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
   struct timeval start, end, start1, end1;
    
    if (ac <= 2)
        std::cout << "Error: bad arguments." << std::endl;
    else
    {
        try
        {
            PmergeMe p(av + 1);
            std::cout << "Before : " << p << std::endl;
            gettimeofday(&start, NULL);
            p.star_merg_list();
            gettimeofday(&end, NULL);
            gettimeofday(&start1, NULL);
            p.star_merg_list();
            gettimeofday(&end1, NULL);
            std::cout << "After : " << p << std::endl;
            std::cout << "Time to process a range of " << p.getPmergeMe1().size() << " elements with std::list : " <<
            (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec) << " us" << std::endl;
            std::cout << "Time to process a range of " << p.getPmergeMe2().size() << " elements with std::deque : " <<
            (end1.tv_sec - start1.tv_sec) * 1000000.0 + (end1.tv_usec - start1.tv_usec) << " us" << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    return 0;
}