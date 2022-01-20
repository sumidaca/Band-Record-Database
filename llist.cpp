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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   A program that modifies the database.
//   
//
****************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include "llist.h"
#include "record.h"

using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   A constructor
//                 This function sets the filename and calls readfile 
//                 at the start of the program.
//
****************************************************************/

llist::llist()
{
    strcpy(filename, "records.txt");
    start = NULL;
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   A constructor
//                 This function sets the filename and calls readfile 
//                 at the start of the program.
//
//  Parameters:    filename[] (char) : name of file
//
****************************************************************/

llist::llist(char filename[])
{
    strcpy(this->filename, filename);
    start = NULL;
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   A destructor
//                 This function calls writefile and cleanup at the
//                 end of the program
//
//  Parameters:    number (int) : account number
//
//                 name[] (char) : name of customer
//
//                 address[] (char) : address of customer
//
//  Return values:  0 : success
//
****************************************************************/

llist::~llist()
{
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   An add record function
//                 This function adds a record to the database.
//
//  Parameters:    number (int) : account number
//
//                 name[] (char) : name of customer
//
//                 address[] (char) : address of customer
//
//  Return values:  0 : success
//
****************************************************************/

int llist::addRecord (int accountNo, char name[], char address[])
{
    struct record * newrecord;
    struct record * current;
    struct record * previous;
    int isdone;

    #ifdef DEBUGMODE
    cout << "Function: addRecord\n";
    cout << "Parameters: accountNo: " << accountNo << ", name: " << name << ", address: " << address << "\n\n";
    #endif

    newrecord = new struct record;

    isdone = 0;
    (*newrecord).accountno = accountNo;
    strcpy((*newrecord).name, name);
    strcpy((*newrecord).address, address);

    current = NULL;
    previous = NULL;

    if(start == NULL)
    {
        (*newrecord).next = NULL;
        start = newrecord;
    }
    else
    {
        current = start;
        while(isdone == 0)
        {
            if(current == NULL)
            {
                (*previous).next = newrecord;
                (*newrecord).next = NULL;
                isdone = 1;
            }
            else if((*current).accountno > accountNo)
            {
                previous = current;
                current = (*current).next;
            }
            else if(accountNo >= (*start).accountno)
            {
                (*newrecord).next = current;
                start = newrecord;
                isdone = 1;
            }
            else
            {
                (*previous).next = newrecord;
                (*newrecord).next = current;
                isdone = 1;
            }
        }
    }

    return 0;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   A print all records function
//                 This function prints all records from the database.
//
//  Return values:  0 : success
//
****************************************************************/

void llist::printAllRecords()
{
    struct record * records;

    #ifdef DEBUGMODE
    cout << "Function: printAllRecords\n\n";
    #endif

    records = start;

    if(records == NULL)
    {
        cout << "There are no records to print\n";
    }
    else
    {
        while(records != NULL)
        {
            cout << "Account number: "<< (*records).accountno << "\nName: " << (*records).name << "\nAddress: " << (*records).address << "\n\n";
            records = (*records).next;
        }
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   A find record function
//                 This function finds a record from the database.
//
//  Parameters:    number (int) : account number
//
//  Return values:  0 : success
//
****************************************************************/

int llist::findRecord (int accountNo)
{
    int isdone;
    int result;
    struct record * records;

    #ifdef DEBUGMODE
    cout << "Function: findRecord\n";
    cout << "Parameters: accountNo: " << accountNo << "\n\n";
    #endif

    isdone = 0;
    result = -1;
    records = start;

    if(records != NULL)
    {
        while(isdone == 0)
        {
            if(records == NULL)
            {
                isdone = 1;
            }
            else if((*records).accountno > accountNo)
            {
                records = (*records).next;
            }
            else if(accountNo == (*records).accountno)
            {
                cout << "Account number: " << (*records).accountno << "\nName: " << (*records).name << "\nAddress: " << (*records).address << "\n\n";
                records = (*records).next;
                result = 0;
            }
            else
            {
                isdone = 1;
            }
        }
    }

    return result;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   A delete record function
//                 This function deletes a record from the database.
//
//  Parameters:    number (int) : account number
//
//  Return values:  0 : success
//
****************************************************************/

int llist::deleteRecord (int accountNo)
{
    struct record * current;
    struct record * previous;
    int isdone;
    int result;

    #ifdef DEBUGMODE
    cout << "Function: deleteRecord\n";
    cout << "Parameters: accountNo: " << accountNo << "\n\n";
    #endif

    isdone = 0;
    result = -1;
    current = NULL;
    previous = NULL;

    if(start != NULL)
    {
        current = start;
        while(isdone == 0)
        {
            if(current == NULL)
            {
                isdone = 1;
            }
            else if((*current).accountno > accountNo)
            {
                previous = current;
                current = (*current).next;
            }
            else if(accountNo == (*start).accountno)
            {
                start = (*current).next;
                previous = current;
                current = (*current).next;
                delete previous;
                result = 0;
            }
            else if(accountNo == (*current).accountno && previous != NULL)
            {
                (*previous).next = (*current).next;
                delete current;
                current = (*previous).next;
                result = 0;
            }
            else
            {
                isdone = 1;
            }
        }
    }

    return result;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   A read function
//                 This function reads the specified file.
//
//  Return values:  success : 0 couldn't read file, 1 if read file successfully
//
****************************************************************/

int llist::readfile ()
{
    struct record * temp;
    struct record * current;
    struct record * previous;
    int success = 0;
    int line = 0;
    int isdone = 0;
    char input[80];
    char end[2];

    #ifdef DEBUGMODE
    cout << "Function: readfile\n";
    #endif

    temp = NULL;
    current = NULL;
    previous = NULL;
    success = 0;

    ifstream infile(filename);

    if(infile != NULL)
    {
        start = new struct record;
        temp = new struct record;

        infile >> (*start).accountno;

        if((*start).accountno != 0)
        {
            infile.get();
            infile.getline((*start).name, 25);
            while((isdone == 0) && (line < 80))
            { 
                infile.get(input[line]);
                if(input[line] == '\n' && strcmp(end, "\n") == 0)
                {
                    isdone = 1;
                    strncpy((*start).address, input, line - 1);
                    strcat((*start).address, "\0");
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
            }
            isdone = 0;
            line = 0;
            strcpy(end, "");
            strcpy(input, "");
        }
        else
        {
            start = NULL;
        }

        while(infile >> (*temp).accountno && start != NULL)
        {
            infile.get();
            infile.getline((*temp).name, 25);
            current = new struct record;
            (*current).accountno = (*temp).accountno;
            strcpy((*current).name, (*temp).name);
            while((isdone == 0) && (line < 80))
            { 
                infile.get(input[line]);
                if(input[line] == '\n' && strcmp(end, "\n") == 0)
                {
                    isdone = 1;
                    strncpy((*current).address, input, line - 1);
                    strcat((*current).address, "\0");
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
            }
            isdone = 0;
            line = 0;
            strcpy(end, "");
            strcpy(input, "");          
            if(previous == NULL)
            {
                (*start).next = current;
            }
            else
            {
                (*previous).next = current;
            }
            previous = current;
            current = NULL;
        }
        success = 1;
    }

    infile.close();

    return success;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   A write function 
//                 This function write to the specified file.
//
//  Return values:  success : 0 couldn't read file, 1 if read file successfully
//
****************************************************************/

int llist::writefile ()
{
    ofstream outfile;
    int success = 0;
    struct record * records;

    #ifdef DEBUGMODE
    cout << "Function: writefile\n";
    #endif

    records = start;

    outfile.open(filename);

    if(records != NULL)
    {
        while(records != NULL)
        {
            outfile << (*records).accountno << "\n" << (*records).name << "\n" << (*records).address << "\n\n";
            records = (*records).next;
        }

        success = 1;
    }
    else
    {
        outfile << "";
    }

    outfile.close();

    return success;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   A clean up function
//                 This function deallocates the memory in heap.
//
****************************************************************/

void llist::cleanup ()
{
    #ifdef DEBUGMODE
    cout << "Function: cleanup\n";
    #endif

    while (start != NULL)
    {
        delete start;
        start = (*start).next;
    }

    start = NULL;
}
