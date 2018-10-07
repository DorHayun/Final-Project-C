//Following are main functions used in reading command lines and storing/retrieving data
// in appropariate lists/fields


#include <stdlib.h>
#include <string.h>
#include "readLines.h"
#include "getApartment.h"
#include "addApartment.h"
#include "buyApartment.h"
#include "delApartment.h"


void start(ApartmentTable *db, History *hist) {

	BOOL isEOF = FALSE;
	char line[INPUT_MAX];
	COMMAND *currCommand = NULL;

	printf("Please enter one of the following commands: \n");
	printf("add-an-apt, get-an-apt, buy-an-apt or delete-an-apt\n");
	printf("For reconstruction commands, please enter:\n");
	printf("!!, !num, history, short_history or !num^str1^str2\n");
	printf("To exit, enter exit.\n");

	while (isEOF == FALSE) {
		gets(line);
		if (line[0] != '\0') {
			if (strcmp(line, "exit") == 0) {
				exitProgram(db, hist);
				break;
			}
			else {
				currCommand = readCurrCommand(line);
				performCommand(currCommand, db, hist);
			}
		}
	}
}



// executes command entered
void performCommand(COMMAND *currCommand, ApartmentTable *db, History *hist) {

	if (strcmp(currCommand->command, "get-an-apt") == 0) {
		updateHistory(hist, currCommand->raw_command);
		getApartment(*currCommand, *db);
	}
	else if (strcmp(currCommand->command, "buy-an-apt") == 0) {
		updateHistory(hist, currCommand->raw_command);
		buyApartment(*currCommand, db);
	}
	else if (strcmp(currCommand->command, "delete-an-apt") == 0) {
		updateHistory(hist, currCommand->raw_command);
		delApartment(*currCommand, db);
	}
	else if (strcmp(currCommand->command, "add-an-apt") == 0) {
		updateHistory(hist, currCommand->raw_command);
		addApartment(*currCommand, db);
	}
	else if (strcmp(currCommand->command, "history") == 0) {
		history(*hist);
	}
	else if (strcmp(currCommand->command, "short_history") == 0) {
		short_history(*hist);
	}
	else if (currCommand->command[0] == '!') {
		performPrevCommand(currCommand, db, hist);
	}
}


//execute command from history
void performPrevCommand(COMMAND *currCommand, ApartmentTable *db, History *hist) {
	BOOL is_replace_required = FALSE;
	char *find_str = NULL;
	char *replace_str = NULL;
	char *found_str = startSubString(currCommand->raw_command, '^');
	int history_command_number = 0;

	if (found_str == NULL) {

		// encountered '!!', so performing last command in history
		if (currCommand->command[1] == '!') {
			history_command_number = -1;
		}

		//encountered '!<num>', so perform command at specified number
		else {
			history_command_number = atoi(currCommand->raw_command + 1);
		}
	}

	//encountered "!<num>^str1^str2": must perform command at <num>, replacing str1 with str2
	else {
		history_command_number = atoi(found_str + 1);
		find_str = startSubString(currCommand->raw_command + strlen(found_str) + 1, '^');
		replace_str = duplicateStr(currCommand->raw_command + strlen(find_str) + strlen(found_str) + 2);
		is_replace_required = TRUE;
	}
	char *command_from_hist = getPrevCommand(history_command_number, hist);

	//creates dummy string - copy of command at <num>
	char *command_to_run = duplicateStr(command_from_hist);

	if (find_str != NULL && replace_str != NULL) {
		// replacing string using helper function
		command_to_run = str_replace(command_to_run, find_str, replace_str);
	}
	currCommand = readCurrCommand(command_to_run);
	performCommand(currCommand, db, hist);
}

// exitProgram()
void exitProgram(ApartmentTable *table, History *hist) {
	save_history_to_file(*hist);
	//save_apartment_table_to_file(table);
	saveAptTofile(table);

	printf("Good Bye!");
}



ApartmentTable *initialProgramState(History *hist) {
	ApartmentTable *table;
	table = load_apartment_table_from_file();
	load_from_history_file(hist);
	return table;
}



// analyze key words 
Dict *findKeyWords(char *str) {
	int physSize = 2, size = 0;
	KeyValue *arr;
	Dict *pt = malloc(sizeof(Dict));

	arr = malloc(sizeof(KeyValue) * 2);
	str = strtok(str, "-");

	while (str != NULL) {
		if (size == physSize) {
			physSize *= 2;
			arr = realloc(arr, sizeof(Dict) * physSize);
		}
		arr[size].key = startSubString(str, ' ');
		arr[size].value = NULL;
		if (arr[size].key == NULL) {
			arr[size].key = duplicateStr(str);
		}
		else {
			if (strlen(str) > strlen(arr[size].key)) {
				arr[size].value = removeSpaces(duplicateStr(str + strlen(arr[size].key)));
			}
		}
		str = strtok(NULL, "-");
		size++;
	}

	pt->size = size;
	pt->arr = arr;
	return pt;
}


// read and store characters from command line
List *extractChars(char *ch) {

	List *pList = malloc(sizeof(List));
	char *tmp, *last;

	makeEmptyList(pList);

	while (ch != NULL) {
		if (ch[0] == '"') { //for example, if command was:  add-an-apt "Hasavyonim 23 Ramat Ono"  2000000 
			ch++;
			tmp = startSubString(ch, '"');
			ch++;
		}
		else {
			tmp = startSubString(ch, ' ');
			if (tmp == NULL) {
				tmp = duplicateStr(ch);
				ch = NULL;
			}
		}
		insertDataToEndList(pList, tmp);
		if (ch != NULL)
			ch += strlen(tmp) + 1;
	}
	return pList;
}



void printDict(Dict *kwargs) {
	for (int i = 0; i < kwargs->size; i++) {
		printf("Key : %s \n", kwargs->arr[i].key);
		if (kwargs->arr[i].value != NULL) {
			printf("Value : %s \n", kwargs->arr[i].value);
		}
	}

}


char *getValueByKey(char *key, Dict *kwargs) {
	for (int i = 0; i < kwargs->size; i++) {
		if (strcmp(kwargs->arr[i].key, key) == 0) {
			return kwargs->arr[i].value;
		}
	}
	return NULL;
}


// isCommand: returns true if string is command such as "get-an-apt" or "sr" 
BOOL isCommand(char *key, Dict *kwargs) {
	for (int i = 0; i < kwargs->size; i++) {
		if (strcmp(kwargs->arr[i].key, key) == 0) {
			return TRUE;
		}
	}
	return FALSE;
}


void insertNodeToEndList(List *pList, ListNode *newNode) {
	if (isEmptyList(pList)) {
		pList->head = pList->tail = newNode;
	}
	else {
		pList->tail->next = newNode;
		pList->tail = newNode;
	}
}


void makeEmptyList(List *pList) {
	pList->head = pList->tail = NULL;
}

BOOL isEmptyList(List *lst) {
	return (lst == NULL) || (lst->head == NULL);
}

void freeList(List *lst) {
	ListNode *curr = lst->head, *saver;
	while (curr != NULL) {
		saver = curr->next;
		free(curr);
		curr = saver;
	}
}

void insertDataToEndList(List *pList, char *str) {
	ListNode *lNode;
	lNode = createNodeElement(str, NULL);
	insertNodeToEndList(pList, lNode);
}

ListNode *createNodeElement(char *str, ListNode *next) {
	ListNode *pNode;
	pNode = malloc(sizeof(ListNode));
	pNode->data = str;
	pNode->next = next;
	return pNode;
}

void printList(List *pList) {
	ListNode *curr;
	curr = pList->head;
	while (curr != NULL) {
		printf("%s \n", curr->data);
		curr = curr->next;
	}

}

// reads current command entered
COMMAND *readCurrCommand(char *str) {
	COMMAND *cmd = malloc(sizeof(Dict));
	char *args = NULL, *command_name = NULL;

	cmd->raw_command = duplicateStr(str);
	command_name = strtok(str, " ");
	cmd->command = duplicateStr(command_name);
	cmd->args = NULL;
	cmd->kwargs = NULL;

	args = str + strlen(command_name) + 1;

	if (args[0] != '-' && args[0] != '–')
		cmd->args = extractChars(args);
	else
		cmd->kwargs = findKeyWords(args);

	return cmd;
}

