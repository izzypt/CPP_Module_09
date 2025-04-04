/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:28:31 by sde-mull          #+#    #+#             */
/*   Updated: 2025/04/04 21:58:04 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){

	std::cout << "PmergeMe default constructor called" << std::endl;
}

PmergeMe::PmergeMe(int argc, char **argv){

	std::cout << "PmergeMe parametric constructor called" << std::endl;
	for (int index = 1; index < argc; index++)
		this->_SavingValues.push_back(argv[index]);
}

PmergeMe::PmergeMe(PmergeMe const &src){


	std::cout << "PmergeMe copy constructor called" << std::endl;
	*this = src;
}

PmergeMe &PmergeMe::operator=(PmergeMe const &rhs){
	
	std::cout << "PmergeMe assignment operator called" << std::endl;
	if (this != &rhs){
		
	}

	return *this;
}

PmergeMe::~PmergeMe(){

	std::cout << "PmergeMe destructor called" << std::endl;
}

std::vector<char *> PmergeMe::GetSavingValues(void) const{

	return this->_SavingValues;
}

std::vector<int> PmergeMe::GetContainerInt(void) const{

	return this->_ContainerInt;;
}

void PmergeMe::PrintVectorChar( void ) const{

	for (std::vector<char *>::const_iterator it = this->_SavingValues.begin(); it < this->_SavingValues.end(); it++)
		std::cout << "List char value: " << *it << std::endl;
}

void PmergeMe::PrintVectorInt( void ) const{
	
	for (std::vector<int>::const_iterator it = this->_ContainerInt.begin(); it < this->_ContainerInt.end(); it++)
		std::cout << *it << " ";
}

void PmergeMe::PrintListInt( void ) const{
	
	for (std::list<int>::const_iterator it = _ContainerList.begin(); it != _ContainerList.end(); ++it) {
        std::cout << *it << " ";
    }
}

void PmergeMe::Run( void ){
	
	Parsing();
	CopyVectorToList();
	std::cout << "Before: ";
	PrintVectorInt();
	std::cout << std::endl;
	clock_t start = clock();
	MergeInsertionAlgorithmVector(this->_ContainerInt);
	clock_t end = clock();
	double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "After: ";
	PrintVectorInt();
	std::cout << std::endl;

	std::cout << "Time to process a range of " << this->_ContainerInt.size() << " elements with std::vector : " << std::fixed << std::setprecision(6) << elapsed_time << " us" << std::endl;
	start = clock();
	MergeInsertionAlgorithmList(this->_ContainerList);
	end = clock();
	elapsed_time = double(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << this->_ContainerInt.size() << " elements with std::list : " << std::fixed << std::setprecision(6) << elapsed_time << " us" << std::endl;
}

void PmergeMe::CopyVectorToList( void ){
	std::copy(this->_ContainerInt.begin(), this->_ContainerInt.end(), std::back_inserter(this->_ContainerList));
}

void PmergeMe::MergeInsertionAlgorithmVector(std::vector<int> &Container){

	long unsigned int HalfContainerSize = Container.size() / 2;
		
	std::vector<int> Right;
	std::vector<int> Left;
	
	if (Container.size() > 2){

		for (long unsigned int index = 0; index < HalfContainerSize; index++)
			Left.push_back(Container[index]);	
		for (long unsigned int index = HalfContainerSize; index < Container.size(); index++)
			Right.push_back(Container[index]);
		MergeInsertionAlgorithmVector(Right);
		MergeInsertionAlgorithmVector(Left);
		MergeVector(Container, Left, Right);
	}
	else
		InsertionVector(Container);
}

void PmergeMe::MergeVector(std::vector<int> &Container, const std::vector<int> &Left, const std::vector<int> &Right) {

    size_t leftIndex = 0, rightIndex = 0, mergedIndex = 0;

    while (leftIndex < Left.size() && rightIndex < Right.size()) {
        if (Left[leftIndex] < Right[rightIndex]) {
            Container[mergedIndex++] = Left[leftIndex++];
        } else {
            Container[mergedIndex++] = Right[rightIndex++];
        }
    }

    while (leftIndex < Left.size()) {
        Container[mergedIndex++] = Left[leftIndex++];
    }

    while (rightIndex < Right.size()) {
        Container[mergedIndex++] = Right[rightIndex++];
    }
}

void PmergeMe::InsertionVector(std::vector<int> &Container){
	
	int left;
	
	for (long unsigned int index = 0; index < Container.size(); index++){

		left = index - 1;
		if (left > -1 && Container[index] < Container[left]){
			while (left > -1 && Container[left] > Container[left + 1]){
				int temp = Container[left];
				Container[left] = Container[left + 1];
				Container[left + 1]  = temp;
				left = left - 1;
			}
		}
		
	}
}

void PmergeMe::MergeInsertionAlgorithmList(std::list<int> &Container){

    std::list<int> Right;
    std::list<int> Left;

    if (Container.size() > 1){
        size_t HalfContainerSize = Container.size() / 2;

        std::list<int>::iterator it = Container.begin();
        for (size_t i = 0; i < HalfContainerSize; ++i) {
            Left.push_back(*it);
            ++it;
        }
        while (it != Container.end()) {
            Right.push_back(*it);
            ++it;
        }

        MergeInsertionAlgorithmList(Left);
        MergeInsertionAlgorithmList(Right);
        MergeList(Container, Left, Right);
    }
    else
        InsertionList(Container);
}

void PmergeMe::MergeList(std::list<int> &Container, const std::list<int> &Left, const std::list<int> &Right) {

    std::list<int>::const_iterator leftIt = Left.begin();
    std::list<int>::const_iterator rightIt = Right.begin();
    std::list<int>::iterator containerIt = Container.begin();

    while (leftIt != Left.end() && rightIt != Right.end()) {
        if (*leftIt < *rightIt) {
            *containerIt = *leftIt;
            ++leftIt;
        } else {
            *containerIt = *rightIt;
            ++rightIt;
        }
        ++containerIt;
    }

    while (leftIt != Left.end()) {
        *containerIt = *leftIt;
        ++leftIt;
        ++containerIt;
    }

    while (rightIt != Right.end()) {
        *containerIt = *rightIt;
        ++rightIt;
        ++containerIt;
    }
}

void PmergeMe::InsertionList(std::list<int> &Container) {

    std::list<int>::iterator it = Container.begin();
    std::list<int>::iterator next = it;

    ++next;

    while (next != Container.end()) {
        int key = *next;
        std::list<int>::iterator prev = it;
        --prev;

        while (prev != Container.begin() && *prev > key) {
            std::iter_swap(prev, next);
            --next;
            --prev;
        }
        ++it;
        ++next;
    }
}


void PmergeMe::Parsing( void ){
	
	for (std::vector<char *>::iterator it = this->_SavingValues.begin(); it < this->_SavingValues.end(); it++)
		PushVectorInt(*it);

	for (std::vector<int>::iterator it = this->_ContainerInt.begin(); it < this->_ContainerInt.end(); it++){

		std::map<int, bool>::iterator iter = this->_CheckRepeatedNumbers.find(*it);
		
		if (iter != this->_CheckRepeatedNumbers.end())
			throw std::invalid_argument("There must not be duplicated values!!");
		else
			this->_CheckRepeatedNumbers.insert(std::make_pair(*it, true));
		
	}
}

void PmergeMe::PushVectorInt(char *value){

	std::string StrValue(value);
	std::vector<std::string> StringSplitted;  
	
	StringSplitted = ft_split(StrValue, " ");

	for (std::vector<std::string>::iterator it = StringSplitted.begin(); it < StringSplitted.end(); it++){
		if (it->find_first_not_of("1234567890") != std::string::npos)
			throw std::invalid_argument("The values must be a positive number!!");
		else if (!CheckIntRange(*it))
			throw std::invalid_argument("The integer must be between MIN_INT and MAX_INT");
		else
			this->_ContainerInt.push_back(std::atoi(it->c_str()));
	}
}


bool PmergeMe::CheckIntRange(std::string integer){

	char* end;

    long value = std::strtol(integer.c_str(), &end, 10);

    if (value < INT_MIN || value > INT_MAX) {
        return false;
    }

	return true;
}

void PmergeMe::StrTrim(std::string& str){

    size_t start = str.find_first_not_of(" \t\r\n");
    if (start != std::string::npos)
        str = str.substr(start);

    size_t end = str.find_last_not_of(" \t\r\n");
    if (end != std::string::npos)
        str = str.substr(0, end + 1);
}

std::vector<std::string> PmergeMe::ft_split(std::string src, std::string del)
{
    std::vector<std::string> tokens;
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
