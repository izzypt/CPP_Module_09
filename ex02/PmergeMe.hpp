/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:38:03 by smagalha          #+#    #+#             */
/*   Updated: 2025/04/05 12:38:05 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PmergeMe_HPP
# define PmergeMe_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <deque>
#include <string>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <map>
#include <vector>
#include <cctype>
#include <climits>
#include <cerrno>
#include <iomanip>
#include <list> 

class PmergeMe
{
    private:
        std::map<int, bool>     _CheckRepeatedNumbers;
        std::vector<char *>     _SavingValues;
        std::vector<int>        _ContainerInt;
        std::list<int>          _ContainerList;

    public:
        PmergeMe();
        PmergeMe(int argc, char **argv);
        PmergeMe( PmergeMe const & src);
        ~PmergeMe();

        PmergeMe & operator=(PmergeMe const & rhs);

        //getters functions
        std::vector<char *> GetSavingValues( void ) const;
        std::vector<int>    GetContainerInt(void) const;
        
        //prints functions
        void PrintVectorChar( void ) const;
        void PrintVectorInt( void ) const;
        void PrintListInt( void ) const;

        //Other
        void Run ( void );
        void Parsing( void );
        void PushVectorInt(char *value);

        std::vector<std::string> ft_split(std::string src, std::string del);
        void StrTrim(std::string& str);
        bool CheckIntRange(std::string integer);

        void MergeInsertionAlgorithmVector(std::vector<int> &Container);
        void InsertionVector(std::vector<int> &Container);
        void MergeVector(std::vector<int> &Container, const std::vector<int> &Left, const std::vector<int> &Right);

        void MergeInsertionAlgorithmList(std::list<int> &Container);
        void InsertionList(std::list<int> &Container);
        void MergeList(std::list<int> &Container, const std::list<int> &Left, const std::list<int> &Right);

        void CopyVectorToList( void );

};

#endif
