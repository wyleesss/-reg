#pragma once

#include <iostream>
#include <string>


class Card
{
public:

  Card();

  virtual ~Card();


protected:


  std::string c_numbers;
  unsigned int c_limit;
  int c_balance;
  std::string c_name;

  void setC_numbers(std::string value)
  {
    c_numbers = value;
  }

  std::string getC_numbers()
  {
    return c_numbers;
  }

  void setC_limit(unsigned int value)
  {
    c_limit = value;
  }

  unsigned int getC_limit()
  {
    return c_limit;
  }

  void setC_balance(int value)
  {
    c_balance = value;
  }

  int getC_balance()
  {
    return c_balance;
  }

  void setC_name(std::string value)
  {
    c_name = value;
  }

  std::string getC_name()
  {
    return c_name;
  }


  void c_plus(unsigned long int money);
  void c_pay(unsigned long int money);
  void c_info();
};
