#include "MD5.h"
#include "regdb.h"
#include "Card.h"
#include "Pocket.h"
#include "User.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

class ID {
	long int id_iterator = 0;
public:
	int takeup() 
	{ 
		id_iterator++;
		return id_iterator;
	}
};
ID USER_ID;

User U;

bool check_login(string login) {
	if (login.size() > 6 && login.find(" ") == string::npos && login.size() < 20)
	{
		return true;
	}
	return false;
}

bool check_pass(string password) {
	if (password.size() > 6 && password.find(" ") == string::npos && password.size() < 20)
	{
		return true;
	}
	return false;
}

bool inline check_Sign(string login, string password) {
	if (check_login(login) && check_pass(password))
	{
		return true;
	}
	return false;
}

void reg_init() {
	bool leaver;
	bool run = true;
	int choice, age;
	string login = "", password = "", question = "", answer = "", u_answer = "", name = "", main_currency = "", gmail = "", string_age = "";
	while (run)
	{
		system("CLS");
		cout << "Choose the option->\n";
		cout << "1 - Sign in\n";
		cout << "2 - Log in\n";
		cout << "3 - Forget password?\n";
		cin >> choice;
		switch (choice)
		{
		case(1): //Регістрація
			system("CLS");
			cout << "e - to return\n\n";

			leaver = false;
			while (true) {
				cout << "Write your name->\n";
				cin >> name;
				/*if (!check_name(name)) {
						cout << "INVALID NAME\n";
						continue;
					}*/
				if (name == "e") {
					leaver = true;
					break;
				}

				cout << "Write your age->\n";
				cin >> string_age;
				/*if (age<14&||string_age>100) {
						cout << "INVALID AGE\n";
						continue;
					}*/
				if (string_age == "e") {
					leaver = true;
					break;
				}
				age = stoi(string_age);

				cout << "Write your main currency->\n";
				cin >> main_currency;
				/*if (!check_main_currency(main_currency)) {
						cout << "INVALID CURRENCY\n";
						continue;
					}*/
				if (main_currency == "e") {
					leaver = true;
					break;
				}

				while (true) {
					cout << "Write your gmail->\n";
					cin >> gmail;
					if (gmail == "e") {
						leaver = true;
						break;
					}
					/*if (!check_gmail(gmail)) {
						cout << "INVALID GMAIL\n";
						continue;
					}*/
					if (dbcheck_gmail(gmail)) {
						cout << "ACCOUNT WITH THAT GMAIL ALREADY EXIST\n";
						continue;
					}
					else break;
				}
				if (login == "e") {
					leaver = true;
					break;
				}

				while (true) {
					cout << "Write your login->\n";
					cin >> login;
					if (login == "e") {
						leaver = true;
						break;
					}
					if (!check_login(login)) {
						cout << "INVALID LOGIN\n";
						continue;
					}
					if (dbcheck_login(md5(login))) {
						cout << "LOGIN ALREADY EXIST\n";
						continue;
					}
					else break;
				}
				if (login == "e") {
					leaver = true;
					break;
				}

				while (true) {
					cout << "Write your password->\n";
					cin >> password;
					if (password == "e") {
						leaver = true;
						break;
					}
					if (!check_pass(password)) {
						cout << "INVALID PASSWORD\n";
						continue;
					}
					else break;
				}
				if (password == "e") {
					leaver = true;
					break;
				}
				cout << "Write your question->\n";
				cin >> question;
				if (question == "e") {
					leaver = true;
					break;
				}

				cout << "Write your answer->\n";
				cin >> answer;
				if (answer == "e") {
					leaver = true;
					break;
				}
				break;
			}
			if (leaver) continue;
			cout << " ACCOUNT SUCCESSFULLY REGISTERED\n";
			Sleep(1000);
			login = md5(login); //хеш логіна
			password += login; //додавання солі
			password = md5(password); //хеш пароля
			answer += md5(question);
			answer = md5(answer);
			//запис в базу даних
			dbnew_user(USER_ID.takeup(), name, age, main_currency, login, gmail, password, question, answer);
			dbcreate_tables(dbtake_id(login));
			return;
		case(2): //Вхід

			system("CLS");
			cout << "e - to return\n\n";

			leaver = false;
			while (true) {
				cout << "Write your login->\n";
				cin >> login;
				if (login == "e") {
					leaver = true;
					break;
				}

				cout << "Write your password->\n";
				cin >> password;
				if (password == "e") {
					leaver = true;
					break;
				}
				login = md5(login);
				password += login;
				password = md5(password);

				//перевірка існування в базі даних логіну та пароля
				if (dbcheck_login(login) && dbtake_password(login) == password)
				{
					cout << "LOG IN SUCCESSFUL\n";
					dbselect_users(login, name, age, main_currency, gmail);
					//перенесення в клас
					
					run = false;
					leaver = true;
					Sleep(1000);
					break;
				} 
				else
				{
					cout << "LOG IN UNSUCCESSFUL\n";
					cout << "WRONG LOGIN OR PASSWORD\n";
					Sleep(1000);
				}


			}
			if (leaver) continue;
			return;
		case(3): //відновлення

			system("CLS");
			cout << "e - to return\n\n";

			leaver = false;
			while (true) {
				cout << "Write your login->\n";
				cin >> login;
				if (login == "e") {
					leaver = true;
					break;
				}
				//Перевірка чи є в базі
				login = md5(login);
				if (dbcheck_login(login)) {
					//витягуєм питання та відповідь з бази
					dbtake_sqsa(login, question, answer);
					while (true) {
						cout << question << "\n";
						cin >> u_answer;
						if (u_answer == "e") {
							leaver = true;
							break;
						}
						u_answer += md5(question);
						u_answer = md5(u_answer);
						if (answer == u_answer)
						{
							cout << "WELCOME\n";
							cout << "Write your new password->\n";
							cin >> password;
							if (password == "e") {
								leaver = true;
								break;
							}
							password += login;
							password = md5(password);
							//запис пароля в базу
							dbupdate_password(login, password);
							cout << "PASSWORD SUCCESSFULLY SAVED\n";
							leaver = true;
							Sleep(1000);
							break;
						}
						else
						{
							cout << "WRONG ANSWER\n";
						}
					}
					if (u_answer == "e") {
						leaver = true;
						break;
					}
				}
				else
				{
					cout << "WRONG LOGIN\n";
				}
			}
			if (leaver) continue;
			break;
		default:
			break;
		}
	}
}

int main()
{

	reg_init();

}