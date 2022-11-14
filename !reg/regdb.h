#pragma once
#include <string>

void dbnew_user(int ID, std::string NAME, int AGE, std::string MAIN_CURRENCY, std::string LOGIN, std::string GMAIL, std::string PASSWORD, std::string SECRET_QUESTION, std::string SECRET_ANSWEAR);

bool dbcheck_login(std::string LOGIN);

bool dbcheck_gmail(std::string GMAIL);

std::string dbtake_password(std::string LOGIN);

void dbtake_sqsa(std::string LOGIN, std::string& SECRET_QUESTION, std::string& SECRET_ANSWEAR);

void dbupdate_password(std::string LOGIN, std::string NEW_PASSWORD);

void dbcreate_tables(const int USER_ID);

int dbtake_id(std::string LOGIN);

void dbselect_users(std::string LOGIN, std::string& NAME, int& AGE, std::string& MAIN_CURRENCY, std::string& GMAIL);