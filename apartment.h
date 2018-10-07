#pragma once

#ifndef APARTMENT_H
#define APARTMENT_H

#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include "utilityFunctions.h"


#define APARTMENT_FILE "db.txt"

typedef struct apartment {
	int id; //first field, 
	int price; //2
	char *address; //3
	short int rooms; //4
	short int entry_year; //5
	short int entry_month; //6
	short int entry_day; //7
	short int created_year; //8
	short int created_month; //9
	short int created_day; //10
} Apartment;

typedef unsigned char BYTE;


typedef struct apartment_db {
	int size;
	int r_size;
	int current_index;
	Apartment *arr;
} ApartmentTable;

void printApartment(Apartment apartment);

ApartmentTable sortTable(ApartmentTable db, BOOL desc);

void saveAptTofile(ApartmentTable *db);

ApartmentTable *load_apartment_table_from_file();

#endif 