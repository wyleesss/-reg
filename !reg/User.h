#pragma once

#include <iostream>
#include <string>
#include "Card.h"
#include <vector>
#include "Pocket.h"

class User : public Card, public Pocket
{
public:

  User();

  virtual ~User();

protected:
    vector<Card> all_cards;
  std::string u_name;
  unsigned short int u_age;
  std::string u_main_currency;
  std::string u_login;
  std::string u_gmail;
  std::string u_password;


  void setU_name(std::string value)
  {
    u_name = value;
  }

  std::string getU_name()
  {
    return u_name;
  }

  void setU_age(unsigned short int value)
  {
    u_age = value;
  }

  unsigned short int getU_age()
  {
    return u_age;
  }

  void setU_main_currency(std::string value)
  {
    u_main_currency = value;
  }

  std::string getU_main_currency()
  {
    return u_main_currency;
  }

  void u_ch_pass(std::string old_pass, std::string new_pass);
      void u_ch_gmail(std::string pass, std::string new_gmail);
      std::string u_pass_rec();
};


