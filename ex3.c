/* Assignment 4: Author- Daniel Grounin*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int** BuildMatrix(int* pRow, int* pColumn);
void freefunc(int** matrix, int row);
void printMatrix(int** matrix, int row, int column);
int** TransposeMatrix(int** matrix, int row, int col, int* pRow, int* pCol);

int main(){
	int pRow = 0, pCol = 0, row = 0, col = 0;
	int** matrix = NULL, matrix1 = NULL;
	matrix = BuildMatrix(&row, &col); //func get the adreeses of row & column 
	printMatrix(matrix, row, col); //func to print matrix
	matrix1 = TransposeMatrix(matrix, row, col, &pRow, &pCol); //reverse rows and columns, i to j and j to i.
	puts("\n");
	printMatrix(matrix1, pRow, pCol);
	free(matrix1, pRow);
	free(matrix, row);
	return 0;
}

int** BuildMatrix(int* pRow, int* pColumn){
	int** matrix;
	printf("Enter Row and Column :\n");
	scanf("%d %d", pRow, pColumn);
	matrix = (int**)malloc((*pRow) * (sizeof(int*)));
	if (matrix == 0){ //if 0 memory allocated
		puts("error");
		exit(1);
	}
	for (int i = 0; i < *pRow; i++){
		matrix[i] = (int*)malloc((*pColumn) * (sizeof(int)));
		if (matrix[i] == 0){
			puts("error");
			freefunc(matrix, i);
			exit(1);
		}
		for (int j = 0; j < *pColumn; j++){
			printf("enter elments :\n ");
			scanf("%d", &matrix[i][j]);
		}
	}
	return matrix;
}

void freefunc(int** matrix, int row){ //func to free up memory
	for (int i = 0; i < row; i++){
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;
}

void printMatrix(int** matrix, int row, int column){
	for (int i = 0; i < row; i++){
		for (int j = 0; j < column; j++){
			printf("%d ", matrix[i][j]);
		}
		puts("\n");
	}
}

int** TransposeMatrix(int** matrix, int row, int col, int* pRow, int* pCol){
	int** temp = (int**)malloc((col) * (sizeof(int*)));
	if (temp == 0){
		puts("error");
		exit(1);
	}
	for (int i = 0; i < col; i++){
		temp[i] = (int*)malloc((row) * (sizeof(int)));
		if (temp[i] == 0){
			puts("error");
			freefunc(temp, i);
			exit(1);
		}
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			temp[j][i] = matrix[i][j]; //reversed
		}
	}
		*pRow = col;
		*pCol = row;
	return temp;
}
