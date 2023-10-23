#include <mysql.h>
#include <iostream>
#include "user.cpp"
#include "message.cpp"
//#include "make_tab_db.cpp"
#include <vector>
#include <string>
using namespace std;
MYSQL mysql;
MYSQL_RES* res;
MYSQL_ROW row;

void makeDBase() // make db base for example 
	{

// �������� ���������� ����������
mysql_init(&mysql);
if (&mysql == nullptr) {
	// ���� ���������� �� ������� � ������� ��������� �� ������
	cout << "Error: can't create MySQL-descriptor" << endl;
}

// ������������ � �������
if (!mysql_real_connect(&mysql, "localhost", "root", "root", "testdb2", NULL, NULL, 0)) {
	// ���� ��� ����������� ���������� ���������� � �� ������� ��������� �� ������
	cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
}

mysql_query(&mysql, "CREATE TABLE table_user(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), login VARCHAR(255), pass VARCHAR(255))");
mysql_query(&mysql, "INSERT INTO table_user(id, name, login, pass) values(default, 'Daria', 'daria', '0')");
mysql_query(&mysql, "INSERT INTO table_user(id, name, login , pass) values(default, 'Lida','lida', '0')");
mysql_query(&mysql, "INSERT INTO table_user(id, name, login, pass) values(default, 'Nastya', 'nastya', '0')");
mysql_query(&mysql, "INSERT INTO table_user(id, name, login, pass) values(default, 'login', 'login', 'pass')");

mysql_query(&mysql, "CREATE TABLE table_message(id INT AUTO_INCREMENT PRIMARY KEY, from_user VARCHAR(255), to_user VARCHAR(255), text_message VARCHAR(255))");
mysql_query(&mysql, "INSERT INTO table_message(id, from_user, to_user, text_message) values(default, 'Daria', 'Lida', '������!')");
mysql_query(&mysql, "INSERT INTO table_message(id, from_user, to_user, text_message) values(default, 'Lida', 'Daria', '����!')");
mysql_query(&mysql, "INSERT INTO table_message(id, from_user, to_user, text_message) values(default, 'Nastya', 'Daria', 'How are you?')");

mysql_query(&mysql, "SELECT * FROM table_user "); //������ ������ � ������� user ���� username
//������� ��� ��� ���� � ������� ����� ����

unsigned j = 0;
if (res = mysql_store_result(&mysql))
  {
	while (row = mysql_fetch_row(res)) 
	{
		for (j = 0; j < mysql_num_fields(res); j++) 
		{
			cout << row[j] << "  ";
		}
		cout << endl;
	}
  }
else
cout << "������ MySql ����� " << mysql_error(&mysql);

mysql_query(&mysql, "SELECT * FROM table_message"); //������ ������ � ������� message
//������� ��� ��� ���� � ������� ����� ����
if (res = mysql_store_result(&mysql)) 
  {
	while (row = mysql_fetch_row(res))  {
		for (j = 0; j < mysql_num_fields(res); j++)
		{
			cout << row[j] << "  ";
		}
		cout << endl;
										 }
  }
else
cout << "������ MySql ����� " << mysql_error(&mysql);
//	delete res; // ������� ������
	//delete row;
		// ��������� ���������� � ����� ������
mysql_close(&mysql);
}
	
	


int main() {
	
	setlocale(LC_ALL, "");
	bool  user_present=false;
	bool user_pass_ok = false;
	cout << "Need to make DB for example (y) yes or No? " << endl;
	string Choise_mDB;
	cin >> Choise_mDB;
	cout<< endl;
	if (Choise_mDB == "y" || Choise_mDB == "Y")
	 {
		makeDBase();
		cout << " Greating Db is ok";

	 }
		unsigned i = 0;
// ��������� � ���� ��� ������
	
	mysql_init(&mysql); // �������� ���������� ����������
	if (&mysql == nullptr) {
		// ���� ���������� �� ������� � ������� ��������� �� ������
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// ������������ � �������
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "testdb2", NULL, NULL, 0)) {
		// ���� ��� ����������� ���������� ���������� � �� ������� ��������� �� ������
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	else {
		// ���� ���������� ������� ����������� ������� ����� � "Success!"
		cout << "Success!" << endl;
	}

	mysql_set_character_set(&mysql, "utf8");
	//������� ���������� �� ��������� �� ������, �� ��������� ��� latin1
	cout << "connection characterset: " << mysql_character_set_name(&mysql) << endl;
	cout << "Input you login: " ;
	string user_login;
	cin >> user_login;
	// for test user_login = "daria";
	cout << endl;
	cout << "Input you pass: " ;
	string user_pass;
	cin >> user_pass;
    cout << endl;
	//for test user_pass = "0";
	vector<std::string>userlogs;
	vector<std::string>userpass;
	mysql_query(&mysql, "SELECT login , pass FROM table_user  "); //������ ������ � ������� user ��������� ���� �������������
	
	//������� ��� ��� ���� � ���� ����� ����
	if (res = mysql_store_result(&mysql))
	{
		while (row = mysql_fetch_row(res))
		{
					
			for (i = 0; i < mysql_num_fields(res); i++) {
				if (i == 0)
				{
					userlogs.push_back(row[i]);
				}
				
				if (i == 1)
				{
					userpass.push_back(row[i]);
				}
			                                            }
			cout << endl;
		}
	}
	else
	{
		cout << "������ MySql ����� " << mysql_error(&mysql);
	}
	for (auto k: userlogs) {
		
		if (k == user_login.c_str()) {
			
			user_present = true;
							 }
	                       };
	for (auto k : userpass) {

		if (k == user_pass.c_str()) {

			user_pass_ok = true;
		}
	};
	if (user_present && user_pass_ok)
	{
		string text = string("SELECT from_user, to_user, text_message FROM table_message " + string("WHERE to_user = '") + user_login.c_str() + "'");
		mysql_query(&mysql, text.c_str()); //������ ������ � ������� message ��� ���� ������������ � ��� ���������

		//������� ��� ��� ���� � ���� ����� ����
		if (res = mysql_store_result(&mysql)) {
			while (row = mysql_fetch_row(res)) { // ����
				for (i = 0; i < mysql_num_fields(res); i++) { // ������

					{ cout << row[i] << "  "; }
				}
				cout << endl;
			}
		}
		else
			cout << "������ MySql ����� " << mysql_error(&mysql);
	}
	else {
		cout << "Pass/Login incorrect!" << endl;
	};
	
	// ������������ ��������
	//delete res;
//	delete row;
	mysql_close(&mysql); // ��������� ���������� � �������� ���� ������

	system("Pause");

	return 0;
}
