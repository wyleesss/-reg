#pragma once

#include <iostream>
#include <string>

class Pocket
{
public:

  Pocket();

  virtual ~Pocket();

protected:

  unsigned long int p_balance;

  void setP_balance(unsigned long int value)
  {
    p_balance = value;
  }

  unsigned long int getP_balance()
  {
    return p_balance;
  }

  void p_plus(unsigned long int money);
  void p_pay(unsigned long int money);
  void p_info();
};
