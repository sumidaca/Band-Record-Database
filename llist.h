/*****************************************************************
//
//  NAME:        Cameron Sumida
//
//  PROJECT:     2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        December 3, 2020
//
//  FILE:        llist.h
//
//  DESCRIPTION:
//   Contains the member function prototypes for llist.
//   
//
****************************************************************/
#ifndef LLIST_H
#define LLIST_H
#include "record.h"

class llist
{
private:
    record *    start;
    char        filename[16];
    int         readfile();
    int         writefile();
    void        cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int, char [],char []);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);

};

#endif
