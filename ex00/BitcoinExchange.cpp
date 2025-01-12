#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _flagEverythingGood(false){
    std::cout << "BitcoinExchange default constructor called" << std::endl;
}

BitcoinExchange::~BitcoinExchange(){
    std::cout << "BitcoinExchange destructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src){
    std::cout << "BitcoinExchange Copy constructor called" << std::endl;
    *this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	std::cout << "BitcoinExchange Assignment operator called" << std::endl;
	if (this != &src){
        this->_flagEverythingGood = src.getFlagEverythingGood();
        this->_Database = src.getDatabase();
        this->_InputValues = src.getInputValues();
	}
	return (*this);
}

bool BitcoinExchange::getFlagEverythingGood() const{
    return (this->_flagEverythingGood);
}

std::deque<std::deque<double> > BitcoinExchange::getDatabase() const {
    return (this->_Database);
}

std::deque<double>              BitcoinExchange::getInputValues() const{
    return (this->_InputValues);
}

void BitcoinExchange::StrTrim(std::string& str){

    size_t start = str.find_first_not_of(" \t\r\n");
    if (start != std::string::npos)
        str = str.substr(start);

    size_t end = str.find_last_not_of(" \t\r\n");
    if (end != std::string::npos)
        str = str.substr(0, end + 1);
}

bool    BitcoinExchange::EditDatabaseFile(std::ifstream& File, std::deque<std::deque<double> >& Container, std::string delimiter){
    
    std::string line;
    std::string date;
    std::string value;
    size_t pos = 0;
    unsigned int index = 1;

    while (std::getline(File, line)){
        if (line == "date,exchange_rate" && index == 1){
            index++;
            continue;
        }
        else if (line != "date,exchange_rate" && index == 1)
            throw std::invalid_argument("The first line of the database must be \"date,exchange_rate\"");
        pos = line.find(delimiter);
        if (pos == std::string::npos)
            return false;
        date = line.substr(0, pos);
        value = line.substr(pos + delimiter.length());
        StrTrim(date);
        StrTrim(value);
        SavingValuesDatabaseContainer(date, Container, value, index);
        index++;
    }
    if (this->_flagEverythingGood)
            return false;
    return true;
}

void    BitcoinExchange::RunInputFile(std::ifstream& File, std::deque<double> &Container, std::string delimiter){

    std::string line;
    std::string date;
    std::string value;
    unsigned int index = 1;
    int DaysOnMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (std::getline(File, line)){
        if (CheckWhileString(date, line, value, index, delimiter)){
            index++;
            continue;
        }
        ConvertToDouble(date, value, Container, index);
        PrintMessage(Container, DaysOnMonth, index);
        Container.clear();
        index++;
    }
}

void    BitcoinExchange::PrintMessage(std::deque<double> &Container, int *DaysOnMonth, unsigned int &index){
    
    if (Container[3] > 1000){
        std:: cerr << "Error: too large a number on line " <<  index << std::endl;
        return ;
    }
    else if (Container[3] < 0){
        std:: cerr << "Error: not a positive number on line " <<  index << std::endl;
        return ;
    }
    if (!CheckDate(Container, DaysOnMonth)){
        std:: cerr << "Error: Bad date on line " <<  index << std::endl;
        return ;
    }

    int positionDB = SearchDatabase(Container, this->_Database);
    
    
    std::cout << Container[0] << "-";
    if (Container[1] < 10)
        std::cout << "0";
    std::cout << Container[1] << "-";
    if (Container[2] < 10)
        std::cout << "0";
    std::cout << Container[2];
    std::cout  << " => " << Container[3] << " = " << Container[3] * this->_Database[positionDB][3] << std::endl;
}

int     BitcoinExchange::SearchDatabase(std::deque<double> &Container, std::deque<std::deque<double> > &Database){

    unsigned int index = 0;

    while ((Container[0] > Database[index][0]) && index < Database.size())
        index++;
    while ((Container[1] > Database[index][1]) && index < Database.size())
        index++;
    while ((Container[2] > Database[index][2]) && index < Database.size() && Container[1] == Database[index][1])
        index++;
    
    if (Container[2] != Database[index][2])
        index--;
    return (index);

}

bool    BitcoinExchange::CheckDate(std::deque<double> &Container, int *DaysOnMonth){
    
    if (isLeapYear(Container[0]))
        DaysOnMonth[1] = 29;
    else
        DaysOnMonth[1] = 28;

    if (Container[1] > 12 || Container[1] < 1)
        return false;
    
    if (Container[2] > DaysOnMonth[static_cast<int>(Container[1]) - 1] || Container[2] < 1)
        return false;
    return true;
}

bool BitcoinExchange::isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            return (year % 400 == 0);
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void    BitcoinExchange::ConvertToDouble(std::string date, std::string value, std::deque<double> &Container, unsigned int index){

    std::deque<std::string> DividedValues;
    double Conversion;

    DividedValues = ft_split(date, "-");
    
    std::deque<std::string>::iterator it = DividedValues.begin();
    
    while (it != DividedValues.end()){
        Conversion = string_to_double(*it, index);
        Container.push_back(Conversion);
        it++;
    }
    
    Container.push_back(string_to_double(value, index));
}

bool BitcoinExchange::CheckWhileString(std::string &date, std::string &line, std::string &value, unsigned int &index, std::string delimiter){
    
    size_t pos = 0;
    
    if (line == "date | value" && index == 1){
        return true;
    }
    else if (line != "date | value" && index == 1)
        throw std::invalid_argument("The first line of the input file must be \"date | value\"");
    pos = line.find(delimiter);
    if (pos == std::string::npos){
        std:: cerr << "Error: bad input on line " <<  index <<  " => " << line << std::endl;
        return true;
    }
    date = line.substr(0, pos);
    value = line.substr(pos + delimiter.length());
    StrTrim(date);
    StrTrim(value);
    if (value.length() == 0 || date.length() == 0 || value.find_first_not_of(" \t") || date.find_first_not_of(" \t")){
        std:: cerr << "Error: bad input on line " <<  index <<  " => " << line << std::endl;
        return true;
    }
    return false;
}

void BitcoinExchange::SavingValuesDatabaseContainer(std::string date, std::deque<std::deque<double> >& Container, std::string Value, unsigned int index){
    
    std::deque<std::string> DividedValues;
    std::deque<double> YearMonthDayValue;
    double Conversion;

    DividedValues = ft_split(date, "-");
    
    std::deque<std::string>::iterator it = DividedValues.begin();
    
    while (it != DividedValues.end()){
        Conversion = string_to_double(*it, index);
        YearMonthDayValue.push_back(Conversion);
        it++;
    }
    
    YearMonthDayValue.push_back(string_to_double(Value, index));
    
    Container.push_back(YearMonthDayValue);
}

std::deque<std::string> BitcoinExchange::ft_split(std::string src, std::string del)
{
    std::deque<std::string> tokens;
    size_t pos = 0;
    size_t len = del.length();

    while((pos = src.find(del)) != std::string::npos)
    {
        tokens.push_back(src.substr(0, pos));
        src.erase(0, pos + len);
    }
    tokens.push_back(src);
    return (tokens);
}

double BitcoinExchange::string_to_double(const std::string& str, unsigned int index) {
    std::istringstream iss(str);
    double value;

    if (!(iss >> value) || !iss.eof()) {
        std:: cerr << "Error: bad input on line " <<  index <<  " => " << str << std::endl;
        this->_flagEverythingGood = true;
    }
    return value;
}

void BitcoinExchange::PrintDoubleArray(std::deque<std::deque<double> > Container) const{
    for (std::deque<std::deque<double> >::const_iterator outerDequeIt = Container.begin(); outerDequeIt != Container.end(); ++outerDequeIt) {
        const std::deque<double>& outerDeque = *outerDequeIt;

        std::cout << "line: "; 
        
        for (std::deque<double>::const_iterator innerDequeIt = outerDeque.begin(); innerDequeIt != outerDeque.end(); ++innerDequeIt) {
            double value = *innerDequeIt;

            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

void BitcoinExchange::PrintSingleArray(std::deque<double> container){
    std::deque<double>::iterator it = container.begin();
    
    std::cout << "Element: ";
    while (it != container.end()){
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
}

void BitcoinExchange::SaveDatabase( void ){

    std::ifstream ReadFile_Database;

    ReadFile_Database.open(DATABASE);

    if (ReadFile_Database.fail()){
        throw std::invalid_argument("Error: Could not open Database.\nCheck if the file has the correct name");
    }
    
    if (!EditDatabaseFile(ReadFile_Database, this->_Database, ",")){
        throw std::invalid_argument("Error: The Database was received in an incorrect form");
    }
    
    ReadFile_Database.close();
}

void BitcoinExchange::PrintScreen(char *file){
    
    std::ifstream ReadInputFile;

    ReadInputFile.open(file);

    if (ReadInputFile.fail()){
        throw std::invalid_argument("Error: Could not open input file.\nCheck if the file has the correct name");
    }
    
    RunInputFile(ReadInputFile, this->_InputValues, "|");
    
    ReadInputFile.close();
    //PrintDoubleArray(this->_Database);
}


const char* WrongNumberOfArguments::what() const throw()
{
	return ("Error: Wrong Number of arguments\nUsage: ./btc file");
}
