#ifndef Index_h
#define Index_h

#include <iostream>
#include <fstream>   //for file manipulation
#include <stdlib.h>  //for clear screen, exit
#include <iomanip>   //for whitespace etc
#include <vector>    //for vector operation
#include <string>    //for string operation
#include <sstream>   //for string breakdown
#include <algorithm> //for sorting
using namespace std;

vector<string> date;
vector<double> hours;
vector<double> hoursEnd;
vector<string> name;
vector<string> activity;
vector<int> trans_amount, trans_total;
string username, password, temp_date, temp_hours, temp_end, temp_name, temp_activity, line;

void load();
void save();
void header();
void login();
void menu();
void dashboard();
void editSchedule();
void add_schedule();
void matchSchedule();

void save()
{
    ofstream myFile("Schedule.txt", ios::trunc);

    for (int i = 0; i < date.size(); i++)
    {
        myFile << "\n"
               << date[i] << "," << hours[i] << "," << activity[i];
    }
    myFile.close();
}

void load()
{

    ifstream myFile("Schedule.txt");
    if (!myFile.is_open())
    {
        cout << "Database is not found" << endl;
        exit(0);
    }

    // load data
    name.clear();
    date.clear();
    hours.clear();
    hoursEnd.clear();
    activity.clear();

    // while (getline(myFile, line)) {
    //     stringstream ss(line);
    //     getline(ss, temp_date, ',');
    //     date.push_back(temp_date);
    //     getline(ss, temp_hours, ',');
    //     hours.push_back(stof(temp_hours));
    //     getline(ss, temp_activity, ',');
    //     activity.push_back(temp_activity);
    // }

    while (!myFile.eof())
    {
        getline(myFile, temp_name, ',');
        name.push_back(temp_name);
        getline(myFile, temp_date, ',');
        date.push_back(temp_date);
        getline(myFile, temp_hours, ',');
        hours.push_back(stof(temp_hours));
        getline(myFile, temp_end, ',');
        hoursEnd.push_back(stof(temp_end));
        getline(myFile, temp_activity, '\n');
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

void menu()
{
    header();
    char choice;
    cout << "Welcome to your Personal Scheduler\n";
    cout << "Select program: \n1. Dashboard\n2. Edit Schedule\n3. Schedule Matcher\n\n";
    cout << "Your Choice (1-2) [E/e for exit]: ";
    cin >> choice;
    switch (choice)
    {
    case '1':
        dashboard();
    case '2':
        editSchedule();
    case '3':
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
    char *dt = ctime(&ttime);

    cout << "==========================================\n";
    cout << "         Welcome to your Dashboard         " << endl;
    cout << "==========================================\n";

    cout << "Today is : " << dt << endl
         << endl;

    cout << setw(4) << left << "No " << setw(17) << left << "|Name" << setw(15) << left << "|Date"
         << "|Start" << setw(6) << "|End" << setw(21) << "|Activity"
         << "|" << endl;

    for (int i = 0; i < date.size(); i++)
    {
        cout << setw(3) << right << i + 1 << ".|" << setw(16) << left << name[i] << "|" << setw(14) << left << date[i] << "|" << setw(5) << left << hours[i] << "|" << setw(5) << left << hoursEnd[i] << "|" << setw(20) << activity[i] << "|" << endl;
    }

    cout << "\nB/b: Back\nE/e: Exit\nYour choice: ";
    cin >> choice;
    if (choice == 'B' || choice == 'b')
    {
        menu();
    }
    else if (choice == 'E' || choice == 'e')
    {
        exit(0);
    }
    else
    {
        header();
        dashboard();
    }
}

void login()
{
    header();
    int tries = 0;
    string input_username, input_password;

    do
    {
        cout << "Please login to proceed\n";
        cout << "Username = ";
        cin >> input_username;
        cout << "Password = ";
        cin >> input_password;
        if (input_username == "admin" && input_password == "admin")
        {
            menu();
        }
        else
        {
            header();
            cout << "Wrong Username/Password! (" << tries + 1 << " tries)\n";
            tries++;
        }
    } while (tries < 3);
    cout << "\nYou have tried 3 times.\n";
    cout << "Please contact the IT admin to reset your username/password.\n\n";
}

void editSchedule()
{
    int choice;
    char choice2;
    string input;
beginning:

    header();
    cout << setw(4) << left << "No " << setw(12) << left << "|Date"
         << "|Hours" << setw(17) << "|Activity"
         << "|" << endl;
    for (int i = 0; i < date.size(); i++)
    {
        cout << setw(3) << right << i + 1 << ".|" << setw(11) << left << date[i] << "|" << setw(5) << left << hours[i] << "|" << setw(16) << activity[i] << "|" << endl;
    }
    cout << "Select item number (1-" << date.size() << "): ";
    cin >> choice;
    choice--;

invalid:
    cout << setw(3) << right << choice + 1 << ".|" << setw(22) << left << date[choice] << "|" << setw(5) << right << hours[choice] << "|" << setw(7) << activity[choice] << "|" << endl;
    cout << "\nWhat do you want to edit? \nN/n Name\nP/p Price\nS/s stock\nD/d Delete item\nB/b Back\nYour choice: ";
    cin >> choice2;
    if (choice2 == 'N' || choice2 == 'n')
    {
        cout << "\nEnter new date (DD/MM/YYYY): ";
        cin.ignore();
        getline(cin, date[choice]);
    }
    else if (choice2 == 'P' || choice2 == 'p')
    {
        cout << "\nEnter new time: ";
        cin >> input;
        hours[choice] = stof(input);
    }
    else if (choice2 == 'S' || choice2 == 's')
    {
        cout << "\nEnter new activity: ";
        cin >> input;
        activity[choice] = input;
    }
    else if (choice2 == 'D' || choice2 == 'd')
    {
        date.erase(date.begin() + choice);
        hours.erase(hours.begin() + choice);
        activity.erase(activity.begin() + choice);
    }
    else if (choice2 == 'B' || choice2 == 'b')
    {
        save();
        menu();
    }
    // go back
    else
    {
        system("CLS");
        header();
        goto invalid;
    }
    goto beginning;
}

void add_schedule()
{
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
    hours.push_back(stof(new_hours));
    activity.push_back(new_activity);
    ofstream myFile("Schedule.txt", ios::app);
    myFile << "\n"
           << new_date << "," << new_hours << "," << new_activity;
    myFile.close();
    dashboard();
}

void matchSchedule()
{
    struct schedule_request
    {
        string nameReq, dateReq;
        double hoursReqS;
    };

    schedule_request listReq;

    cout << "Mau janji sama siapa nih?" << endl;
    cin >> listReq.nameReq;
    cout << endl;

    cout << "Mau tanggal berapa? (DD/MM/YYYY)" << endl;
    cin >> listReq.dateReq;
    cout << endl;

    cout << "Mau mulai jam berapaa?" << endl;
    cin >> listReq.hoursReqS;
    cout << endl;

    for (int i = 0; i < date.size(); i++)
    {
        if (listReq.nameReq == name[i])
        {
            if (listReq.dateReq == date[i])
            {
                if (listReq.hoursReqS < hours[i])
                {
                    cout
                        << "Bisa nih bikin janji jam segini tapi dia ada acara lagi dari jam "
                        << hours[i] << " sampai " << hoursEnd[i] << " yaaa" << endl;
                    break;
                }
                else if (listReq.hoursReqS > hoursEnd[i])
                {
                    if (listReq.hoursReqS > hours[i + 1] && listReq.hoursReqS < hours[i + 1])
                    {
                        cout << "Yah:( dia lagi gak bisa nih kalo jam segituu" << endl;
                    }
                    // if (i == date.size() - 1){
                    //     cout << "Bisa nih bikin janji jam segini" << endl;
                    //     break;
                    // } else {
                    //     cout << "Bisa nih bikin janji jam segini tapi "
                    //     << listReq.nameReq << " ada janji lain di jam "
                    //     << hours[i + 1] << endl;
                    //     break;
                    // }
                    if (i == date.size() - 1)
                    {
                        cout << "Kosong terus" << endl;
                        break;
                    }
                    else
                    {
                        if (listReq.hoursReqS < hours[i + 1])
                        {
                            cout
                                << "Bisa nih bikin janji jam segini tapi dia ada acara lagi dari jam "
                                << hours[i + 1] << " yaaa" << endl;
                            break;
                        }
                        else if (listReq.hoursReqS > hours[i + 1] && listReq.hoursReqS < hours[i + 1])
                        {
                            cout << "Yah:( dia lagi gak bisa nih kalo jam segituu" << endl;
                        }
                    }
                }
                else
                {
                    cout << "Yah:( dia lagi gak bisa nih kalo jam segituu" << endl;
                    break;
                }
            }
            else
            {
                cout << "Dia lagi gak sibuk kok, aman!" << endl;
                break;
            }
        }
        else
        {
            continue;
        }
    }
}

#endif /* Index_h */