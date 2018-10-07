#pragma once

#ifndef READLINES_H
#define READLINES_H

#include <string.h>
#include <stdio.h>
#include "history.h"
#include "apartment.h"
#include "utilityFunctions.h"
#define _CRT_SECURE_NO_WARNINGS

#define INPUT_MAX 256

typedef struct list_node {
	char *data;
	struct list_node *next;
} ListNode;

typedef struct list {
	ListNode *head;
	ListNode *tail;
} List;

typedef struct key_value {
	char *key;
	char *value;
} KeyValue;

typedef struct dict {
	KeyValue *arr;
	int size;
} Dict;

typedef struct command {
	char *raw_command;
	char *command;
	List *args;
	Dict *kwargs;
} COMMAND;


ApartmentTable *initialProgramState(History *hist);
void performPrevCommand(COMMAND *currCommand, ApartmentTable *db, History *hist);

void performCommand(COMMAND *currCommand, ApartmentTable *db, History *hist);

void start(ApartmentTable *db, History *hist);

void exitProgram(ApartmentTable *db, History *hist);

COMMAND *readCurrCommand(char *str);

List *extractArgs(char *args);

Dict *findKeyWords(char *str);

char *startSubString(const char *str, char ch);

void debugCommand(COMMAND);

/* Dict helper functions */
char *getValueByKey(char *key, Dict *dict);
BOOL isCommand(char *key, Dict *dict);
void printDict(Dict *pValue);



/* List helper functions */
void makeEmptyList(List *pList);
void insertDataToEndList(List *pList, char *str);
void insertNodeToEndList(List *pList, ListNode *newNode);
void freeList(List *pList);
void printList(List *pList);
BOOL isEmptyList(List *lst);
ListNode *createNodeElement(char *str, ListNode *next);
void swapNodes(ListNode *pNode, ListNode *pNode2);

#endif  

