/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagalha <smagalha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 21:28:33 by sde-mull          #+#    #+#             */
/*   Updated: 2025/04/04 20:29:14 by smagalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
    RPN calculator(argv[1]);

    if (argc != 2)
    {
		  std::cerr << "Error: need just one argument." << std::endl;
		  return (1);
    }

    try {
        calculator.Start();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}

/* 
Reverse Polish Notation is a specific way of writing expressions where first you write the values, then the operation you want to perform. 

So for instance, to add the numbers 3 and 4 you'd write 3 4 +.


*/
