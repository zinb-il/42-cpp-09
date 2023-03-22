/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:52:28 by ziloughm          #+#    #+#             */
/*   Updated: 2023/03/22 17:52:31 by ziloughm         ###   ########.fr       */
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

// bool BitcoinExchange::getValidDate(std::string s)
// {
//     std::istringstream  date(s);
//     struct              tm tm;
//     int                 m,d,y;
//     char                dash1, dash2;
    
//     if(date >> y >> dash1 >> m >> dash2 >> d && \
//         dash1 == '-' && dash2 == '-' && date.eof())
//         return true;
//     std::cout << ERR1 << s << std::endl;
//     return false;
// }
int * BitcoinExchange::getValidDate(std::string s)
{
    int                 *dt = new int [3];
    std::smatch         match;
    std::regex          re("^(\\d{4})-(\\d\\d)-(\\d\\d)$");
    int                 daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if(std::regex_match(s, match, re))
    {
        dt[2] = std::stoi(match[3]);
        dt[1] = std::stoi(match[2]);
        dt[0] = std::stoi(match[1]);
        if (dt[1] == 2 && ((!(dt[0] % 4) && dt[0] % 100) || !(dt[0] %400)))
            daysInMonth[1] = 29;
        if (dt[0] > 0 && dt[1] > 0 && dt[1] <= 12 && dt[2] >= 1 && dt[2] <= daysInMonth[dt[1] - 1])
            return dt;
    }
    std::cout << ERR1 << s << std::endl;
    return 0;
}

bool BitcoinExchange::getValidNumb(long double n)
{
    if (n >= 0 && n <= 1000)
        return true;
    else if (n < 0)
        std::cout << ERR3 << std::endl;
    else
        std::cout << ERR2 << std::endl;
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
        btc[str.substr(0, str.find(DEL1))] = std::stold(str.substr(str.find(DEL1) + 1));
}

void BitcoinExchange::getNextDate(int *dt, std::string date, long double num)
{
    std::string day = std::to_string(dt[3]);
    std::string month = std::to_string(dt[1]);

    if (day.length() < 2)
        day = "0" + day;
    if (month.length() < 2)
        month = "0" + day;
    std::string d = day + "-" + month + "-" + std::to_string(dt[3]);
    std::cout <<dt[3]<< "pppp" << d << "    "<< date << std::endl;
    while(!btc[d])
    {
        dt[3]--;
        break;
    }
    std::cout << date << " => " << num << " = " << (num * btc[d]) << std::endl;
}

void BitcoinExchange::getCurrency(void)
{
    std::string         str;
    std::string         date;
    long double         num;
    
    std::getline(*inputfile, str);
    while (std::getline(*inputfile, str))
    {
        date = str.substr(0, str.find(DEL2));
        num = std::stold(str.substr(str.find(DEL2) + 3));
        if (!getValidDate(date) || !getValidNumb(num))
            continue;
        else
            getNextDate(getValidDate(date) ,date, num);
    }
}


/********************************************************************/

