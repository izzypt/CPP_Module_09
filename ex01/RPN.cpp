/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:28:31 by sde-mull          #+#    #+#             */
/*   Updated: 2025/04/04 21:06:54 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

// Constructor, called when an instance of RPN is created.
RPN::RPN() {
    std::cout << "RPN default constructor called" << std::endl;
}

// Constructor, called when an instance of RPN is created with an expression.
RPN::RPN(char *expression) {
    std::cout << "RPN default constructor called" << std::endl;

    // Convert the input expression (char*) into a string and store it in _Expression.
    this->_Expression = std::string(expression);
}

// Destructor, called when an instance of RPN is destroyed.
RPN::~RPN() {
    std::cout << "RPN destructor called" << std::endl;
}

// Copy constructor, used when creating a new instance as a copy of an existing one.
RPN::RPN(RPN const & src) {
    std::cout << "RPN copy constructor called" << std::endl;
    
    // Copy the state of the source object into the new object.
    *this = src;
}

// Assignment operator, used to assign one RPN object to another.
RPN & RPN::operator=(RPN const & rhs) {
    std::cout << "RPN assignment operator called" << std::endl;
    
    if (this != &rhs)
        this->_Numbers = rhs._Numbers;  // Copy the stack of numbers from rhs to the current object.
    
    return *this;
}

// The Start function processes the RPN expression, evaluates it, and prints the result.
void RPN::Start(void) {
    int checkSpace = 1;  // A flag to ensure that operators are correctly separated by operands.

    // If the expression is too short (4 characters or less), throw an error.
    if (this->_Expression.size() <= 4)
        throw std::invalid_argument("Error");
    
    // Loop through each character in the expression.
    for (std::string::iterator it = this->_Expression.begin(); it != this->_Expression.end(); it++) {
        
        // Check for invalid characters (anything other than digits, operators, and spaces).
        if (*it != '*' && *it != '-' && *it != '+' && *it != '/' && !(*it >= '0' && *it <= '9') && *it != ' ')
            throw std::invalid_argument("Error");
        
        // If the character is a number (0-9), push it to the stack.
        if (*it >= '0' && *it <= '9') {
            // If a number is not preceded by a space or operator, throw an error.
            if (checkSpace == 0)
                throw std::invalid_argument("Error");
            this->_Numbers.push(*it - '0');  // Push the number (converted from char to int) onto the stack.
            checkSpace = 0;  // Mark that the next character should be an operator or space.
        }

        // If the character is an operator, pop two numbers from the stack, perform the operation, and push the result back.
        if (*it == '*' || *it == '/' || *it == '+' || *it == '-') {
            if (checkSpace == 0)  // If an operator follows a number without a space, throw an error.
                throw std::invalid_argument("Error");
            if (this->_Numbers.size() < 2)  // If there are fewer than two numbers, throw an error.
                throw std::invalid_argument("Error");
            
            int second = this->_Numbers.top();  // Pop the second operand.
            this->_Numbers.pop();
            int first = this->_Numbers.top();   // Pop the first operand.
            this->_Numbers.pop();
            
            // Perform the operation and push the result back onto the stack.
            this->_Numbers.push(Calculate(first, second, *it));
            checkSpace = 0;
        }

        // If there's no space after a number or operator, it's an error.
        if (checkSpace == 1)
            throw std::invalid_argument("Error");
        
        // If the character is a space, set the checkSpace flag to allow a number or operator to follow.
        if (*it == ' ')
            checkSpace = 1;
    }

    // If there is more than one number left in the stack, it's an error.
    if (this->_Numbers.size() > 1)
        throw std::invalid_argument("Error");
    
    // Output the result (top element of the stack).
    std::cout << "Result: " << this->_Numbers.top() << std::endl;
}

// Helper function to print the contents of the stack for debugging.
void RPN::printStack(void) const {
    std::stack<int> tempStack = _Numbers;  // Copy the stack to a temporary stack for printing.

    // Print the elements of the stack from top to bottom.
    while (!tempStack.empty()) {
        std::cout << tempStack.top() << std::endl;
        tempStack.pop();
    }
}

// Helper function to perform the arithmetic operation on two operands.
int RPN::Calculate(int first, int second, char operation) {
    // Depending on the operator, perform the appropriate operation and return the result.
    if (operation == '+') 
        return (first + second);
    else if (operation == '-')
        return (first - second);
    else if (operation == '*')
        return (first * second);
    else if (operation == '/') {
        if (second == 0)  // If dividing by zero, throw an error.
            throw std::invalid_argument("Error");
        return (first / second);
    }

    // If the operator is not recognized, throw an error.
    throw std::invalid_argument("Error");
}
