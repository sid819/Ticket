#include <iostream> 
#include <fstream>
//#include <stdlib.h>
#include <string>
//#include <conio.h>
#include <stdio.h>
using namespace std;
bool login(bool);
void registr();


class TourBus
{
	
	
public:
	string destination;
	int bid;
	string time;
	int max_seats;

	int fare;
	int booked;
	
	TourBus()
	{
		bid = 0;
		max_seats = 50;
		booked = 0;
		fare = 0;
		time = "";
		destination = "";
	}
	void input();
	void show();
	void display();
	int getid()
	{
		return bid;
	}
	void book()
	{
		booked++;
	}
	string getDestination()
	{
		return destination;
	}
	string getTime()
	{
		return time;
	}
	int getBooked() {
		return booked;
	}
	int getMax() {
		return max_seats;
	}
	int getFare()
	{
		return fare;
	}
};


class Ticket
{
	string name;
	TourBus bus;
public:

	void generate(string cname, TourBus tb)
	{
		name=cname;
		bus = tb;
	}
	void display()
	{
		cout << "Customer Name " << name << endl;
		cout << "Details of Bus " << endl;
		bus.show();
	}
};
void TourBus::input() //CASE 1 ADD NEW BUS
{
	cout << "Enter bus id ";
	cin >> bid;
	cout << "Enter bus destination ";
	cin>>destination;
	cout << "Enter time of bus ";
	cin >> time;
	cout << "Enter fare of the bus ";
	cin >> fare;
}
void TourBus::display()// CASE 3 DISPLAY ALL BUSES
{
	cout << bid << "\t" << destination << "\t" << time << "\t" << max_seats << "\t" << booked << "\t" << fare << "\n";
}
void TourBus::show() // CASE 2 AND 6
{
	cout << "Bus Id " << bid << endl;
	cout << "Desination " << destination << endl;
	cout << "Time " << time << endl;
	cout << "No. of seats remaining " << max_seats - booked << endl;
	cout << "\n";
}



int main()
{
    bool z = false;
    bool lin = false;
	int choice;
	cout << "****************** LOGIN ******************\n";
	cout << "1. Login";
	cout << "\n2. Register";
	cout << "\nEnter your choice";
	cin >> choice;

	switch (choice)
	{
	case 1:
		z =login(lin);
		break;
	case 2:
		registr();
		break;
	
	default:
		cout << "Wrong Choice"; 
		main();
			
	}
    if (z == true)
    {
		system("cls");
		int ch;
		fstream F, G;
		TourBus b;

		do
		{
			system("cls");
			cout << "Press 1 - Add a New Tour Bus" << endl;
			cout << "Press 2 - Show Selected Bus" << endl;
			cout << "Press 3 - Display All Buses" << endl;
			cout << "Press 4 - Delete a Bus" << endl;
			cout << "Press 5 - Book a ticket " << endl;
			cout << "Press 6 - Display Booked Tickets " << endl;
			cout << "Press 7 - Exit " << endl;
			cout << "Enter your choice ";
			cin >> ch;
			switch (ch)
			{
			case 1:
			{
				F.open("tour.dat", ios::app | ios::binary);
				b.input();
				F.write((char*)&b, sizeof(b));
				F.close();
				cout << "Bus added Successfully " << endl;
				cin.get();
				cin.get();
				system("cls");

				break;
			}
			case 2:
			{
				int id, chk = 0;
				cout << "Enter the bus id to be displayed ";
				cin >> id;
				F.open("tour.dat", ios::in | ios::binary);
				if (F.fail())
					cout << "Can't open file " << endl;
				else
				{
					while (F.read((char*)&b, sizeof(b)))
					{
						if (b.getid() == id)
						{
							b.show();
							chk = 1;
							break;
						}
					}
					if (chk == 0)
						cout << "Bus not Found" << endl;
				}
				F.close();
				cin.get();
				cin.get();
				break;
			}


			case 3:
			{
				F.open("tour.dat", ios::in | ios::binary);
				if (F.fail())
					cout << "Can't open file " << endl;
				else
				{
					while (F.read((char*)&b, sizeof(b)))
						b.display();
				}
				F.close();
				cout << "Press a key to continue ";
				cin.get();
				cin.get();
				system("cls");
				break;
			}
			case 4:
			{
				int chk = 0, id;
				cout << "Enter the bus id to be deleted ";
				cin >> id;
				F.open("tour.dat", ios::in | ios::binary);
				G.open("temp.dat", ios::out | ios::binary);
				if (F.fail())
					cout << "Can't open file " << endl;
				else
				{
					while (F.read((char*)&b, sizeof(b)))
					{
						if (b.getid() != id)
						{
							G.write((char*)&b, sizeof(b));
						}
						else
						{
							b.show();
							chk = 1;

						}
					}
					if (chk == 0)
					{
						cout << "Bus not Found" << endl;
						cin.get();
						cin.get();
					}

					else
					{
						cout << "Bus Deleted " << endl;
						cin.get();
						cin.get();
					}
				}
				F.close();
				G.close();
				remove("tour.dat");
				rename("temp.dat", "tour.dat");
				break;
			}
			case 5:
			{
				string dest, cname;
				int chk =0;
				Ticket t;
				cout << "Enter the destination ";
				cin >> dest;
				F.open("tour.dat", ios::in | ios::out | ios::binary);
				if (F.fail())
					cout << "Can't open file " << endl;
				else
				{
					while (F.read((char*)&b, sizeof(b)))
					{
						if (b.getDestination() == dest)
						{
							b.show();
							chk = 1;
							cout << "Enter the customer name ";
							cin >> cname;
							
							t.generate(cname, b);
							G.open("tickets.dat", ios::app | ios::binary);
							G.write((char*)&t, sizeof(t));
							G.close();
							int c = sizeof(b); //size of a single entry
							int j = F.tellg(); // currently where the get pointer is pointing
							F.seekp(j-c, ios::beg);
							b.book();
							F.write((char*)&b, sizeof(b));
							cout << "Ticket booked" << endl;
							cin.get();
							cin.get();
							break;
						}
					}
					if (chk == 0)
					{
						cout << "No Bus Found" << endl;
						cin.get();
						cin.get();
					}
					
				}
				F.close();
				break;
			}
			case 6:
			{
				Ticket t;
				cout << "Booked Tickets " << endl;
				G.open("tickets.dat", ios::in | ios::binary);
				if (G.fail())
					cout << "can't open file " << endl;
				else
				{
					while (G.read((char*)&t, sizeof(t)))
						t.display();
				}

				G.close();
				cout << "Press a key to continue ";
				cin.get();
				cin.get();
				break;

			}
			case 7:
			{
				cout << " Exiting Program";
				exit(0);

			}
			default: {cout << "Wrong choice, please try again";
				break; }

			}
		} while (ch != 8);


    }
	return 0;
}

//Registration
void registr ()
{
    int c = 0;
    string reguser, regpass, su;
	system("cls");
	cout << "Enter your username : ";
	cin >> reguser;
	cout << "Enter your password : ";
	cin >> regpass;

    ifstream searchu("database.txt");
    while (searchu >>su)
    {
        if (su == reguser)
        {
            c = 1;
        }
    }
    searchu.close();
    if (c == 1)
    {
        cout << "\n\nSorry! the username already exists, Pls try another one\n";
        
        cin.get();
        cin.get();
        system("cls");
        main();
    }

    else
    {
        ofstream reg("database.txt", ios::app);
        reg << reguser << ' ' << regpass << endl;
        system("cls");
        cout << "\nRegistration Sucessful\n";
        main();
    }


}
//Login
bool login(bool lin)
{   
    bool a = lin;
    int count = 0;
    string user, pass, u, p;
    system("cls");
    cout << "please enter the following details" << endl;
    cout << "USERNAME :";
    cin >> user;
    cout << "PASSWORD :";
    cin >> pass;

    ifstream input("database.txt");
    while (input >> u >> p)
    {
        if (u == user && p == pass)

        {
            count = 1;
            system("cls");
        }
    }
    input.close();
    if (count == 1)
    {
        a = true;
        cout << "\nHello  " << user << "\nLOGIN SUCESS\nWe're glad that you're here.\nThanks for logging in\n";
        
        cin.get();
        cin.get();
		return a;
        main();
    }
    else
    {
        a = false;
        cout << "\nLOGIN ERROR\nPlease check your username and password\n";
        return a;
        main();
    }
}

