/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:33:40 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/26 22:43:29 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <list>
# include <deque>
# include <iterator>
# include <algorithm>
# include <sys/time.h>


class PmergeMe
{
    private:
        std::list<int>  perge1;
        std::deque<int> perge2;
        PmergeMe();
        void    fill_containers(char ** s);
        bool    check_double(std::list<int>l1);
        void    merge_sort_list(std::list<int> &lst);
        void    merge_sort_deque(std::deque<int> &lst);
        void    maerge_list(std::list<int> &lst, std::list<int> &left, std::list<int> &right);
        void    maerge_deque(std::deque<int> &lst, std::deque<int> &left, std::deque<int> &right);
    public:
        PmergeMe(char ** s);
        PmergeMe(PmergeMe const & ob);
        ~PmergeMe();
        PmergeMe & operator=(PmergeMe const & ob);
        std::list<int>  getPmergeMe1(void) const;
        std::deque<int> getPmergeMe2(void) const;
        void    star_merg_list(void);
        void    star_merg_deque(void);

        class DoubleNum : public std::exception
        {
            public:
                const char* what(void) const throw();
        };
        class NegativeNum : public std::exception
        {
            public:
                const char* what(void) const throw();
        };
        class MaxNum : public std::exception
        {
            public:
                const char* what(void) const throw();
        };
};

std::ostream & operator<<(std::ostream & o, PmergeMe const &ref);

#   endif