#pragma once

#ifndef HISTORY_H
#define HISTORY_H

#define N 7
#define INITIAL_ALLOCATED_SIZE_LONG 7
#define HISTORY_FILE "history.txt"
#define _CRT_SECURE_NO_WARNINGS

typedef struct history {
	char* short_term_history[N];
	char** long_term_history;
	int size_long_history;
	int allocated_size;
} History;

void updateHistory(History* hist, char*str);
void short_history(History hist);
void history(History hist);
char* getPrevCommand(int ind, History* hist);
void save_history_to_file(History hist);
void load_from_history_file(History *pHistory);
void checkMemoryAlloc(void *ptr);

#endif 