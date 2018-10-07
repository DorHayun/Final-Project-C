
#include "delApartment.h"


void delApartment(COMMAND cmd, ApartmentTable *db)
{
	time_t d1;
	char *pt;
	int currentPlace = 0;

	pt = getValueByKey("Enter", cmd.kwargs);
	int dayBack = (int)(pt ? atoi(pt) : NULL);
	Apartment* arrTmp = malloc(sizeof(Apartment*) * db->size);
	for (int i = 0; i < db->size; i++) {
		Apartment tmp = db->arr[i];
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
			if (d1 - now  > 0) {

			}
			else {
				arrTmp[currentPlace++] = db->arr[i];
			}
		}
	}
	db->size = currentPlace;
	db->arr = arrTmp;
}
