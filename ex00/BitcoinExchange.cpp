/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:52:28 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/25 15:36:46 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/********************************************************************/
/*                     Constructors  and Destructor                 */
/********************************************************************/

BitcoinExchange::BitcoinExchange()
{
    //std::cout << "BitcoinExchange Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(std::string file):file_in(file), inputfile(new std::ifstream (file, std::ifstream::binary))
{
    if (!inputfile->good())
        throw (BitcoinExchange::ErrFile());
    getDataBase();
    //std::cout << "BitcoinExchange Parameter constroctur called" << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const & ob)
{
    //std::cout << "BitcoinExchange Copy constroctur called" << std::endl;
    *this = ob;
}

BitcoinExchange::~BitcoinExchange()
{
    inputfile->close();
    delete(inputfile);
    //std::cout << "BitcoinExchange Destructor called" << std::endl;
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


std::map<std::string, double> BitcoinExchange::getBtc(void) const
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

bool BitcoinExchange::getValidDate(std::string s, int *dt)
{
    std::smatch         match;
    std::regex          re("^([0-9]{4})-([0-9][0-9])-([0-9][0-9])$");
    int                 daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if(std::regex_match(s, match, re))
    {
        dt[2] = std::stoi(match[3]);
        dt[1] = std::stoi(match[2]);
        dt[0] = std::stoi(match[1]);
        if (dt[1] == 2 && ((!(dt[0] % 4) && dt[0] % 100) || !(dt[0] %400)))
            daysInMonth[1] = 29;
        if (dt[0] > 0 && dt[1] > 0 && dt[1] <= 12 && dt[2] >= 1 && dt[2] <= daysInMonth[dt[1] - 1])
            return true;
    }
    std::cout << ERR1 << s << std::endl;
    return false;
}

long double  BitcoinExchange::getValidNumb(std::string n)
{
    std::istringstream  number(n);
    long double num;
    
    if(!(number >> num) || !number.eof())
    {
        std::cerr << ERR1 << n << std::endl;
        return -1;
    }
    num =  std::stold(n);
    if (num >= 0 && num <= 1000)
        return num;
    else if (num < 0)
        std::cerr << ERR3 << std::endl;
    else
        std::cerr << ERR2 << std::endl;
    return -1;
}

void BitcoinExchange::getDataBase(void)
{
    std::ifstream *db = new std::ifstream(DATA);
    std::string         str;
    if (!db->good())
        throw (BitcoinExchange::ErrFile());
    std::getline(*db, str);
    while (std::getline(*db, str))
        btc[str.substr(0, str.find(DEL1))] = std::stold(str.substr(str.find(DEL1) + 1));
}

void BitcoinExchange::getNextDate(int *dt, std::string date, long double num)
{
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    std::string day = (std::to_string(dt[2]).length() < 2) ? "0" + std::to_string(dt[2]) : std::to_string(dt[2]);
    std::string month = (std::to_string(dt[1]).length() < 2) ? "0" + std::to_string(dt[1]) : std::to_string(dt[1]);
    std::string d = std::to_string(dt[0]) + "-" + month + "-" + day;
    
    while(btc.find(d) == btc.end())
    {
        if (dt[0] <= 0)
        {
            std::cerr << ERR4 << date << std::endl;
            return ;
        }
        (dt[1] == 2 && ((!(dt[0] % 4) && dt[0] % 100) || !(dt[0] %400))) ? daysInMonth[1] = 29 : daysInMonth[1] = 28;
        if (--dt[2] <= 0)
        {
            if (--dt[1] <= 0)
            {
                dt[1] = 12;
                --dt[0];
                dt[2] = daysInMonth[dt[1] - 1];
            }
        }
        day = (std::to_string(dt[2]).length() < 2) ? "0" + std::to_string(dt[2]) : std::to_string(dt[2]);
        month = (std::to_string(dt[1]).length() < 2) ? "0" + std::to_string(dt[1]) : std::to_string(dt[1]);
        d = std::to_string(dt[0]) + "-" + month + "-" + day;
    }
    std::cout << date << " => " << num << " = " << (num * btc[d]) << std::endl;
}

void BitcoinExchange::getCurrency(void)
{
    std::string         str;
    std::string         date;
    long double         num;
    int                 *dt = new int [3];
    
    std::getline(*inputfile, str);
    if (std::strcmp("date | value", str.c_str()))
    {
        std::cerr << "Error: invalid forme of file." << std::endl;
        return ;
    }
    while (std::getline(*inputfile, str))
    {
        date = str.substr(0, str.find(DEL2));
        if (!getValidDate(date, dt))
            continue;
        num = getValidNumb(str.substr(str.find(DEL2) + 3));
        if ( num < 0)
            continue;
        else
            getNextDate(dt ,date, num);
    }
}


/********************************************************************/

