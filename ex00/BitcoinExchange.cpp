/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:52:28 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/21 19:15:47 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/********************************************************************/
/*                     Constructors  and Destructor                 */
/********************************************************************/

BitcoinExchange::BitcoinExchange()
{
    std::cout << "BitcoinExchange Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string file):file_in(file), inputfile(new std::ifstream (file, std::ifstream::binary))
{
    if (!inputfile->good())
        throw (BitcoinExchange::ErrFile());
    getDataBase();
    std::cout << "BitcoinExchange Parameter constroctur called" << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & ob)
{
    std::cout << "BitcoinExchange Copy constroctur called" << std::endl;
    *this = ob;
}

BitcoinExchange::~BitcoinExchange()
{
    inputfile->close();
    delete(inputfile);
    std::cout << "BitcoinExchange Destructor called" << std::endl;
}

/********************************************************************/



/********************************************************************/
/*                    Assignment Operator Overload                  */
/********************************************************************/


BitcoinExchange & BitcoinExchange::operator=(BitcoinExchange const & ob)
{
    // std::cout << "BitcoinExchange Copy assignment operator called" << std::endl;
    file_in = ob.getFile();
    inputfile = ob.getInfile();
    btc = ob.getBtc();
    return *this;
}

/********************************************************************/


/********************************************************************/
/*                          Getters functions                       */
/********************************************************************/


std::map<std::string, int> BitcoinExchange::getBtc(void) const
{
    return (this->btc);
}
std::string BitcoinExchange::getFile(void) const
{
    return (this->file_in);
}
std::ifstream * BitcoinExchange::getInfile(void) const
{
    return (this->inputfile);
}

/********************************************************************/


/********************************************************************/
/*                             Exceptions                           */
/********************************************************************/

const char * BitcoinExchange::ErrFile::what() const throw ()
{
    return ERR;
}

/********************************************************************/


/********************************************************************/
/*                          Public functions                        */
/********************************************************************/

bool BitcoinExchange::getValidDate(std::string s)
{
    std::istringstream date(s);
    int m,d,y;
    char dash1, dash2;
    if(date >> y >> dash1 >> m >> dash2 >> d && \
        dash1 == '-' && dash2 == '-' && date.eof())
    {
        if (d <= 0 || d > 31 || m <= 0 && m > 12 || y < 0)
            return false;
        return true;
    }
    std::cout << ERR1 << date << std::endl;
    return false;
}

void BitcoinExchange::getDataBase(void)
{
    std::ifstream *db = new std::ifstream(DATA);
    std::string         str;
    if (!db->good())
        throw (BitcoinExchange::ErrFile());
    std::getline(*db, str);
    while (std::getline(*db, str))
        btc[str.substr(0, str.find(DEL1))] = std::stoi(str.substr(str.find(DEL1) + 1));
}

void BitcoinExchange::getCurrency(void)
{
    std::string         str;
    std::string         date;
    long int            num;
    
    std::getline(*inputfile, str);
    while (std::getline(*inputfile, str))
    {
        date = str.substr(0, str.find(DEL2));
        num = std::stoi(str.substr(str.find(DEL2) + 3));
        if (!getValidDate(date) || num < 1 || num > 10000)
        {
            std::cout << ERR1 << date << std::endl;
        }
    }
}


/********************************************************************/

