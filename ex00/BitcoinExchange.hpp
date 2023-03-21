/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:33:40 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/21 19:08:20 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#   ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <iterator>
# include <algorithm> 

# define ERR "Error: could not open file."
# define ERR1 "Error: bad input => "
# define ERR2 "Error: too large a number."
# define DATA "data.csv"
# define DEL1 ","
# define DEL2 " | "

class BitcoinExchange
{
    private:
        std::map<std::string, int> btc;
        std::string file_in;
        std::ifstream *inputfile;
        void getDataBase(void);
        bool getValidDate(std::string s);
        BitcoinExchange();
    public:
        BitcoinExchange(std::string file);
        BitcoinExchange(BitcoinExchange const & ob);
        ~BitcoinExchange();
        BitcoinExchange & operator=(BitcoinExchange const & ob);
        std::map<std::string, int> getBtc(void) const;
        std::string getFile(void) const;
        std::ifstream * getInfile(void) const;
        void    getCurrency(void);
        
        class ErrFile : public std::exception
        {
            public:
                const char* what(void) const throw();
        };
        
        
};

#   endif