/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:28:31 by sde-mull          #+#    #+#             */
/*   Updated: 2025/04/05 12:42:11 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// Default constructor
PmergeMe::PmergeMe(){
    std::cout << "PmergeMe default constructor called" << std::endl;
}

// Parametric constructor, takes command-line arguments and stores them in _SavingValues
PmergeMe::PmergeMe(int argc, char **argv){
    std::cout << "PmergeMe parametric constructor called" << std::endl;
    // Start from index 1 to avoid the program name
    for (int index = 1; index < argc; index++)
        this->_SavingValues.push_back(argv[index]);
}

// Copy constructor - called when a new object is created from an existing one
PmergeMe::PmergeMe(PmergeMe const &src){
    std::cout << "PmergeMe copy constructor called" << std::endl;
    *this = src;  // Call the assignment operator
}

// Assignment operator to assign one PmergeMe object to another
PmergeMe &PmergeMe::operator=(PmergeMe const &rhs){
    std::cout << "PmergeMe assignment operator called" << std::endl;
    if (this != &rhs){
        // You can add copying logic here if needed (currently it's shallow)
    }
    return *this;
}

// Destructor - called when an object is destroyed
PmergeMe::~PmergeMe(){
    std::cout << "PmergeMe destructor called" << std::endl;
}

// Accessor for the _SavingValues vector (command-line arguments)
std::vector<char *> PmergeMe::GetSavingValues(void) const{
    return this->_SavingValues;
}

// Accessor for the _ContainerInt vector (parsed integers)
std::vector<int> PmergeMe::GetContainerInt(void) const{
    return this->_ContainerInt;
}

// Prints all elements in _SavingValues vector (char* values)
void PmergeMe::PrintVectorChar(void) const{
    for (std::vector<char *>::const_iterator it = this->_SavingValues.begin(); it < this->_SavingValues.end(); it++)
        std::cout << "List char value: " << *it << std::endl;
}

// Prints all elements in _ContainerInt vector (integers)
void PmergeMe::PrintVectorInt(void) const{
    for (std::vector<int>::const_iterator it = this->_ContainerInt.begin(); it < this->_ContainerInt.end(); it++)
        std::cout << *it << " ";
}

// Prints all elements in _ContainerList list (integers)
void PmergeMe::PrintListInt(void) const{
    for (std::list<int>::const_iterator it = _ContainerList.begin(); it != _ContainerList.end(); ++it) {
        std::cout << *it << " ";
    }
}

// Main logic to run the program
void PmergeMe::Run(void){
    Parsing();  // Parse command-line arguments into _ContainerInt
    CopyVectorToList();  // Copy vector to list for parallel sorting
    std::cout << "Before: ";
    PrintVectorInt();  // Print the unsorted integers
    std::cout << std::endl;
    
    // Measure sorting time for std::vector
    clock_t start = clock();
    MergeInsertionAlgorithmVector(this->_ContainerInt);  // Sort vector
    clock_t end = clock();
    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "After: ";
    PrintVectorInt();  // Print sorted vector
    std::cout << std::endl;

    std::cout << "Time to process a range of " << this->_ContainerInt.size() << " elements with std::vector : " 
              << std::fixed << std::setprecision(6) << elapsed_time << " us" << std::endl;

    // Measure sorting time for std::list
    start = clock();
    MergeInsertionAlgorithmList(this->_ContainerList);  // Sort list
    end = clock();
    elapsed_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << this->_ContainerInt.size() << " elements with std::list : " 
              << std::fixed << std::setprecision(6) << elapsed_time << " us" << std::endl;
}

// Copy contents of _ContainerInt (std::vector) into _ContainerList (std::list)
void PmergeMe::CopyVectorToList(void){
    std::copy(this->_ContainerInt.begin(), this->_ContainerInt.end(), std::back_inserter(this->_ContainerList));
}

// Recursively applies merge-insertion sort to a vector
void PmergeMe::MergeInsertionAlgorithmVector(std::vector<int> &Container){
    long unsigned int HalfContainerSize = Container.size() / 2;
    
    std::vector<int> Right;
    std::vector<int> Left;
    
    if (Container.size() > 2){
        // Split the vector into Left and Right halves
        for (long unsigned int index = 0; index < HalfContainerSize; index++)
            Left.push_back(Container[index]);
        for (long unsigned int index = HalfContainerSize; index < Container.size(); index++)
            Right.push_back(Container[index]);
        
        // Recursively sort Left and Right halves
        MergeInsertionAlgorithmVector(Right);
        MergeInsertionAlgorithmVector(Left);

        // Merge the two sorted halves back into the Container
        MergeVector(Container, Left, Right);
    }
    else {
        // If size <= 2, use insertion sort directly
        InsertionVector(Container);
    }
}

// Merge two sorted vectors into one
void PmergeMe::MergeVector(std::vector<int> &Container, const std::vector<int> &Left, const std::vector<int> &Right) {
    size_t leftIndex = 0, rightIndex = 0, mergedIndex = 0;

    // Merge elements from Left and Right vectors into Container
    while (leftIndex < Left.size() && rightIndex < Right.size()) {
        if (Left[leftIndex] < Right[rightIndex]) {
            Container[mergedIndex++] = Left[leftIndex++];
        } else {
            Container[mergedIndex++] = Right[rightIndex++];
        }
    }

    // If any elements are left in Left, add them to Container
    while (leftIndex < Left.size()) {
        Container[mergedIndex++] = Left[leftIndex++];
    }

    // If any elements are left in Right, add them to Container
    while (rightIndex < Right.size()) {
        Container[mergedIndex++] = Right[rightIndex++];
    }
}

// Insertion sort for a vector
void PmergeMe::InsertionVector(std::vector<int> &Container){
    int left;
    
    // Iterate through the vector and perform insertion sort
    for (long unsigned int index = 0; index < Container.size(); index++){
        left = index - 1;
        if (left > -1 && Container[index] < Container[left]){
            // Perform insertion for this element
            while (left > -1 && Container[left] > Container[left + 1]){
                int temp = Container[left];
                Container[left] = Container[left + 1];
                Container[left + 1] = temp;
                left = left - 1;
            }
        }
    }
}

// Recursively applies merge-insertion sort to a list
void PmergeMe::MergeInsertionAlgorithmList(std::list<int> &Container){
    std::list<int> Right;
    std::list<int> Left;

    if (Container.size() > 1){
        size_t HalfContainerSize = Container.size() / 2;

        // Split the list into Left and Right halves
        std::list<int>::iterator it = Container.begin();
        for (size_t i = 0; i < HalfContainerSize; ++i) {
            Left.push_back(*it);
            ++it;
        }
        while (it != Container.end()) {
            Right.push_back(*it);
            ++it;
        }

        // Recursively sort Left and Right halves
        MergeInsertionAlgorithmList(Left);
        MergeInsertionAlgorithmList(Right);

        // Merge the two sorted halves back into the Container
        MergeList(Container, Left, Right);
    }
    else
        InsertionList(Container);  // Use insertion sort for list if size <= 1
}

// Merge two sorted lists into one
void PmergeMe::MergeList(std::list<int> &Container, const std::list<int> &Left, const std::list<int> &Right) {
    std::list<int>::const_iterator leftIt = Left.begin();
    std::list<int>::const_iterator rightIt = Right.begin();
    std::list<int>::iterator containerIt = Container.begin();

    // Merge elements from Left and Right lists into Container
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

    // If any elements are left in Left, add them to Container
    while (leftIt != Left.end()) {
        *containerIt = *leftIt;
        ++leftIt;
        ++containerIt;
    }

    // If any elements are left in Right, add them to Container
    while (rightIt != Right.end()) {
        *containerIt = *rightIt;
        ++rightIt;
        ++containerIt;
    }
}

// Insertion sort for a list
void PmergeMe::InsertionList(std::list<int> &Container) {
    std::list<int>::iterator it = Container.begin();
    std::list<int>::iterator next = it;

    ++next;

    // Perform insertion sort for each element in the list
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

// Parsing command-line arguments, converting them to integers and validating them
void PmergeMe::Parsing(void){
    for (std::vector<char *>::iterator it = this->_SavingValues.begin(); it < this->_SavingValues.end(); it++)
        PushVectorInt(*it);  // Convert char* to integer and store in _ContainerInt

    // Check for duplicate values and throw an error if found
    for (std::vector<int>::iterator it = this->_ContainerInt.begin(); it < this->_ContainerInt.end(); it++){
        std::map<int, bool>::iterator iter = this->_CheckRepeatedNumbers.find(*it);
        
        if (iter != this->_CheckRepeatedNumbers.end())
            throw std::invalid_argument("There must not be duplicated values!!");
        else
            this->_CheckRepeatedNumbers.insert(std::make_pair(*it, true));
    }
}

// Convert string values from command line arguments to integers and push them to _ContainerInt
void PmergeMe::PushVectorInt(char *value){
    std::string StrValue(value);
    std::vector<std::string> StringSplitted;  
    StringSplitted = ft_split(StrValue, " ");  // Split string by spaces

    for (std::vector<std::string>::iterator it = StringSplitted.begin(); it < StringSplitted.end(); it++){
        if (it->find_first_not_of("1234567890") != std::string::npos)
            throw std::invalid_argument("The values must be a positive number!!");
        else if (!CheckIntRange(*it))  // Check if integer is within valid range
            throw std::invalid_argument("The integer must be between MIN_INT and MAX_INT");
        else
            this->_ContainerInt.push_back(std::atoi(it->c_str()));  // Convert and store integer
    }
}

// Check if the integer value is within the valid range
bool PmergeMe::CheckIntRange(std::string integer) {
    long value = std::atol(integer.c_str());
    return (value >= INT_MIN && value <= INT_MAX);
}

// Helper function to split a string by a delimiter
std::vector<std::string> PmergeMe::ft_split(std::string src, std::string del) {
    std::vector<std::string> result;
    size_t pos = 0;
    while ((pos = src.find(del)) != std::string::npos) {
        result.push_back(src.substr(0, pos));
        src.erase(0, pos + del.length());
    }
    result.push_back(src);  // Push the last part after the last delimiter
    return result;
}
