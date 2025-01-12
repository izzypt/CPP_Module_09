#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <deque>
#include <string>
#include <sstream>
#include <stdexcept>


#define DATABASE "data.csv"

class	WrongNumberOfArguments : public std::exception{
	public:
		virtual const char* what() const throw();
};

class BitcoinExchange
{
    private:
        std::deque<std::deque<double> > _Database;
        std::deque<double>              _InputValues;
        bool                            _flagEverythingGood;

    public:
        BitcoinExchange();
        BitcoinExchange( BitcoinExchange const & src);
        ~BitcoinExchange();
        BitcoinExchange &operator=(const BitcoinExchange &src);

        //getters
        bool                            getFlagEverythingGood() const;
        std::deque<std::deque<double> > getDatabase() const;
        std::deque<double>              getInputValues() const;
        //Functions
        void                    SaveDatabase( void );
        bool                    EditDatabaseFile(std::ifstream& File, std::deque<std::deque<double> >& Container, std::string delimiter);
        void                    StrTrim(std::string& str);
        void                    SavingValuesDatabaseContainer(std::string date, std::deque<std::deque<double> >& Container, std::string Value, unsigned int index);
        std::deque<std::string> ft_split(std::string src, std::string del);
        double                  string_to_double(const std::string& str, unsigned int index);
        void                    PrintDoubleArray(std::deque<std::deque<double> > Container) const;
        void                    PrintScreen(char *file);
        void                    RunInputFile(std::ifstream& File, std::deque<double> &Container, std::string delimiter);
        bool                    CheckWhileString(std::string &date, std::string &line, std::string &value, unsigned int &index, std::string delimiter);
        void                    ConvertToDouble(std::string date, std::string value, std::deque<double> &Container, unsigned int index);
        void                    PrintSingleArray(std::deque<double> container);
        void                    PrintMessage(std::deque<double> &Container, int *DaysOnMonth, unsigned int &index);
        bool                    CheckDate(std::deque<double> &Container, int *DaysOnMonth);
        bool                    isLeapYear(int year);
        int                     SearchDatabase(std::deque<double> &Container, std::deque<std::deque<double> >& Database);


};      

std::ostream &  operator<<( std::ostream & o, BitcoinExchange const & i );

#endif
