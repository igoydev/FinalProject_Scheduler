#ifndef Index_h
#define Index_h

#include<iostream>
#include<fstream>//for file manipulation
#include<stdlib.h>//for clear screen, exit
#include<iomanip>//for whitespace etc
#include<vector>//for vector operation
#include<string>//for string operation
#include<sstream>//for string breakdown
#include<algorithm>//for sorting
using namespace std;

vector<string> date;
vector<string> hours;
vector<string> activity;
vector<int> trans_amount, trans_total;
string username, password, temp_date, temp_hours, temp_activity, line;

void load();
void save();
void header();
void login();
void menu();
void dashboard();
void editSchedule();
void add_schedule();
void matchSchedule();


void load() {
    
    ifstream myFile("Schedule.txt");
    if (!myFile.is_open()) {
        cout << "Database is not found" << endl;
        exit(0);
    }
    
   
    //load data
    date.clear();
    hours.clear();
    activity.clear();
    
    while (getline(myFile, line)) {
        stringstream ss(line);
        getline(ss, temp_date, ',');
        date.push_back(temp_date);
        getline(ss, temp_hours, ',');
        hours.push_back(temp_hours);
        getline(ss, temp_activity, ',');
        activity.push_back(temp_activity);
        
    }
    
    
    myFile.close();
    
}

void header()
{
    cout << "==========================================\n";
    cout << "||           PERSONAL SCHEDULER         ||\n";
    cout << "==========================================\n";
}

void menu() {
    header();
    char choice;
    cout << "Welcome to your Personal Scheduler\n";
    cout << "Select program: \n1. Dashboard\n2. Edit Schedule\n3. Schedule Matcher\n\n";
    cout << "Your Choice (1-2) [E/e for exit]: ";
    cin >> choice;
    switch (choice) {
    case'1':
        dashboard();
    case'2':
        add_schedule();
    case'3':
        matchSchedule();
    case 'E':
        exit(0);
    case 'e':
        exit(0);
    default:
        system("CLS");
        menu();
    }
}

void dashboard()
{
    char choice;
    time_t ttime = time(0);
    char* dt = ctime(&ttime);
    
    cout << "==========================================\n";
    cout << "         Welcome to your Dashboard         " <<endl;
    cout << "==========================================\n";
    

    cout << "Today is : " << dt <<endl<<endl;
    
    
    cout << setw(4) << left << "No " << setw(17) << left << "|Date" << "|Hours" << setw(21) << "|Activity" <<"|" << endl;
    
    
    for (int i = 0; i < date.size(); i++) {
        cout << setw(3) << right << i + 1 << ".|" << setw(9) << left << date[i] << "|" << setw(5) << left << hours[i] << "|" << setw(20)<< activity[i] << "|" << endl;
    }
    
    cout << "\nB/b: Back\nE/e: Exit\nYour choice: ";
    cin >> choice;
    if (choice == 'B' || choice == 'b') {
        menu();
    }else if(choice == 'E' || choice == 'e'){
        exit(0);
    }else {
        header();
        dashboard();
    }
    
    
}

void login()
{
    header();
    int tries = 0;
    string input_username, input_password;
    
    do {
        cout << "Please login to proceed\n";
        cout << "Username = "; cin >> input_username;
        cout << "Password = "; cin >> input_password;
        if (input_username == "admin" && input_password == "administrator") {
            menu();
        }
        else {
            header();
            cout << "Wrong Username/Password! (" << tries + 1 << " tries)\n";
            tries++;
        }
    } while (tries < 3);
    cout << "\nYou have tried 3 times.\n";
    cout << "Please contact the IT admsin to reset your username/password.\n\n";
}

void editSchedule()
{
    cout << "==========================================\n";
    cout << "||              EDIT SCHEDULE           ||\n";
    cout << "==========================================\n";
}

void add_schedule() {
    string new_date, new_hours, new_activity;
    header();
    cin.ignore();
    cout << "Date (DD/MM/YYYY): ";
    getline(cin, new_date);
    cout << new_date << " Time: ";
    getline(cin, new_hours);
    cout << new_hours << " Activity: ";
    getline(cin, new_activity);
    date.push_back(new_date);
    hours.push_back(new_hours);
    activity.push_back(new_activity);
    ofstream myFile("Schedule.txt",ios::app);
    myFile << "\n" << new_date << "," << new_hours << "," << new_activity;
    myFile.close();
    dashboard();
}

void matchSchedule()
{
    
}

#endif /* Index_h */
