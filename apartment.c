



#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "apartment.h"


void printApartment(Apartment apartment)
{

	printf("Apt details:\n");
	printf("Code: %d\n", apartment.id);
	printf("Address: %s\n", apartment.address);
	printf("Number of rooms: %d\n", apartment.rooms);
	printf("Price: %d\n", apartment.price);
	printf("Entry date: %d.%d.%d\n", apartment.entry_day, apartment.entry_month, apartment.entry_year + 2000);
	printf("Database entry date: %d.%d.%d\n", apartment.created_day, apartment.created_month, apartment.created_year + 2000);
}
 
void swapApartment(Apartment *pt1, Apartment *pt2){
	Apartment tmp = *pt1;
	*pt1 = *pt2;
	*pt2 = tmp;
}


ApartmentTable *load_apartment_table_from_file()
{
	// Loading apartment table from file

	ApartmentTable *db = malloc(sizeof(ApartmentTable));
	db->arr = malloc(sizeof(Apartment *));
	db->size = 0;
	db->r_size = 0;
	db->current_index = 0;

	FILE *fp1 = NULL;
	fp1 = fopen((const char *)APARTMENT_FILE, "r");

	if (fp1 != NULL) {
		int code = 0;
		int *arrSize = &db->size;
		while (fread(&code, sizeof(short int), 1, fp1) > 0)
		{
			int address_len;
			if (db->size == 0) {
				db->r_size = 2;
				db->arr = malloc(sizeof(Apartment) * db->r_size);

			}
			else if (db->size == db->r_size) {
				db->r_size *= 2;
				db->arr = realloc(db->arr, sizeof(Apartment) * db->r_size);

			}

			db->current_index = max(db->current_index, code);
			db->arr[*arrSize].id = code;

			// Reading the address and address len
			fread(&address_len, sizeof(short int), 1, fp1);
			db->arr[*arrSize].address = malloc(sizeof(char) * address_len);
			fread(db->arr[*arrSize].address, sizeof(char), (size_t)address_len, fp1);
			db->arr[*arrSize].address[address_len] = '\0';

			// reading the price of apartment
			fread(&(db->arr[*arrSize].price), sizeof(int), 1, fp1);

			BYTE decoded[5];

			fread(&decoded, sizeof(BYTE), 5, fp1);
			db->arr[*arrSize].rooms = (short int)((decoded[0] & 0xF0) >> 4);
			db->arr[*arrSize].entry_day = (short int)((decoded[0] & 0x0F) << 1 | (decoded[1] & 0x80) >> 7);
			db->arr[*arrSize].entry_month = (short int)((decoded[1] >> 3) & 0x0F);
			db->arr[*arrSize].entry_year = (short int)((decoded[1] & 0x07) << 4 | (decoded[2] & 0xF0) >> 4);

			db->arr[*arrSize].created_day = (short int)((decoded[3] & 0xF8) >> 3);
			db->arr[*arrSize].created_month = (short int)((decoded[3] & 0x07) << 1 | (decoded[3] & 0x80) >> 7);
			db->arr[*arrSize].created_year = (short int)decoded[4];
			(*arrSize)++;
		}
		fclose(fp1);
	}
	db->current_index++;
	return db;
}



void saveAptTofile(ApartmentTable *db)
{
	FILE *fp1 = NULL;
	fp1 = fopen((const char *)APARTMENT_FILE, "w");

	for (int i = 0; i < db->size; i++)

	{
		int address_len = (int)strlen(db->arr[i].address);

		fwrite(&(db->arr[i].id), sizeof(short int), 1, fp1);
		fwrite(&address_len, sizeof(short int), 1, fp1);
		fwrite(db->arr[i].address, sizeof(char), (size_t)address_len, fp1);
		fwrite(&(db->arr[i].price), sizeof(int), 1, fp1);

		BYTE decoded[5];
		decoded[0] |= db->arr[i].rooms << 4;
		decoded[0] |= db->arr[i].entry_day >> 1;
		decoded[1] |= (db->arr[i].entry_day & 0x01) << 7;
		decoded[1] |= db->arr[i].entry_month << 3;
		decoded[1] |= db->arr[i].entry_year >> 4;
		decoded[2] |= db->arr[i].entry_year << 4;

		decoded[3] |= db->arr[i].created_day << 3;
		decoded[3] |= db->arr[i].created_month >> 1;
		decoded[4] |= db->arr[i].created_month & 0x01 << 7;
		decoded[4] |= db->arr[i].created_year;
		fwrite(&decoded, sizeof(BYTE), (size_t)5, fp1);
	}

	fclose(fp1);
}



ApartmentTable sortTable(ApartmentTable db, BOOL desc)
{

	int i;
	ApartmentTable sortedDb;
	sortedDb.arr = malloc(sizeof(Apartment) * db.size);
	sortedDb.size = db.size;

	for (i = 0; i < db.size; i++) {
		sortedDb.arr[i] = db.arr[i];
	}

	BOOL isSorted = FALSE;

	while (isSorted == FALSE)
	{
		isSorted = TRUE;
		for (i = 0; i < sortedDb.size - 1; i++) {
			if (desc == TRUE && sortedDb.arr[i].price < sortedDb.arr[i + 1].price) {
				swapApartment(&sortedDb.arr[i], &sortedDb.arr[i + 1]);
				isSorted = FALSE;
			}
			else if (desc == FALSE && sortedDb.arr[i].price > sortedDb.arr[i + 1].price) {
				swapApartment(&sortedDb.arr[i], &sortedDb.arr[i + 1]);
				isSorted = FALSE;
			}
		}
	}
	return sortedDb;
}
