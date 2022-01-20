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
//  FILE:        record.h
//
//  DESCRIPTION:
//   Contains the definition of record.
//   
//
****************************************************************/
#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};

#endif
