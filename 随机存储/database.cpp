#include <iostream>
#include "student.h"
#include "personal.h"
#include "database.h"
template<class T>
Database<T>::Database()
{
}
template<class T>
void Database<T>::add(T& d)
{
	database.open(fName, ios::in | ios::out | ios::binary);//创建文件并读和取
	database.seekp(0, ios::end);  //写指针放到末尾
	d.writeToFile(database);
	database.close();
}
template<class T>
void Database<T>::modify(const T& d)
{
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	while (!database.eof())
	{
		tmp.readFromFile(database);
		if (tmp == d) {// overloaded==
			cin >> tmp;//overloaded>>
			database.seekp(-d.size(), ios::cur);
			tmp.writeToFile(database);
			database.close();
			return;
		
		
		}

	}
	database.close();
	cout << "not in the database\n";
}
template<class T>
bool Database<T>::find(const T& d)
{
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	while (!database.eof())
	{
		tmp.readFromFile(database);
		if (tmp==d){// overloaded==
			database.close();
			return true;

		}
	}
	database.close();
	return false;
}
template<class T>
ostream& Database<T>::print(ostream& out)
{
	T tmp;
	database.open(fName, ios::in | ios::out | ios::binary);
	while (true) {
		tmp.readFromFile(database);
		if (database.eof())
		{
			break;
		}
		out<<tmp<<endl;
	}
	database.close();
	return out;
}
template<class T>
void Database<T>::run()
{
	cout << "File name:";
		cin >> fName;
	char option[5];
	T rec;
	cout << "1.Add 2.Find 3.Modify a record 4.Exit\n";
cout << "Enter an option: ";
	cin.getline(option, 4);
	while (cin.getline(option, 4))
	{
		if (*option == '1') {
			cin >> rec;
			add(rec);
		}
		else if (*option == '2')
		{
			rec.readKey();
			cout << "The record is";
			if (find(rec) == false)
			{
				cout << "not";
			}
			cout << "in the database\n";
		}
		else if (*option == '3')
		{
			rec.readKey();
			modify(rec);
		}
		else if (*option != '4')
		{
			cout << "wrong option\n";
		}
		else return;
		cout << *this;
		cout << "Enter an option";
	
	}
}
int main()
{
	Database<Personal>().run();
	//Database<Student>().run();
	return 0;
}