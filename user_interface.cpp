/*****************************************************************
//
//  NAME:        Cameron Sumida
//
//  Project:     2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        December 3, 2020
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   A program that creates a user interface.
//   
//
****************************************************************/

#include <iostream>
#include <string>
#include <string.h>
#include "record.h"
#include "llist.h"

using namespace std;

int accountNum();
void getaddress(char [], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A main function
//                 This function prints the user interface.
//
//  Parameters:    argc (int) : contains the number of arguments
//                               which will be processed
//                 *argv[] (char) : array of arguments
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char *argv[])
{
    int isDone = 0;
    int success = 1;
    int accountNo;
    string option;
    string trash;
    char name[30];
    char address[100];
    char filename[16] = "records.txt";

    llist linkedlist(filename);
    cout << "\n";
    while(isDone == 0)
    {
        cout << "This is the bank record database\n";
        cout << "\nPlease choose an option below:\n";
        cout << "add: Add a new record in the database\n";
        cout << "print all: Print all records in the database\n";
        cout << "find: Find records with a specified account #\n";
        cout << "delete: Delete existing records from the database using the account # as a key\n";
        cout << "quit: Quit the program\n";

        cout << "\noption: ";
        getline(cin, option);

        cout << "\n";

        if(option.compare(0, option.size(), "add", 0, option.size()) == 0)
        {
            cout << "Input accepted as add\n\n";

            accountNo = accountNum();
            cout << "Please input name:";
            cin.getline(name, 30);
            if(cin.fail() == true)
            {
                cin.clear();
                getline(cin, trash);
            }
            cout << "\n";
            getaddress(address, 80);

            linkedlist.addRecord(accountNo, name, address);
            strcpy(address, "");
        }
        else if(option.compare(0, option.size(), "print all", 0, option.size()) == 0)
        {
            cout << "Input accepted as print all\n\n";
            linkedlist.printAllRecords();
        }
        else if(option.compare(0, option.size(), "find", 0, option.size()) == 0)
        {
            cout << "Input accepted as find\n\n";
            accountNo = accountNum();
            success = linkedlist.findRecord(accountNo);
            if(success == -1)
            {
                cout << "Record was not found\n\n";
            }
        }
        else if(option.compare(0, option.size(), "delete", 0, option.size()) == 0)
        {
            cout << "Input accepted as delete\n\n";
            accountNo = accountNum();
            success = linkedlist.deleteRecord(accountNo);
            if(success == 0)
            {
                cout << "Record was deleted\n\n";
            }
            else
            {
                cout << "Record was not deleted\n\n";
            }
        }
        else if(option.compare(0, option.size(), "quit", 0, option.size()) == 0)
        {
            cout << "Input accepted as quit\n\n";
            isDone = 1;
        }
        else
        {
            cout << "Invalid option. Please enter a valid option\n\n";
        }
    }

return 0;
}

/*****************************************************************
//
//  Function name: accountNum
//
//  DESCRIPTION:   An accountNum function
//                 This function asks the user for an account number.
//
//  Return values:  accountNo : account number
//
****************************************************************/

int accountNum()
{
    int accountNo;
    int isvalid = 0;
    string trash;

    #ifdef DEBUGMODE
    cout << "Function: accountNo\n";
    cout << "Parameters: none\n\n";
    #endif

    cout << "Please input account number: ";
    cin >> accountNo;
    getline(cin, trash);

    while(isvalid == 0)
    {
        if(cin.fail() == true)
        {
            cin.clear();
            getline(cin, trash);
            cout << "That is not an number. Please enter a number: ";
            cin >> accountNo;
            getline(cin, trash);
        }

        else if(accountNo <= 0)
        {
            cout << "That is not a positive number. Please enter a positive number: ";
            cin >> accountNo;
            getline(cin, trash);
        }

        else
        {
            isvalid = 1;
        }

    }

    cout << "\n";

    return accountNo;
}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   A get address function
//                 This function gets the user's address.
//
//  Parameters:    address[] (char) : where the address is stored
//                 number (int) : number of characters
//
****************************************************************/

void getaddress(char address[], int number)
{
    int line = 0;
    int isDone = 0;
    char input[80];
    char end[2];
    string trash;

    #ifdef DEBUGMODE
    cout << "Function: getAddress\n";
    cout << "Parameters: address: " << address << ", number: " << number << "\n\n";
    #endif
    
    cout << "Input address. Hit enter on a blank line to quit:";

    while((isDone == 0) && (line < number))
    { 
        cin.get(input[line]);
        if(input[line] == '\n' && strcmp(end, "\n") == 0)
        {
            isDone = 1;
            strncpy(address, input, line - 1);
            strcat(address, "\0");
        }
        else if(input[line] == '\n')
        {
            strcpy(end, "\n");
        }
        else
        {
            strcpy(end, "");
        }
        line = line + 1;

        if(line == 80)
        {
            getline(cin, trash);
            strcpy(address, input);
            isDone = 1;
        }
    }
}
