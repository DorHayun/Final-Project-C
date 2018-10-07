#pragma once


#ifndef UTILITY_FUNCS_H
#define UTILITY_FUNCS_H
#define _CRT_SECURE_NO_WARNINGS


typedef int BOOL;
#define FALSE 0
#define TRUE 1

char *substring(char *string, int startPos, int length);
char *str_replace(char *org_str, char *search, char *replace);
char *removeSpaces(char *string);
char *startSubString(const char *str, char ch);
void checkMemoryAlloc(void *ptr);
char *duplicateStr(const char *s);


//int max(int num1, int num2);

#endif  
