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
	char* chessboard = (char*)malloc(sizeof(char) * 20001);
	if (chessboard == NULL) { printf("fail to malloc()!\n"); return ERRORCS; }
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
	int line, column;
	FILE* file = fopen(file_str, "r");
	if (file == NULL) { printf("error!\n"); setbuf(stdin, NULL); return ERRORCS; };
	fscanf(file, "%d-%d-%s",&line, &column, chessboard);

	CBStr.line = line;
	CBStr.column = column;
	CBStr.chessboard = chessboard;

	return CBStr;
}