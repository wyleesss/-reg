#pragma once
#include "regdb.h"
#include <vector>
#include <stdio.h>
#include <sqlite3.h>

const char* direction = "project_data.db";

void dbnew_user(int ID, std::string NAME, int AGE, std::string MAIN_CURRENCY, std::string LOGIN, std::string GMAIL, std::string PASSWORD, std::string SECRET_QUESTION, std::string SECRET_ANSWEAR) {
	sqlite3* DB;
	char* errorMessagge;
	int res = sqlite3_open(direction, &DB);
	std::string insert = "INSERT INTO USERS (ID, NAME, AGE, MAIN_CURRENCY, LOGIN, GMAIL, PASSWORD, SECRET_QUESTION, SECRET_ANSWEAR) VALUES("
		+ std::to_string(ID) + ", '"
		+ NAME + "', "
		+ std::to_string(AGE) + ", '"
		+ MAIN_CURRENCY + "', '"
		+ LOGIN + "', '"
		+ GMAIL + "', '"
		+ PASSWORD + "', '"
		+ SECRET_QUESTION + "', '"
		+ SECRET_ANSWEAR + "'"
		+ ");";
	res = sqlite3_exec(DB, insert.c_str(), NULL, 0, &errorMessagge);
	if (res != SQLITE_OK) {
		sqlite3_free(errorMessagge);
		sqlite3_close(DB);
		return;
	}
	sqlite3_close(DB);
}

bool dbcheck_login(std::string LOGIN) {
	sqlite3* DB;
	sqlite3_stmt* STMT;
	char* errorMessagge;
	std::string select = "SELECT * FROM USERS";
	int res = sqlite3_open(direction, &DB);
	res = sqlite3_prepare_v2(DB, select.c_str(), -1, &STMT, NULL);
	if (res != SQLITE_OK) {
		sqlite3_free(&errorMessagge);
		sqlite3_reset(STMT);
		sqlite3_close(DB);
		return false;
	}
	while (res = sqlite3_step(STMT) == SQLITE_ROW) {
		if (LOGIN == std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 4)))) {
			sqlite3_reset(STMT);
			return true;
		}
	}
	sqlite3_reset(STMT);
	return false;
}

bool dbcheck_gmail(std::string GMAIL) {
	sqlite3* DB;
	sqlite3_stmt* STMT;
	char* errorMessagge;
	std::string select = "SELECT * FROM USERS";
	int res = sqlite3_open(direction, &DB);
	res = sqlite3_prepare_v2(DB, select.c_str(), -1, &STMT, NULL);
	if (res != SQLITE_OK) {
		sqlite3_free(&errorMessagge);
		sqlite3_reset(STMT);
		sqlite3_close(DB);
		return false;
	}
	while (res = sqlite3_step(STMT) == SQLITE_ROW) {
		if (GMAIL == std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 5)))) {
			sqlite3_reset(STMT);
			return true;
		}
	}
	sqlite3_reset(STMT);
	return false;
}

std::string dbtake_password(std::string LOGIN) {
	sqlite3* DB;
	sqlite3_stmt* STMT;
	char* errorMessagge;
	std::string select = "SELECT * FROM USERS";
	int res = sqlite3_open(direction, &DB);
	res = sqlite3_prepare_v2(DB, select.c_str(), -1, &STMT, NULL);
	if (res != SQLITE_OK) {
		sqlite3_free(&errorMessagge);
		sqlite3_close(DB);
		return "";
	}
	while (res = sqlite3_step(STMT) == SQLITE_ROW) {
		if (LOGIN == std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 4)))) {
			std::string result = std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 6)));
			sqlite3_reset(STMT);
			return result;
		}
	}
	sqlite3_reset(STMT);
	return "";
}

void dbtake_sqsa(std::string LOGIN, std::string& SECRET_QUESTION, std::string& SECRET_ANSWEAR) {
	sqlite3* DB;
	sqlite3_stmt* STMT;
	char* errorMessagge;
	std::string select = "SELECT * FROM USERS";
	int res = sqlite3_open(direction, &DB);
	res = sqlite3_prepare_v2(DB, select.c_str(), -1, &STMT, NULL);
	if (res != SQLITE_OK) {
		sqlite3_free(&errorMessagge);
		sqlite3_reset(STMT);
		sqlite3_close(DB);
		return;
	}
	while (res = sqlite3_step(STMT) == SQLITE_ROW) {
		if (LOGIN == std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 4)))) {
			SECRET_QUESTION = std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 7)));
			SECRET_ANSWEAR = std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 8)));
			sqlite3_reset(STMT);
			return;
		}
	}
	sqlite3_reset(STMT);
}

void dbupdate_password(std::string LOGIN, std::string NEW_PASSWORD) {
	if (!dbcheck_login(LOGIN)) return;
	sqlite3* DB;
	char* errorMessagge;
	std::string select = "UPDATE USERS SET PASSWORD = '" + NEW_PASSWORD + "' WHERE LOGIN = '" + LOGIN + "';";
	int res = sqlite3_open(direction, &DB);
	res = sqlite3_exec(DB, select.c_str(), NULL, 0, &errorMessagge);
	if (res != SQLITE_OK) {
		sqlite3_free(&errorMessagge);
		sqlite3_close(DB);
		return;
	}
}

void dbcreate_tables(const int USER_ID) {
	sqlite3* DB;

	std::string CARDS = "CREATE TABLE IF NOT EXISTS CARDS_ID" + std::to_string(USER_ID) + "("
		"CARD_NUMBER        CHAR(16) NOT NULL, "
		"CREDIT_LIMIT       INT      NOT NULL, "
		"BALANCE            INT      NOT NULL, "
		"NAME               TEXT);";

	std::string PCI = "CREATE TABLE IF NOT EXISTS PCI_ID" + std::to_string(USER_ID) + "("
		"PCV_LIST           TEXT     NOT NULL, "
		"CCV_LIST           TEXT);";

	std::string TRANSICTION = "CREATE TABLE IF NOT EXISTS TRANSICTIONS_ID" + std::to_string(USER_ID) + "("
		"DAY                INT      NOT NULL, "
		"MONTH              INT      NOT NULL, "
		"YEAR               INT      NOT NULL, "
		"CATEGORY           TEXT     NOT NULL, "
		"SUMM               INT      NOT NULL, "
		"PAYMENT_METHOD     TEXT     NOT NULL, "
		"CARD_NUMBER        CHAR(16));";

	std::vector<std::string> all_tables{ CARDS, PCI, TRANSICTION };

	for (auto i = all_tables.begin(); i < all_tables.end(); i++) {
		int res = sqlite3_open(direction, &DB);
		char* errorMessagge;
		res = sqlite3_exec(DB, (*i).c_str(), NULL, 0, &errorMessagge);
		if (res != SQLITE_OK) {
			sqlite3_free(errorMessagge);
			sqlite3_close(DB);
			return;
		}
		sqlite3_close(DB);
	}
	return;
}

int dbtake_id(std::string LOGIN) {
	sqlite3* DB;
	sqlite3_stmt* STMT;
	char* errorMessagge;
	std::string select = "SELECT * FROM USERS";
	int res = sqlite3_open(direction, &DB);
	res = sqlite3_prepare_v2(DB, select.c_str(), -1, &STMT, NULL);
	if (res != SQLITE_OK) {
		sqlite3_free(&errorMessagge);
		sqlite3_reset(STMT);
		sqlite3_close(DB);
		return -1;
	}
	while (res = sqlite3_step(STMT) == SQLITE_ROW) {
		if (LOGIN == std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 4)))) {
			int result = sqlite3_column_int(STMT, 0);
			sqlite3_reset(STMT);
			return result;
		}
	}
}

void dbselect_users(std::string LOGIN, std::string& NAME, int& AGE, std::string& MAIN_CURRENCY, std::string& GMAIL) {
	sqlite3* DB;
	sqlite3_stmt* STMT;
	char* errorMessagge;
	std::string select = "SELECT * FROM USERS";
	int res = sqlite3_open(direction, &DB);
	res = sqlite3_prepare_v2(DB, select.c_str(), -1, &STMT, NULL);
	if (res != SQLITE_OK) {
		sqlite3_free(&errorMessagge);
		sqlite3_close(DB);
		return;
	}
	while (res = sqlite3_step(STMT) == SQLITE_ROW) {
		if (LOGIN == std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 4)))) {
			NAME = std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 1)));
			AGE = sqlite3_column_int(STMT, 2);
			MAIN_CURRENCY = std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 3)));
			GMAIL = std::string(reinterpret_cast<const char*>(sqlite3_column_text(STMT, 5)));
		}
	}
	sqlite3_reset(STMT);
	sqlite3_close(DB);
}