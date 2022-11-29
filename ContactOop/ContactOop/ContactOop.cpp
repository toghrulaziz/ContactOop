#include <iostream>
#include <fstream>
#include<stdio.h> 
#include <vector>

using namespace std;



//class Contact {}
//class DataBase {
//
//	AddContact() {} ++
//	DeleteByName() {} ++
//	SearchByName() {} ++ 
//}




class Contact {
	string name;
	string surname;
	string phoneNumber;
public:

	Contact() {}

	Contact(string name, string surname, string phoneNumber)
	{
		SetName(name);
		SetSurname(surname);
		SetPhoneNumber(phoneNumber);
	}

	void SetName(string name) {
		this->name = name;
	}

	void SetSurname(string surname) {
		this->surname = surname;
	}

	void SetPhoneNumber(string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}


	string GetName()const { return name; }
	string GetSurname()const { return surname; }
	string GetPhoneNumber()const { return phoneNumber; }

	friend class Database;
};



class Database : public Contact {
public:


	//////////////////////////////////////////////////////////////////////////////////////

	void AddContact(Contact contact) {
		ofstream phone("contacts.txt", ios::app);
		//ofstream phone("contacts.txt", ios::out);

		if (check_digits(contact.GetPhoneNumber()) == true) {
			if (check_numbers(contact.GetPhoneNumber()) == true) {
				if (phone.is_open()) {
					phone << contact.GetName() << " " << contact.GetSurname() << " "
						<< contact.GetPhoneNumber() << endl;
					cout << "\n\tContact saved successfully !";
				}
				else {
					throw "\n\tError in opening record!";
				}
			}
			else {
				throw "\n\tOnly numbers are allowed!";
			}
		}
		else {
			throw "\n\tPhone number should be of 10 digits "
				"only.";
		}

		cout << endl << endl;
		system("pause");
		system("cls");
		phone.close();

	}



	/////////////////////////////////////////////////////////////////////////////////////////


	void DeleteByName(string keyword) {
		vector<Contact> contact;

		ifstream phone("contacts.txt", ios::in);

		while (phone.is_open()) {

			string namef;
			string surnamef;
			string phoneNumberf;

			while (!phone.eof()) {

				phone >> namef;
				phone >> surnamef;
				phone >> phoneNumberf;

				Contact c = Contact(namef, surnamef, phoneNumberf);

				contact.push_back(c);
			}

			phone.close();
		}


		for (int i = 0; i < contact.size(); i++) {
			if (contact[i].name == keyword) {
				contact.erase(contact.begin() + i);
			}
		}


		ofstream phone1("contacts.txt", ios::out);
		if (phone1.is_open()) {
			for (int i = 0; i < contact.size(); i++) {
				phone1 << contact[i].name << " " << contact[i].surname << " " << contact[i].phoneNumber << endl;
			}
		}
		phone1.close();
	}





	//////////////////////////////////////////////////////////////////////////////////////////

	void SearchByName(string keyword)
	{
		bool found = false;
		ifstream phone("contacts.txt");
		while (phone >> name >> surname >> phoneNumber) {
			if (name == keyword) {
				system("cls");
				cout << "\n\n\n\t\tCONTACT DETAILS";
				cout << "\n\nFirst Name : " << name;
				cout << "\nLast Name : " << surname;
				cout << "\nPhone Number : " << phoneNumber;
				found = true;
				break;
			}
		}
		if (found == false)
			throw "\nNo such contact is found!";

		cout << endl << endl;
		system("pause");
		system("cls");
	}


	/////////////////////////////////////////////////////////////////////////////////////////


	bool check_digits(string number)
	{
		if (number.length() == 10)
			return true;
		else
			return false;
	}


	bool check_numbers(string number)
	{
		bool check = true;

		for (int i = 0; i < number.length(); i++) {
			if (!(int(number[i]) >= 48 && int(number[i]) <= 57)) {
				check = false;
				break;
			}
		}

		if (check == true)
			return true;

		if (check == false)
			return false;

		cout << endl << endl;
		system("pause");
		system("cls");
	}

};


void main() {


	Contact c1 = Contact("Toghrul", "Azizli", "0773780123");
	Contact c2 = Contact("Hakuna", "Matata", "0777777770");
	Contact c3 = Contact("Elon", "Musk", "0775555550");
	Database* d = new Database();


	try
	{
		//d->AddContact(c1);
		//d->AddContact(c2);
		//d->AddContact(c3);
		//d->SearchByName("Hakuna");
		//d->DeleteByName("Toghrul");
	}
	catch (const char* exception)
	{
		cout << exception;
	}

}