#include "chessboard.h"
#include <stdlib.h>
#include <string.h>
#include <io.h>
#pragma warning (disable : 4996)
#pragma warning (disable : 6031)

void saveCB(CBstring CBStr) {
	int column = CBStr.column;
	int line = CBStr.line;
	char name[200] = "";
	char* str = (char*)malloc(sizeof(char) * 20005);
	if (str == NULL) { printf("fail to malloc()!\n"); return; }
	str[0] = '\0';
	sprintf(str, "%d-%d-%s", line, column, CBStr.chessboard);
	char file_str[200];

	do {
		printf("Input the name of your chessboard:\n");
		if (scanf("%s", name) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		sprintf(file_str, "./output/%s.txt", name);
		if (strlen(name) > 16) {
			printf("Your chessboard's name is too long.\n");
			setbuf(stdin, NULL); continue;
		}
		else if (access(file_str, 0) != -1) {
			printf("Your output file has have a file with this name.\n");
			setbuf(stdin, NULL); continue;
		}
		break;
	} while (1);

	FILE* file = fopen(file_str, "w");
	fputs(str, file);
	fclose(file);
	printf("Your chessbaord has been saved.\n");
	free(str);
	return;
}

CBstring readCB() {
	char name[200] = "";
	char file_str[200];
	CBstring CBStr;
	char* str = (char*)malloc(sizeof(char) * 20005);
	char* chessboard = (char*)malloc(sizeof(char) * 20001);
	if (str == NULL) { printf("fail to malloc()!\n"); return; }
	if (chessboard == NULL) { printf("fail to malloc()!\n"); return; }
	str[0] = '\0';
	chessboard[0] = '\0';

	do {
		printf("Input the name of your chessboard which is in the output file(Input 0 to exit):\n");
		scanf("%s", name);
		if (strcmp(name, "0") == 0) { return ERRORCS; }
		else if (strlen(name) > 16) {
			printf("Your chessboard's name is too long.\n");
			setbuf(stdin, NULL); continue;
		}
		sprintf(file_str, "./output/%s.txt", name);
		if (access(file_str, 0) == -1) {
			printf("There is no file with the name.\n");
			setbuf(stdin, NULL); continue;
		}
		break;
	} while (1);

	FILE* file = fopen(file_str, "r");
	if (file == NULL) { printf("error!\n"); setbuf(stdin, NULL); return ERRORCS; };
	fscanf(file, "%s", str);
	char* b = strchr(str, '-');
	char* p = strrchr(str, '-');
	char* temp = (char*)malloc(sizeof(char) * 20005);
	if (temp == NULL) { printf("fail to malloc()!\n"); return; }
	temp[0] = '\0';

	strcpy(temp, str);
	char line_str[3], column_str[3];
	temp[(int)(b - str)] = '\0';
	strcpy(line_str, temp);

	strcpy(temp, str);
	temp[(int)(p - str)] = '\0';
	strcpy(column_str, temp + (b - str) + 1);

	strcpy(temp, str);
	strcpy(chessboard, temp + (p - str) + 1);

	CBStr.line = atoi(line_str);
	CBStr.column = atoi(column_str);
	CBStr.chessboard = chessboard;

	free(str);
	free(temp);
	str = NULL;
	temp = NULL;
	return CBStr;
}