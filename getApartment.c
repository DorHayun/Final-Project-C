

#include <stdlib.h>
#include <time.h>
#include "getApartment.h"

/* //old version
void getApartment(COMMAND cmd, ApartmentTable db) {

	BOOL isAllocated = FALSE;
	ApartmentTable ptr = db;
	//first sort if necessary 
	// sort in ascending order
	if (isCommand("s", cmd.kwargs)) {
		ptr = sortTable(db, FALSE);
		isAllocated = TRUE;
	}
	//sort in descending order
	else if (isCommand("sr", cmd.kwargs)) {
		ptr = sortTable(db, TRUE);
		isAllocated = TRUE;
	}

	// if there is a requirement that is not matched, skip and continue, otherwise include
	for (int i = 0; i < db.size; i++) {
		Apartment tmp = ptr.arr[i];
		time_t d1, d2;
		char *requirement;

		requirement = getValueByKey("MaxPrice", cmd.kwargs);
		int price = (int)(requirement ? atoi(requirement) : NULL);
		if (price && tmp.price > price)
			continue;

		requirement = getValueByKey("MinNumRooms", cmd.kwargs);
		int rooms = (int)(requirement ? atoi(requirement) : NULL);
		if (rooms && tmp.rooms < rooms)
			continue;

		requirement = getValueByKey("MaxNumRooms", cmd.kwargs);
		rooms = (int)(requirement ? atoi(requirement) : NULL);
		if (rooms && tmp.rooms > rooms)
			continue;


		// return all apartments that were inserted @dayBack ago
		requirement = getValueByKey("Enter", cmd.kwargs);
		int dayBack = (int)(requirement ? atoi(requirement) : NULL);
		if (dayBack > 0) {
			struct tm entryDate;
			int now = (int)time(NULL);
			now = now - (84600 * dayBack);

			entryDate.tm_hour = 23;
			entryDate.tm_min = 59;
			entryDate.tm_sec = 59;
			entryDate.tm_year = tmp.entry_year + 100;
			entryDate.tm_mon = tmp.entry_month - 1;
			entryDate.tm_mday = tmp.entry_day;

			d1 = mktime(&entryDate);
			if (now - d1  > 0)
				continue;
		}

		char* date = getValueByKey("Date", cmd.kwargs);
		if (date != NULL) {
			struct tm endDate;
			struct tm startDate;
			endDate.tm_hour = 23;
			endDate.tm_min = 59;
			endDate.tm_sec = 59;
			endDate.tm_year = atoi(substring(date, 5, 4)) - 1900;
			endDate.tm_mon = atoi(substring(date, 3, 2)) - 1;
			endDate.tm_mday = atoi(substring(date, 1, 2));

			startDate.tm_hour = 23;
			startDate.tm_min = 59;
			startDate.tm_sec = 59;
			startDate.tm_year = tmp.entry_year + 100;
			startDate.tm_mon = tmp.entry_month - 1;
			startDate.tm_mday = tmp.entry_day;

			d1 = mktime(&endDate);
			d2 = mktime(&startDate);
			if (d2 - d1 > 0)
				continue;
		}

		printApartment(tmp);
	}

	if (isAllocated == TRUE) {
		// free the memory that allocated if the array is sorted
		//free(ptr.arr);
	}
}
*/


void getApartment(COMMAND cmd, ApartmentTable db) {
	BOOL isAllocated = FALSE;
	ApartmentTable ptr = db;
	//start by sorting if necessary 
	if (isCommand("s", cmd.kwargs)) { 	// sort in ascending order
		ptr = sortTable(db, FALSE);
		isAllocated = TRUE;
	}
	else if (isCommand("sr", cmd.kwargs)) { //descending order
		ptr = sortTable(db, TRUE);
		isAllocated = TRUE;
	}

	// if there is a requirement that is not matched, skip and continue, otherwise include
	for (int i = 0; i < db.size; i++) {
		Apartment tmp = ptr.arr[i];
		time_t d1, d2;
		char *requirement;

		requirement = getValueByKey("MaxPrice", cmd.kwargs);
		if (requirement != NULL) {
			int price = atoi(requirement);
			if (price && tmp.price > price)
				continue;
		}

		requirement = getValueByKey("MinNumRooms", cmd.kwargs);
		if (requirement != NULL) {
			int rooms = atoi(requirement);
			if (rooms && tmp.rooms < rooms)
				continue;
		}

		requirement = getValueByKey("MaxNumRooms", cmd.kwargs);
		if (requirement != NULL) {
			int rooms = atoi(requirement);
			if (rooms && tmp.rooms > rooms)
				continue;
		}

		requirement = getValueByKey("Date", cmd.kwargs);
		if (requirement != NULL) {
			int dateDay = atoi(substring(requirement, 1, 2));
			int dateMonth = atoi(substring(requirement, 3, 2));
			int dateYear = atoi(substring(requirement, 5, 4));
			if (dateYear && tmp.entry_year > dateYear)
				continue;
			if (dateMonth && tmp.entry_month > dateMonth)
				continue;
			if (dateDay && tmp.entry_day > dateDay)
				continue;
		}
		printApartment(tmp);
	}

	if (isAllocated == TRUE) {
		free(ptr.arr);
	}
}
