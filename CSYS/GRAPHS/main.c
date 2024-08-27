#include <stdlib.h>
#include <stdio.h>

size_t calculateMatrixSize(int **matrix, int rows, int cols)
{
	size_t totalSize = rows * sizeof(int *);
	for (int i = 0; i < rows; i++)
		totalSize += cols * sizeof(int);
	return totalSize;
}

void readMatrixSize(int *size)
{
	printf("Enter the size of the matrix: ");
	while (scanf("%d", size) != 1 || *size <= 0)
	{
		printf("Invalid Input, please enter a positive integer: ");
		while (getchar() != '\n');
	}
}

int main()
{
	int size;
	int **matrix = NULL;

	readMatrixSize(&size);

	matrix = malloc(size * sizeof(int *));

	if (matrix == NULL)
	{
		printf("Memory allocation failed!\n");
		return 1;
	}

	for (int i = 0; i < size; i++)
	{
		matrix[i] = malloc(size * sizeof(int));
		if (matrix[i] == NULL)
		{
			printf("Memory allocation failed!\n");
			return 1;
		}
	}

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] = i * size + j + 1;

	printf("Matrix ready!\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}

	size_t matrixSize = calculateMatrixSize(matrix, size, size);
	printf("Total memory size of the matrix: %zu bytes\n", matrixSize);

	printf("\nClearing the matrix\n\n");
	for (int i = 0; i < size; i++)
		free(matrix[i]);
	free(matrix);

	return 0;
}
