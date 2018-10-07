

#include "addApartment.h"
#include <stdlib.h>


void addApartment(COMMAND cmd, ApartmentTable *db)
{
	int newSize = db->size;

	if (db->size == 0)
	{
		db->r_size = 2;
		db->arr = malloc(sizeof(Apartment) * db->r_size);

	}
	else if (db->size == db->r_size) {
		db->r_size *= 2;
		db->arr = realloc(db->arr, sizeof(Apartment) * db->r_size);

	}

	ListNode *pt = cmd.args->head;
	db->arr[newSize].id = db->current_index++;

	// Address
	db->arr[newSize].address = duplicateStr(pt->data);

	//  Price
	pt = pt->next;
	db->arr[newSize].price = atoi(pt->data);

	//  Rooms number
	pt = pt->next;
	db->arr[newSize].rooms = (short)atoi(pt->data);

	//   day, month, year
	pt = pt->next;
	db->arr[newSize].entry_day = (short)atoi(pt->data);

	pt = pt->next;
	db->arr[newSize].entry_month = (short)atoi(pt->data);

	pt = pt->next;
	db->arr[newSize].entry_year = (short)atoi(pt->data);

	time_t now = time(NULL);
	struct tm *time_obj = localtime(&now);

	db->arr[newSize].created_day = (short)time_obj->tm_mday;
	db->arr[newSize].created_month = (short)time_obj->tm_mon;
	db->arr[newSize].created_year = (short)(time_obj->tm_year - 100);
	db->size++;
}