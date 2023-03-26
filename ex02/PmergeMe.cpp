/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:52:28 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/25 15:36:46 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/********************************************************************/
/*                     Constructors  and Destructor                 */
/********************************************************************/

PmergeMe::PmergeMe()
{
    //std::cout << "PmergeMe Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(char ** s)
{
    //std::cout << "PmergeMe Parameter constroctur called" << std::endl;
    fill_containers(s);

}

PmergeMe::PmergeMe(PmergeMe const & ob)
{
    //std::cout << "PmergeMe Copy constroctur called" << std::endl;
    *this = ob;
}

PmergeMe::~PmergeMe()
{
    //std::cout << "PmergeMe Destructor called" << std::endl;
}

/********************************************************************/



/********************************************************************/
/*                    Assignment Operator Overload                  */
/********************************************************************/


PmergeMe & PmergeMe::operator=(PmergeMe const & ob)
{
    //std::cout << "PmergeMe Copy assignment operator called" << std::endl;
    perge1 = ob.getPmergeMe1();
    perge2 = ob.getPmergeMe2();
    return *this;
}

/********************************************************************/




/********************************************************************/
/*                          Getters functions                       */
/********************************************************************/


std::list<int>  PmergeMe::getPmergeMe1(void) const
{
    return perge1;
}
std::deque<int>  PmergeMe::getPmergeMe2(void) const
{
    return perge2;
}

/********************************************************************/



/********************************************************************/
/*                              Functions                           */
/********************************************************************/

bool    PmergeMe::check_double(std::list<int>l1)
{
    std::list<int> lst;
    lst.assign(l1.begin(), l1.end());
    lst.sort();
    std::list<int>::iterator it = std::adjacent_find(lst.begin(), lst.end());
    return(lst.end() == it);
}

void    PmergeMe::fill_containers(char  **s)
{
    int i = 0;
    long double n;

    while(s && s[i])
    {
        n = std::stod(s[i]);
        if (n > std::numeric_limits<int>::max())
            throw(PmergeMe::MaxNum());
        else if (n < 0)
            throw(PmergeMe::NegativeNum());
        perge1.push_back(static_cast<int>(n));
        perge2.push_back(static_cast<int>(n));
        i++;
    }
    if(!check_double(perge1))
        throw(PmergeMe::DoubleNum());
}



void    PmergeMe::maerge_list(std::list<int> &lst, std::list<int> &left, std::list<int> &right)
{

    while (!left.empty() && !right.empty()) {
		if (left.front() <= right.front()) {
			lst.push_back(left.front());
			left.pop_front();
		}
		else {
			lst.push_back(right.front());
			right.pop_front();
		}
	}

	while (!left.empty()) {
		lst.push_back(left.front());
		left.pop_front();
	}

	while (!right.empty()) {
		lst.push_back(right.front());
		right.pop_front();
	}
}

void    PmergeMe::merge_sort_list(std::list<int> &lst)
{
    if (lst.size() == 1)
        return ;
    std::list<int> left, right;

    for (size_t i = 0; i < lst.size() / 2; i++)
    {
        left.push_back(lst.front());
        lst.pop_front();
    }
    while (!lst.empty())
    {
       right.push_back(lst.front());
       lst.pop_front();
    }
    merge_sort_list(left);
    merge_sort_list(right);
    maerge_list(lst, left, right);
}

void    PmergeMe::star_merg_list(void)
{
    this->merge_sort_list(this->perge1);
}


void    PmergeMe::maerge_deque(std::deque<int> &lst, std::deque<int> &left, std::deque<int> &right)
{

    while (!left.empty() && !right.empty()) {
		if (left.front() <= right.front()) {
			lst.push_back(left.front());
			left.pop_front();
		}
		else {
			lst.push_back(right.front());
			right.pop_front();
		}
	}

	while (!left.empty()) {
		lst.push_back(left.front());
		left.pop_front();
	}

	while (!right.empty()) {
		lst.push_back(right.front());
		right.pop_front();
	}
}

void    PmergeMe::merge_sort_deque(std::deque<int> &lst)
{
    if (lst.size() == 1)
        return ;
    std::deque<int> left, right;

    for (size_t i = 0; i < lst.size() / 2; i++)
    {
        left.push_back(lst.front());
        lst.pop_front();
    }
    while (!lst.empty())
    {
       right.push_back(lst.front());
       lst.pop_front();
    }
    merge_sort_deque(left);
    merge_sort_deque(right);
    maerge_deque(lst, left, right);
}

void    PmergeMe::star_merg_deque(void)
{
    this->merge_sort_deque(this->perge2);
}

/********************************************************************/




/********************************************************************/
/*                             Exceptions                           */
/********************************************************************/

const char* PmergeMe::DoubleNum::what(void) const throw()
{
    return "Error : got duplicate number in your input";
}

const char* PmergeMe::NegativeNum::what(void) const throw()
{
    return "Error : got negative number in your input";
}

const char* PmergeMe::MaxNum::what(void) const throw()
{
    return "Error : number out of limits of Integer numbers";
}

/********************************************************************/

std::ostream & operator<<(std::ostream & o, PmergeMe const &ref)
{
    std::list<int> lst = ref.getPmergeMe1();
    std::list<int>::iterator b = lst.begin();
    std::list<int>::iterator e = lst.end();
    while(b != e)
    {
        std::cout << *b << " ";
        b++;
    }
    return o;
}


