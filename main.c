
#include "readLines.h"
#include "history.h"

void main() {

	History hist;
	ApartmentTable *db = NULL;
	db = initialProgramState(&hist);
	start(db, &hist);
	return 0;
}
