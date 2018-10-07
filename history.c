
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "history.h"


//update_History
void updateHistory(History *hist, char *str) {
	char *tmp = NULL;

	if (hist->short_term_history[N - 1] != NULL) {
		tmp = duplicateStr(hist->short_term_history[N - 1]);
	}

	for (int i = N - 1; i >= 1; i--) {
		if (hist->short_term_history[i - 1] != NULL) {
			free(hist->short_term_history[i]);
			hist->short_term_history[i] = malloc(sizeof(char) * strlen(hist->short_term_history[i - 1]) + 1);
			strcpy(hist->short_term_history[i], hist->short_term_history[i - 1]);
		}
	}

	hist->short_term_history[0] = malloc(strlen(str) + 1);
	strcpy(hist->short_term_history[0], str);

	if (tmp != NULL) {
		if (hist->size_long_history == hist->allocated_size) {
			hist->allocated_size *= 2;
			hist->long_term_history = realloc(hist->long_term_history, sizeof(char*) * hist->allocated_size);
		}

		int new_size = hist->size_long_history;
		hist->long_term_history[new_size] = malloc(sizeof(char) * (strlen(tmp) + 1));

		strcpy(hist->long_term_history[new_size], tmp);
		hist->size_long_history++;
		free(tmp);
	}
}

//printShortHistory
void short_history(History hist) {
	for (int i = N - 1; i >= 0; i--) {
		if (hist.short_term_history[i] != NULL)
			printf("%d: %s\n", hist.size_long_history + (N - i), hist.short_term_history[i]);
	}
}

//printHistory
void history(History hist) {
	for (int i = 0; i < hist.size_long_history; i++) {
		printf("%d: %s\n", i + 1, hist.long_term_history[i]);
	}
	short_history(hist);
}

char *getPrevCommand(int ind, History *hist) {
	int total = hist->size_long_history;
	if (ind == -1) {
		return hist->short_term_history[0];
	}
	else if (ind > total) {
		return hist->short_term_history[N - (ind - total)];
	}
	else {
		return hist->long_term_history[ind - 1];
	}
}

//loadHistory
void load_from_history_file(History *hist) {
	FILE *fp1 = NULL;
	fp1 = fopen((const char *)HISTORY_FILE, "r");
	//checkMemoryAlloc(fp1);

	for (int i = 0; i < N; i++) {
		hist->short_term_history[i] = NULL;
	}
	hist->long_term_history = malloc(sizeof(char*) * INITIAL_ALLOCATED_SIZE_LONG);
	hist->allocated_size = INITIAL_ALLOCATED_SIZE_LONG;
	hist->size_long_history = 0;

	if (fp1 != NULL) {
		char line[256];

		int i = 0, string_size = 0;
		while (fgets(line, sizeof line, fp1)) {
			string_size = (int)strlen(line);
			line[string_size - 1] = '\0';
			if (i < N) {
				hist->short_term_history[i] = malloc(sizeof(char) * string_size);
				strcpy(hist->short_term_history[i], line);
			}
			else {
				if (hist->size_long_history == hist->allocated_size) {
					hist->allocated_size *= 2;
					hist->long_term_history = realloc(hist->long_term_history, sizeof(char*) * hist->allocated_size);
				}

				hist->size_long_history++;
				hist->long_term_history[i - N] = malloc(sizeof(char) * string_size);
				strncpy(hist->long_term_history[i - N], line, (size_t)string_size);
			}
			i++;
		}
	}
}


void save_history_to_file(History hist) {
	FILE *fp1 = NULL;
	fp1 = fopen((const char *)HISTORY_FILE, "w");
	checkMemoryAlloc(fp1);

	for (int i = 0; i < N; i++) {
		if (hist.short_term_history[i] != NULL) {
			fprintf(fp1, "%s\n", hist.short_term_history[i]);
		}
	}

	for (int i = hist.size_long_history - 1; i >= 0; i--) {
		fprintf(fp1, "%s\n", hist.long_term_history[i]);
	}
	fclose(fp1);
}
