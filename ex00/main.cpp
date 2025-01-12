#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
  BitcoinExchange Bitcoin;

  try {
    if (argc != 2){
      throw WrongNumberOfArguments();
    }
    Bitcoin.SaveDatabase();
    Bitcoin.PrintScreen(argv[1]);

    BitcoinExchange test(Bitcoin);
    test.PrintScreen(argv[1]);
  }
  catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
