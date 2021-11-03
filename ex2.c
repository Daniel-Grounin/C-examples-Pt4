/* Assignment 4: Author- Daniel Grounin*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
int* SymmetricDiff(int* one, int sizeOne, int* two, int sizeTwo, int* pNewSize);

int main() {

	int* arrOne = NULL;
	int* arrTwo = NULL;
	int sizeOne = 10;
	int sizeTwo = 10;
	int newSize;
	int* Sym_NewArr;
	arrOne = NULL;
	printf("PLEASE ENTER SIZE OF ARRAY ONE: \n\n");
	scanf("%d", &sizeOne);
	arrOne = (int*)malloc(sizeOne * sizeof(int));
	for (int i = 0; i < sizeOne; i++){
		printf("Enter %d's element of array One\n", i + 1);
		scanf("%d", &arrOne[i]);
	}
	arrTwo = NULL;
	printf("\nPLEASE ENTER SIZE OF ARRAY TWO: \n\n");
	scanf("%d", &sizeTwo);
	arrTwo = (int*)malloc(sizeTwo * sizeof(int));
	for (int i = 0; i < sizeTwo; i++){
		printf("Enter %d's element of array Two\n", i + 1);
		scanf("%d", &arrTwo[i]);
	}
	Sym_NewArr = SymmetricDiff(arrOne, sizeOne, arrTwo, sizeTwo, &newSize);
}

int* SymmetricDiff(int* one, int sizeOne, int* two, int sizeTwo, int* pNewSize){
	*pNewSize = 0;
	int* NewArr = (int*)malloc(20 * sizeof(int));
	int count = 0;
	int flag = 0;
	for (int i = 0; i < sizeOne; i++) {
		for (int j = 0; j < sizeTwo; j++) {

			if (one[i] == two[j])
				break;
			if (j == sizeTwo - 1) {
				NewArr[count] = one[i];
				count++;
				flag = 1;
			}
		}
	}
	for (int i = 0; i < sizeTwo; i++) {
		for (int j = 0; j < sizeOne; j++) {
			if (two[i] == one[j])
				break;
			if (j == sizeOne - 1) {
				NewArr[count] = two[i];
				count++;
				flag = 1;;
			}
		}
	}
	*pNewSize = count;
	if (flag == 0) printf("\nThe New array is empty.\n");
	printf("The new array size is %d\n", *pNewSize);
	printf("\n\n");
	for (int i = 0; i < *pNewSize; i++){
		printf("%d ", NewArr[i]);
	}
	printf("\n");
	return NewArr;
}