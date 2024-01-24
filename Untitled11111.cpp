#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <iomanip>

using namespace std;

//  start the class .  
class hotel
{
	
	int room_no;
	char name[30];
	int day;
	char phone[15];
	int bill;

public:
	void main_menu(); // to dispay the main menu
	void add();		  // to book a room
	void display();	  // to display the customer record
	void rooms();	  // to display alloted rooms

	int check(int); // to check room status

	void del(); // to delete the record
};

// displaying main menu.

void hotel::main_menu()
{
	int choice;
	while (choice != 5)
	{

		system("cls");
		cout << "\n\t\t\t\t*************************";
		cout << "\n\t\t\t\t SIMPLE HOTEL MANAGEMENT ";
		cout << "\n\t\t\t\t      * MAIN MENU *";
		cout << "\n\t\t\t\t*************************";
		cout << "\n\n\n\t\t\t1.Book A Room";
		cout << "\n\t\t\t2.Customer Records";
		cout << "\n\t\t\t3.Rooms Allotted";
		cout << "\n\t\t\t4.Delete Customer Record";
		cout << "\n\t\t\t5.Exit";
		cout << "\n\n\t\t\tEnter Your Choice: ";
		cin >> choice;

		switch (choice)
		{

		case 1:
			add();
			break;

		case 2:
			display();
			break;

		case 3:
			rooms();
			break;

		case 4:
			del();
			break;

		case 5:
			break;

		default:
		{
			cout << "\n\n\t\t\tWrong choice.....!!!";
			cout << "\n\t\t\tPress any key to   continue....!!";
			getch();
		}
		}
	}
}

// room booking function.

void hotel::add()
{

	system("cls");
	int r, flag;
	ofstream fout("Record.txt", ios::app);

	cout << "\n Enter Customer Detalis";
	cout << "\n ----------------------";
	cout << "\n\n Room no: ";
	cout << "\n Total no. of Rooms - 50";
	cout << "\n Ordinary Rooms from 1 - 30";
	cout << "\n Luxuary Rooms from 31 - 45";
	cout << "\n Royal Rooms from 46 - 50";
	cout << "\n Enter The Room no. you want to stay in :- ";
	cin >> r;
	cin.ignore();
	// For Bill
	int price;
	if (r >= 1 && r <= 30)
		price = 1500;
	else if (r >= 31 && r <= 45)
		price = 2000;
	else
		price = 5000;
	flag = check(r);

	if (flag)
		cout << "\n Sorry..!!!Room is already booked";

	else
	{

		room_no = r;
		cout << " Name: ";
		cin.getline(name, 30);
		cout << " Days to stay: ";
		cin >> day;
		cin.ignore();
		cout << " Phone No: ";
		cin.getline(phone, 15);
		cin.ignore();
		bill = day * price;

		fout.write((char *)this, sizeof(hotel));
		cout << "\n Room is booked...!!!";
	}

	cout << "\n Press any key to continue.....!!";

	getch();
	fout.close();
}

// checker function.

int hotel::check(int r)
{

	int flag = 0;

	ifstream fin("Record.txt", ios::in);
	fin.read((char *)this, sizeof(*this));
	while (!fin.eof())
	{

		fin.read((char *)this, sizeof(hotel));
		if (room_no == r)
		{

			flag = 1;
			break;
		}
	}

	fin.close();
	return (flag);
}

// display the alloted room.

void hotel::display()
{

	system("cls");

	ifstream fin("Record.txt", ios::in);
	int r, flag=0;

	cout << "\n Enter room no. for a particular customer`s details :- " << endl;
	cin >> r;
	fin.read((char *)this, sizeof(hotel));
	while (!fin.eof())
	{

		if (room_no == r)
		{

			system("cls");
			cout << "\n Cusromer Details";
			cout << "\n ----------------";
			cout << "\n\n Room no: " << room_no;
			cout << "\n Name: " << name;
			cout << "\n Stayed Days: " << day;
			cout << "\n Phone no: " << phone;
			cout << "\n Total Bill: " << bill;
			flag = 1;
			break;
		}

		fin.read((char *)this, sizeof(hotel));
	}

	if (flag == 0)
		cout << "\n Sorry Room no. not found or vacant....!!";

	cout << "\n\n Press any key to continue....!!";

	getch();
	fin.close();
}

// rooms details function.

void hotel::rooms()
{

	system("cls");

	ifstream fin("Record.txt", ios::in);
	cout << "\n\t\t\t    List Of Rooms Allotted";
	cout << "\n\t\t\t    ----------------------";
	cout << "\n\n "<< setw(20)<<"Room No."<< setw(20)<<"Name"<< setw(20)<<"Stayed Days"<< setw(20)<<"Phone No."<< setw(20)<<" Total Bill";
	fin.read((char *)this, sizeof(hotel));
	while (!fin.eof())
	{
        cout << "\n\n "<< setw(20)<<room_no<< setw(20)<<name<< setw(20)<<day<< setw(20)<<phone<< setw(20)<<bill;
		// cout << "\n\n " << room_no << "\t\t" << name;
		// cout << "\t\t" << day << "\t\t" << phone << "\t\t" << bill;
		fin.read((char *)this, sizeof(hotel));
	}

	cout << "\n\n\n\t\t\tPress any key to continue.....!!";
	getch();
	fin.close();
}

void hotel::del()
{
	system("cls");
	int r;
	cout << "\n\n\t\t\t\t Customer Record Deletion ";
	cout << "\n\n\t Enter Room No. : ";
	cin >> r;
	int flag = 0;
	char ch;
	ifstream fin("Record.txt", ios::in);
	ofstream fout("temp.txt", ios::out);
	fin.read((char *)this, sizeof(hotel));
	while (!fin.eof())
	{

		if (room_no == r)

		{

			cout << "\n Name: " << name;
			cout << "\n Stayed Days " << day;
			cout << "\n Phone No: " << phone;
			cout << "\n Total bill: " << bill;
			cout << "\n\n Do you want to delete this record(y/n): ";
			cin >> ch;

			flag = 1;
			if (ch == 'n')
			{

				fout.write((char *)this, sizeof(hotel));
			}
			else
				cout << "Record Deleted Successfully...\n\n";
		}

		else
			fout.write((char *)this, sizeof(hotel));

		fin.read((char *)this, sizeof(hotel));
	}

	fin.close();
	fout.close();

	if (flag == 0)
		cout << "\n Sorry room no. not found or vacant...!!";

	else
	{

		remove("Record.txt");
		rename("temp.txt", "Record.txt");
	}

	cout << "\t press any key to continue ....";
	getche();
}

// main function of our project.

int main()
{

	hotel h;

	system("cls");
	cout << "\n\n";
	cout << "\n\t\t\t\t\t\t\t\t****************************";
	cout << "\n\t\t\t\t\t\t\t\t* HOTEL MANAGEMENT PROJECT *";
	cout << "\n\t\t\t\t\t\t\t\t****************************";
	cout << "\n\n\t\tDeveloped By:  HUNTERS GROUP" << endl;
	cout << "\n\t\t =>Afif " << endl;
	cout << "\t\t =>AbdulRehman " << endl;
	cout << "\t\t =>Ali Hamza " << endl;
	cout << "\t\t =>Awais " << endl;
	cout << "\n\n\n\n\t\t\t\t\t\t\t\t DEPARTMENT OF COMPUTER SCIENCE ";
	cout << "\n\n\t\t\t\t\t\t\t   GOVERNMENT COLLEGE UNIVERSITY FAISALABAD. ";

	cout << "\n\n\n\n\n\t\t\t\tPress any key to continue....!!";

	getch();

	h.main_menu();
	return 0;
}

