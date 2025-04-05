/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:38:14 by smagalha          #+#    #+#             */
/*   Updated: 2025/04/05 12:38:18 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2){
        std::cout << "Error: Wrong number of arguments\nUsage: ./PmergeMe \"Numbers\"" << std::endl;
        return (1);
    }

    PmergeMe Values(argc, argv);

    //Values.PrintVectorChar();
    try{
        
        Values.Run();
        //Values.PrintVectorInt();
   
    } catch (std::exception &e) {

        std::cout << "Error: " << e.what() << std::endl << std::endl;
    }

    return 0;
}

/* 
The exercise asks you to sort using two different containers, but doesn't specify which containers to use. 

Common choices could be std::vector and std::deque, but you can choose any containers that are appropriate for this task.

The goal is to demonstrate the difference in sorting time between two containers, highlighting how the choice of container can impact performance.

The exercise also asks for precise time measurement, so you’ll need to account for timing the sorting process (likely using std::chrono in C++).
*/
