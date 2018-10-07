

#include <stdlib.h>
#include "buyApartment.h"

void buyApartment(COMMAND cmd, ApartmentTable *db)
{
	int id_number, i, size;
	ListNode *pt;
	pt = cmd.args->head;
	id_number = atoi(pt->data);
	size = db->size;
	for (i = 0; i<size; i++)
	{
		if (id_number == db->arr[i].id)
		{
			db->arr[i] = db->arr[size - 1];
			db->size = (size - 1);
			return;
		}
	}
}