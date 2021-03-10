using namespace std;
#include <iostream>
#include<fstream>
#include<cstring>
#include <conio.h>
#include "windows.h"



struct user
{
	char login[20];
	char password[20];
	char card_number[16];
	bool show_flag = true;
	bool admin_rights= false;
	bool regular_customer = false;
    struct tour
    {
        int tour_number;
        int price;
        float discount;
    } tour;

};

struct tour
{
    int number;
    int price;

};

void Change(FILE* fil_1, char choice, user* user_in_file)
{
	if (choice == '1')
	{
		cout << "New name: " << endl;
		cin.getline(user_in_file->login, 20);
		fpos_t pos_i;
		int check = 0;
		fgetpos(fil_1, &pos_i);
		fseek(fil_1, 0, SEEK_SET);
		user user_in_file_2;
		while (!feof(fil_1))
		{
			fread(&user_in_file_2, sizeof(user), 1, fil_1);
			if (feof(fil_1))
				break;
			if (strcmp(user_in_file_2.login, user_in_file->login) == 0)
			{
				check++;
				break;
			}
		}
		if (check == 0)
		{
			pos_i = pos_i - sizeof(user);
			fsetpos(fil_1,&pos_i);
			fwrite(user_in_file, sizeof(user), 1, fil_1);
		}
		else cout << "This username is already in use!" << endl;
	}
	if (choice == '2')
	{
		cout << "New password: " << endl;
		cin.getline(user_in_file->password, 20);
		int size = 0 - sizeof(user);
		fseek(fil_1, size, SEEK_CUR);
		fwrite(user_in_file, sizeof(user), 1, fil_1);
	}
	if (choice == '3')
	{
		cout << "Choose new show-flag:" << endl;
		cout << "1.Show\n2.Do not show"<<endl;
			choice = _getch();
			if (choice == '1')
                user_in_file->show_flag = true;
			else if (choice == '2')
                user_in_file->show_flag = false;
		int size = 0 - sizeof(user);
		fseek(fil_1, size, SEEK_CUR);
		fwrite(user_in_file, sizeof(user), 1, fil_1);
	}
	if (choice == '4')
	{
		cout << "Choose either user can be admin or not: " << endl;
		cout << "1.Can\n2.Can not" << endl;
		choice = _getch();
		if (choice == '1')
            user_in_file->admin_rights = true;
		else if (choice == '2')
            user_in_file->admin_rights = false;
		int size = 0 - sizeof(user);
		fseek(fil_1, size, SEEK_CUR);
		fwrite(user_in_file, sizeof(user), 1, fil_1);
	}
};
void Find(FILE* fil_)
{
	char choice='1';
	user user_in_file;
	user usr_1;
	int count = 0;
	while (choice == '1') 
	{
		cout << "Find user with: " << endl;
		cout << "1.Their login\n2.Tour\n3.Showing flag\n4.Exit\n";

		choice = _getch();
		switch (choice)
		{
		case('1'):
			cout << "Enter login to find user: " << endl;
			cin.getline(usr_1.login, 20);
			fseek(fil_, 0, SEEK_SET);
			while (!feof(fil_))
			{
				fread(&user_in_file, sizeof(user), 1, fil_);
				if (feof(fil_))
					break;
				if (strcmp(usr_1.login, user_in_file.login) == 0)
				{
                    cout << "*-*-*-*-*-*-*-*-*-*-*-*" << endl;
					cout << "Login: "<<user_in_file.login << endl;
					cout << "Password: "<<user_in_file.password << endl;
					cout << "Showing flag: "<<user_in_file.show_flag << endl;
					cout << "Admin?: " << user_in_file.admin_rights << endl;
                    cout << "Tour: " << user_in_file.tour.tour_number << endl;
					cout << "Regular customer: " << user_in_file.regular_customer << endl;
                    cout << "Discount: " << user_in_file.tour.discount << endl;
					cout << "*-*-*-*-*-*-*-*-*-*-*-*" << endl;
					break;
				}
			}
			break;
		case('2'):
			cout << "Enter the number of the tour: " << endl;
			cin >> usr_1.tour.tour_number;
			fseek(fil_, 0, SEEK_SET);
			while (!feof(fil_))
			{
				fread(&user_in_file, sizeof(user), 1, fil_);
				if (feof(fil_))
					break;
				if (usr_1.tour.tour_number == user_in_file.tour.tour_number)
				{
                    cout << "*-*-*-*-*-*-*-*-*-*-*-*" << endl;
                    cout << "Login: "<<user_in_file.login << endl;
                    cout << "Password: "<<user_in_file.password << endl;
                    cout << "Showing flag: "<<user_in_file.show_flag << endl;
                    cout << "Admin?: " << user_in_file.admin_rights << endl;
                    cout << "Tour: " << user_in_file.tour.tour_number << endl;
                    cout << "Regular customer: " << user_in_file.regular_customer << endl;
                    cout << "Discount: " << user_in_file.tour.discount << endl;
                    cout << "*-*-*-*-*-*-*-*-*-*-*-*" << endl;
					count++;
				}
				if (count == 5)
				{
					system("pause");
					cout << "Do you want to keep searching?\n1.Yes\n2.No\n";
					choice = _getch();
					if (choice == '2')
						break;
					else if (choice == '1')
						count == 0;
				}
			}
			system("cls");
			if (count == 0)
			{
				cout << "No users were been found :(" << endl;
				system("pause");
			}
			break;
		case('3'):
			system("cls");

			cout << "Enter the show-flag of the user you want to find:\n1.Do not show\n2.Show" << endl;
			cin >> choice;
			if (choice == '1')
				usr_1.show_flag = false;
			else if (choice == '2')
				usr_1.show_flag = true;
			fseek(fil_, 0, SEEK_SET);
			while (!feof(fil_))
			{
				fread(&user_in_file, sizeof(user), 1, fil_);
				if (feof(fil_))
					break;
				if (usr_1.show_flag == user_in_file.show_flag)
				{
                    cout << "*-*-*-*-*-*-*-*-*-*-*-*" << endl;
                    cout << "Login: "<<user_in_file.login << endl;
                    cout << "Password: "<<user_in_file.password << endl;
                    cout << "Showing flag: "<<user_in_file.show_flag << endl;
                    cout << "Admin?: " << user_in_file.admin_rights << endl;
                    cout << "Tour: " << user_in_file.tour.tour_number << endl;
                    cout << "Regular customer: " << user_in_file.regular_customer << endl;
                    cout << "Discount: " << user_in_file.tour.discount << endl;
                    cout << "*-*-*-*-*-*-*-*-*-*-*-*" << endl;
					count++;
				}
				if (count == 5)
				{
					system("pause");
					cout << "Do you want to keep searching?1.Yes\n2.No\n";
					choice = _getch();
					if (choice == '2')
						break;
					else if (choice == '1')
						count == 0;
				}
			}
			system("pause");
			system("cls");
			if (count == 0)
			{
				cout << "No users were found :(" << endl;
				system("pause");
			}
			break;
		case('4'):
			system("cls");
			break;
		}
		system("pause");
		system("cls");
		cout << "Do you want to keep searching?\n1.Yes\n2.No\n";
		choice = _getch();
	}
	
}
void Admin_menu(FILE*fil_)
{
	system("cls");
	int counter = 1;
	FILE* fil_2;
	fopen_s(&fil_2, "users.txt", "r+b");
	char find_login[20];
	user user_in_file;
	while (counter == 1) {
		system("cls");
		cout << "_-_-_-_ADMIN MENU_-_-_-_" << endl;
		cout << "1.Change user" << endl;
		cout << "2.Delete user" << endl;
		cout << "3.Change tour/tours" << endl;
		cout << "4.Find user" << endl;
		cout << "Press ESC to exit" << endl;
		char choice;
		choice = _getch();
		int check = 0;
		switch (choice)
		{
		case('1'):
			system("cls");
			check = 0;
			cout << "Enter login of the user to change:" << endl;
			cin.getline(find_login, 20);
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
			
			fseek(fil_, 0, SEEK_SET);
			while (!feof(fil_))
			{
				fread(&user_in_file, sizeof(user), 1, fil_);
				if (feof(fil_))
					break;
				if (strcmp(find_login, user_in_file.login) == 0)
				{
					cout << "What do you want to change?"<< endl;
					cout << "1.Login: " << user_in_file.login << endl;
					cout << "2.Password: " << user_in_file.password << endl;
					cout << "3.Show-flag: " << user_in_file.show_flag << endl;
					cout << "4.Admin rights: " << user_in_file.admin_rights<<endl;
					choice = _getch();
					Change(fil_, choice, &user_in_file);
					break;
				}
			}
			
			break;
		case('2'):
			system("cls");
			check = 0;
			cout << "Enter login of the user you want to hide:" << endl;
			cin.getline(find_login, 20);
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
			
			fseek(fil_, 0, SEEK_SET);
            while (!feof(fil_))
			{
				fread(&user_in_file, sizeof(user), 1, fil_);
				if (feof(fil_))
					break;
				if (strcmp(find_login, user_in_file.login) == 0)
				{
					check++;
                    user_in_file.show_flag = false;
					int size = 0 - sizeof(user);
					fseek(fil_, size, SEEK_CUR);
					fwrite(&user_in_file, sizeof(user), 1, fil_);
					break;
				}
			}
			if (check == 0)
			{
				system("cls");
				cout << "User was not found :(" << endl;
			}
			break;
		case('3'):
			system("cls");
			choice = '0';
			cout << "1. Change price\n2. Change discount\nPress ESC to exit\n";
			choice = _getch();
			system("cls");
			if (choice == '1')
			{
				tour tour_1;
				tour filetour;
				cout << "Enter number of the tour: " << endl;
				cin >> tour_1.number;
				cout << "Enter price for tour: " << endl;
				cin >> tour_1.price;
				fseek(fil_2, 0, SEEK_SET);
				while (!feof(fil_2))
				{
					fread(&filetour, sizeof(tour), 1, fil_2);
					if (filetour.number == tour_1.number)
						break;
				}
				int size = 0 - sizeof(tour);
				fseek(fil_2, size, SEEK_CUR);
				fwrite(&tour_1, sizeof(tour), 1, fil_2);
			}
			if (choice == '2')
			{
				user usr_1;
				fseek(fil_2, 0, SEEK_END);
				cout << "Enter tour number: " << endl;
				cin>>usr_1.tour.tour_number;
				cout << "Enter discount: " << endl;
				cin >> usr_1.tour.discount;
				fwrite(&usr_1.tour, sizeof(user), 1, fil_2);
				choice = '0';
			}
			if (choice == '27')
				break;
			
				break;
		case('4'):
			Find(fil_);
			system("pause");
			break;
		case('27'):
			break;
		};
		system("cls");
		cout << "Do you want to return to menu for admins?\n1. Yes\n2. No" << endl;
		choice = _getch();
		if (choice == '1')
			counter = 1;
		else counter = 0;
	}
	fclose(fil_2);
	
}
void User_menu(user*user_in_file, FILE*fil_)
{

	system("cls");
	int counter = 1;
	FILE* fil_2;
	fopen_s(&fil_2, "tours.txt", "r+b");

	while (counter == 1) {
		system("cls");
		cout << "USER MENU" << endl;
		cout << "1.See tour list" << endl;
		cout << "2.Buy a tour" << endl;
		cout << "Press ESC to exit" << endl;
		char choice = _getch();
		int size = 0 - sizeof(user);
		switch (choice)
		{
		case('1'):
		    cout<<"1.Spain, price : 35 000 UAH"<<endl;
		    cout<<"2.Greece, price : 40 000 UAH"<<endl;
		    cout<<"3.Italy, price : 35 000 UAH"<<endl;
		case('2'):
			system("cls");
			choice = '0';
			while (choice - '0' < 1 || choice - '0' > 3) {
				cout << "Choose the tour you want to buy 1 - 3)" << endl;
				fseek(fil_2, 0, SEEK_SET);
				user usr_1;
				while (!feof(fil_2))
				{
					fread(&user_in_file, sizeof(user), 1, fil_2);
					if (feof(fil_2))
						break;
					cout << user_in_file->tour.tour_number << "Price=" << usr_1.tour.price << endl;
				}
				choice = _getch();
				if (choice - '0' < 1 && choice - '0' > 3)
					cout << "There is no tour for this number :(" << endl;
			}
			user_in_file->tour.tour_number = choice - '0';
			cout << "Enter your card number: " << endl;
			cin >> user_in_file->card_number;
			fseek(fil_, size, SEEK_CUR);
			fwrite(user_in_file, sizeof(user), 1, fil_);
			break;
		case ('27'):
			break;


		}
		cout << "Do you want to return to the user menu?\n1. Yes\n2. No" << endl;
		choice = _getch();
		counter = choice - '0';
	}
	fclose(fil_2);
}
void menu1(FILE *fil_)
{
	char admin_password[] = { "/\\"};
	int check = 0;
	user usr_1, user_in_file;
	cout << "1. Login \n2. Registrate\nPress ESC to exit" << endl;
	char choice;
	choice = _getch();
	switch(choice)
	{
	case ('1'):
		while (choice != 27) {
			cout << "Enter your login and password:" << endl;
			cout << "Login: ";
			cin.getline(usr_1.login, 20);
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
			
			cout << endl;
			cout << "Password: ";
			cin.getline(usr_1.password, 20);
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
			
			fseek(fil_, 0, SEEK_SET);
			while (!feof(fil_))
			{
				fread(&user_in_file, sizeof(user), 1, fil_);
				if (feof(fil_)) break;
				if (strcmp(user_in_file.login, usr_1.login) == 0)
				{
					check++;
					break;
				}
			}
			if (check != 0)
			{
				
				if (strcmp(user_in_file.password, usr_1.password) == 0)
				{
					system("cls");
					cout << "You have successfully logged in! :)" << endl;
					if (user_in_file.admin_rights == true)
					{
						Admin_menu(fil_);
					}
					else if (user_in_file.admin_rights == false)
					{
						User_menu(&user_in_file,fil_);
					}
					break;
				}
				else
				{
					system("cls");
					cout << "ERROR: passwords do not match\nPress Y to try again, Press ESC to exit" << endl;
					choice = _getch();
				}

			}
			else
			{
				system("cls");
				cout << "ERROR: user was not found\nPress Y to try again, Press ESC to exit" << endl;
				choice = _getch();
			}

		}
		break;

	case ('2'):
		
		while (choice != 27) 
		{
			
				system("cls");
				cout << "Enter your login and password:" << endl;
				cout << "Login: ";
				
				cin.getline(usr_1.login,20);
				if (cin.fail())
				{
					cin.clear();
					cin.ignore();
				}
				cout << endl;
			
			cout << "Password: ";
			cin.getline(usr_1.password, 20);
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
			}
			cout << endl;
			if (strcmp(admin_password,usr_1.password) == 0)
				usr_1.admin_rights = true;
			fseek(fil_, 0, SEEK_SET);
			
			while (!feof(fil_))
			{
				fread(&user_in_file, sizeof(user), 1, fil_);
				if (strcmp(user_in_file.login, usr_1.login) == 0)
				{
					cout << "ERROR: This user already exists" << endl;
					fseek(fil_, 0, SEEK_SET);
					check++;
					break;
				}

			}
			fpos_t posi;
			if (check == 0)
			{
				fseek(fil_, 0, SEEK_SET);
					while(!feof(fil_))
					{ 
						fread(&user_in_file, sizeof(user), 1, fil_);
						if (user_in_file.show_flag == false)
					    {
							int size = 0 -sizeof(user);
							fseek(fil_, size, SEEK_CUR);
							fwrite(&usr_1, sizeof(user), 1, fil_);
							check++;
							break;
					    }  
					}
					if (check == 0) 
					{
						fseek(fil_, 0, SEEK_END);
						fwrite(&usr_1, sizeof(user), 1, fil_);
					}
					check = 0;
				break;
			}
			else if (check != 0)
			{
				cout << "Press Y to try again, Press ESC to exit" << endl;
				choice = _getch();
			};

			
		}
		break;
	default:
		break;

	}
}

int main() {
	user fileperson;
	FILE* fil_;
	fopen_s(&fil_, "users.bin", "r+b");
	menu1(fil_);
	fpos_t pos_i;
	char choice;
	system("cls");
	cout << "Do you want to buy a tour?\n1. Yes\n2. No" << endl;
	choice = _getch();
	system("cls");
	if(choice=='1')
	User_menu(fil_);
	system("cls");
	fclose(fil_);
	return 0;
}