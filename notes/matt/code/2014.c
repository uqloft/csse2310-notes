#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char* read_line(FILE* file) {
	char* buff = malloc(sizeof(char) * 80);
	int buffSize = 0;
	int next = 0;
	while(1) {
		next = fgetc(file);
		if (next == EOF || next == '\n') {
			buff[buffSize] = '\0';
			return buff;
		} else {
			buff[buffSize++] = (char)next;
		}
	}
}

int sorter(const void* s1, const void* s2) {
	const char* a1 = *(char**)s1;
	const char* a2 = *(char**)s2;
	return strcmp(a1, a2);
}

int sort_strings(char** argv) {
	FILE* readFile = fopen(argv[1], "r");
	FILE* writeFile = fopen(argv[2], "w");

	if (readFile == NULL || writeFile == NULL) {
		printf("Invalid Files\n");
		return 1;
	}

	int arrSize = 0;
	char** readStrings = malloc(sizeof(char*));
	char* readLine = read_line(readFile);
	while (readLine[0] != '\0') {
		readStrings = realloc(readStrings, sizeof(char*) * arrSize + 1);
		readStrings[arrSize] = malloc(sizeof(char));
		readStrings[arrSize++] = readLine;
		readLine = read_line(readFile);
	}
	qsort(readStrings, arrSize, sizeof(char*), sorter);
	for (int i = 0; i < arrSize; i++) {
		fprintf(writeFile, "%s\n", readStrings[i]);
	}
	return 0;
}

void print_chopped(int n, char c, char* line) {
	char* new = malloc(sizeof(char) * 80);
	int columnCounter = 0;
	int size = 0;
	for (int i = 0; i < strlen(line); i++) {
		if (line[i] == c) {
			columnCounter++;
		} else if (columnCounter == n) {
			new[size++] = line[i];
		}  
	}
	new[size] = '\0';
	printf("%s\n", new);
}

bool chopLines(int n, char c, const char* filename) {
	FILE* file = fopen(filename, "r");
	char* buff = malloc(sizeof(char) * 80);
	int buffSize = 0;
	int next = 0;
	while(1) {
		next = fgetc(file);
		if (next == EOF) {
			buff[buffSize] = '\0';
			print_chopped(n, c, buff);
			break;
		} else if (next == '\n') {
			buff[buffSize] = '\0';
			print_chopped(n, c, buff);
			buff = malloc(sizeof(char) * 80);
			buffSize = 0;
		} else {
			buff[buffSize++] = next;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	chopLines(1, ' ', argv[1]);
}










