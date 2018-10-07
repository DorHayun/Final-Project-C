//Following are all helper functions used for string manipulation 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilityFunctions.h"



//removes whitespace from string
char *removeSpaces(char *string) {

	if (string[0] == ' ') {
		char *tmp = substring(string, 2, (int)strlen(string));
		free(string);
		string = tmp;
	}

	if (string[strlen(string) - 1] == ' ')
		string[strlen(string) - 1] = '\0';

	return string;
}

//create a substring of given length from string starting position
char *substring(char *string, int startPos, int length) {
	char *strPtr;
	int c;

	strPtr = malloc(sizeof(char) * (length + 1));

	for (c = 0; c < length; c++) {
		*(strPtr + c) = *(string + startPos - 1);
		string++;
	}
	*(strPtr + c) = '\0';
	return strPtr;
}


// replaces str1 (replaceStr)  with str2 (withStr) 
char *str_replace(char *orig, char *replaceStr, char *withStr) {

	char *result; // the return string
	char *ins;    // the next insert point
	char *tmp;    // dummy variable
	int len_rep;  //length of string to be removed
	int len_with; //length of string that we replace repStr with
	int len_front; //distance between rep and end of last rep
	int count; // number of replacements

			   //error check
	if (!orig || !replaceStr)
		return NULL;

	len_rep = (int)strlen(replaceStr);
	len_with = (int)strlen(withStr);

	// count the number of replacements needed
	ins = orig;

	for (count = 0; tmp = strstr(ins, replaceStr); ++count) {
		ins = tmp + len_rep;
	}
	tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

	if (!result)
		return NULL;

	while (count--) {
		ins = strstr(orig, replaceStr);
		len_front = (int)(ins - orig);
		tmp = strncpy(tmp, orig, (size_t)len_front) + len_front;
		tmp = strcpy(tmp, withStr) + len_with;
		orig += len_front + len_rep;
	}	
	strcpy(tmp, orig);
	return result;
}


//searches for ch in str and returns pointer to location if found
char *startSubString(const char *str, char ch) {
	char *strEnd, *strOut;
	strEnd = strchr(str, ch);

	if (strEnd == NULL)
		return NULL;

	strOut = malloc(sizeof(char) * (strEnd - str) + 1);
	strncpy(strOut, str, strEnd - str);
	strOut[strEnd - str] = '\0';
	return removeSpaces(strOut);
}


void checkMemoryAlloc(void *ptr) {
	if (ptr == NULL) {
		printf("Error allocating memory.\n");
		return -1;
	}
}


char *duplicateStr(const char *s) {
	char *d = malloc(strlen(s) + 1);   // Space for length plus nul
	if (d == NULL) return NULL;          // No memory
	strcpy(d, s);                        // Copy the characters
	return d;                            // Return the new string
}
