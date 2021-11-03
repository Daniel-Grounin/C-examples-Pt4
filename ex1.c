/* Assignment 4: Author- Daniel Grounin*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
char** CreateStr(int* countWords);
char** ToLowerCase(char** words, int size, int* newSize);
void wordFrequency(char** words, int countWords);
char** textPreprocessing(char** words, int* countWords, char** stopwords, int countStopwords);
void freefunc(char** str, int size);

int main(){
	char** words = NULL, * stopwords = NULL, * newWords = NULL; //get rid of garbage values
	int count = 0, countStopwords = 0, countNewwords = 0;
	words = CreateStr(&count); //create string
	newWords = ToLowerCase(words, count, &countNewwords); //lower case the string and buffer overflow for numbers.
	freefunc(words, count);
	stopwords = CreateStr(&countStopwords); //create string
	words = NULL;
	words = textPreprocessing(newWords, &countNewwords, stopwords, countStopwords);
	wordFrequency(words, countNewwords); //determine how many times words apear.
	freefunc(words, countNewwords);
	freefunc(stopwords, countStopwords);

	return 0;
}

void wordFrequency(char** words, int countWords){ //תדירות המילים{
	int count = 1, i, j;
	for (i = 0; i < countWords; i++){
		count = 0;
		for (j = i; j < countWords; j++){
			if (strcmp(words[i], words[j]) == 0){ //string compare, if == 0 ,equal.
				count += 1;
			}
		}
		for (j = 0; j < i; j++){
			if (strcmp(words[i], words[j]) == 0) //in string check duplicates
				break;
		}
		if (j == i){
			printf("\n%s - %d", words[i], count);
		}
	}
	puts("\n");
}

char** CreateStr(int* countWords){   //create array of strings 
	char buffer[10 + 1]; //plus 1 for '\0'
	char** wordsAlloc = NULL;
	puts("Hello, Please enter the amount of words:");
	scanf("%d", countWords);
	getchar();
	wordsAlloc = (char**)malloc((*countWords) * sizeof(char*)); //words allocation
	puts("Enter them:");
	int i = 0;
	while (i < (*countWords)){
		scanf("%s", buffer); //scan string
		wordsAlloc[i] = (char*)malloc(strlen(buffer) + 1); //allocate memory one by on
		if (wordsAlloc == NULL){ //if not allocated
			freefunc(wordsAlloc, i);
			exit(1);
		}
		strcpy(wordsAlloc[i], buffer); //string copy function
		i++;
	}
	return wordsAlloc;
}
char** ToLowerCase(char** words, int size, int* newSize){ //convert all to lower case
	char** tempAlloc = NULL;
	int i = 0, j = 0, flag = 0, counter = 0;
	while (i < size){
		flag = 1;
		while (j < strlen(words[i])){
			if (words[i][j] >= '0' && words[i][j] <= '9'){ //numbers part 
				flag = 0;
			}
			if (words[i][j] >= 'A' && words[i][j] <= 'Z'){ //checks in ASCII table 
				words[i][j] += 'a' - 'A'; //or 32
			}
			j++;
		}
		if (flag == 1){
			counter++;
			tempAlloc = (char**)realloc(tempAlloc, counter * sizeof(char*)); //memory allocation 
			if (tempAlloc == NULL){  //if not allocated
				puts("Memory free'd!\n");
				freefunc(words, size);  //free memory
				exit(1);
			}
			tempAlloc[counter - 1] = (char*)malloc(strlen(words[i]) + 1);
			if (tempAlloc[counter - 1] == NULL){
				puts("Memory free'd!\n");
				freefunc(words, size);
				freefunc(tempAlloc, counter);
				exit(1);
			}
			strcpy(tempAlloc[counter - 1], words[i]);
		}
		i++;
	}
	*newSize = counter;
	return tempAlloc;
}

char** textPreprocessing(char** words, int* countWords, char** stopwords, int countStopwords){
	char** tempAlloc = NULL;
	int i = 0, counter = 0, flag = 0;
	while (i < *countWords){
		flag = 1;
		for (int j = 0; j < countStopwords; j++){
			if (strcmp(words[i], stopwords[j]) == 0){ //if entered same words 
				flag = 0;
			}
		}
		if (flag == 1){
			counter++; //count words for new allocation
			tempAlloc = (char**)realloc(tempAlloc, counter * sizeof(char*));
			if (tempAlloc == NULL){
				puts("Memory free'd\n");
				freefunc(words, *countWords);
				freefunc(stopwords, countStopwords);
				exit(1);
			}
			tempAlloc[counter - 1] = (char*)malloc(strlen(words[i]) + 1);

			if (tempAlloc[counter - 1] == NULL){
				puts("Memory free'd\n");
				freefunc(words, *countWords);
				freefunc(stopwords, countStopwords);
				freefunc(tempAlloc, counter);
				exit(1);
			}
			strcpy(tempAlloc[counter - 1], words[i]);
		}
		i++;
	}
	*countWords = counter;
	return tempAlloc;
}
void freefunc(char** str, int size){ //free allocation function
	for (int j = 0; j < size; j++){
		free(str[j]);
	}
	free(str);
}
