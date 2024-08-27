#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void calculateMatrixSize(int **matrix, int rows, int cols);
void readMatrixSize(int *size);
void createMatrix(int ***matrix, int size);
void fillMatrix(int **matrix, int size);
void printMatrix(int **matrix, int size);
void clearMatrix(int ***matrix, int size);
void writeMatrixToFile(int **matrix, int size, const char *filename, char key);
void readMatrixFromFile(int ***matrix, int *size, const char *filename, char key);
void encryptDecrypt(char *data, char key);

int main()
{
	int size;
	char plaintext[1024];
	// char key[1024];
	char ciphertext[1024];
	char decryptedtext[1024];

	readMatrixSize(&size);

	int **matrix = NULL;
	char key = 'K';

	createMatrix(&matrix, size);
	fillMatrix(matrix, size);
	calculateMatrixSize(matrix, size, size);

	writeMatrixToFile(matrix, size, "encrypted", key);

	printMatrix(matrix, size);
	clearMatrix(&matrix, size);
	createMatrix(&matrix, size);

	readMatrixFromFile(&matrix, &size, "encrypted", key);
	printMatrix(matrix, size);

	// clearMatrix(&matrix, size);

	return 0;
}

void clearMatrix(int ***matrix, int size)
{
	printf("\nClearing the matrix\n\n");

	if (matrix && *matrix)
	{
		for (int i = 0; i < size; i++)
			if ((*matrix)[i])
			{
				free((*matrix)[i]);
				(*matrix)[i] = NULL;
			}

		free(*matrix);
		*matrix = NULL;
		printf("Matrix cleared successfully\n");
	}
	else
	{
		printf("Matrix pointer is NULL\n");
	}
}

void calculateMatrixSize(int **matrix, int rows, int cols)
{
	size_t totalSize = rows * sizeof(int *);
	for (int i = 0; i < rows; i++)
		totalSize += cols * sizeof(int);
	printf("Total memory size of the matrix: %zu bytes\n", totalSize);
}

void readMatrixSize(int *size)
{
	printf("Enter the size of the matrix: ");
	while (scanf("%d", size) != 1 || *size <= 0)
	{
		printf("Invalid Input, please enter a positive integer: ");
		while (getchar() != '\n')
			;
	}
}

void createMatrix(int ***matrix, int size)
{
	*matrix = malloc(size * sizeof(int *));
	if (*matrix == NULL)
	{
		printf("Memory allocation failed!\n");
		return;
	}

	for (int i = 0; i < size; i++)
	{
		(*matrix)[i] = malloc(size * sizeof(int));
		if ((*matrix)[i] == NULL)
		{
			printf("Memory allocation failed!\n");
			// Free previously allocated memory before returning
			for (int j = 0; j < i; j++)
				free((*matrix)[j]);
			free(*matrix);
			return;
		}
	}
	printf("Matrix created successfully!\n");
}

void fillMatrix(int **matrix, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] = i * size + j + 1;

	printf("Matrix filled!\n");
}

void printMatrix(int **matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}
}

void writeMatrixToFile(int **matrix, int size, const char *filename, char key)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Failed to open file %s for writing.\n", filename);
		return;
	}

	char *buffer = malloc(size * size * 20);
	if (buffer == NULL)
	{
		printf("Memory allocation failed!\n");
		fclose(file);
		return;
	}

	char *ptr = buffer;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			ptr += sprintf(ptr, "%d\t", matrix[i][j]);
		ptr += sprintf(ptr, "\n");
	}

	encryptDecrypt(buffer, key);
	fwrite(buffer, sizeof(char), strlen(buffer), file);

	free(buffer);
	fclose(file);

	printf("Matrix written to %s\n", filename);
}

void readMatrixFromFile(int ***matrix, int *size, const char *filename, char key)
{

	if (*matrix == NULL)
	{
		printf("Matrix is already cleared. Cannot read from file.\n");
		return;
	}

	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Failed to open file %s for reading.\n", filename);
		return;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = malloc(fileSize + 1);
	if (buffer == NULL)
	{
		printf("Memory allocation failed!\n");
		fclose(file);
		return;
	}

	fread(buffer, 1, fileSize, file);
	buffer[fileSize] = '\0';

	encryptDecrypt(buffer, key);

	char *ptr = buffer;
	sscanf(ptr, "%d", size);

	createMatrix(matrix, *size);

	for (int i = 0; i < *size; i++) {
		for (int j = 0; j < *size; j++) {
			sscanf(ptr, "%d", &(*matrix)[i][j]);
			while(*ptr != '\t' && *ptr != '\n') ptr++;
			if (*ptr == '\t') ptr++;
		}
		while (*ptr != '\n') ptr++;
		ptr++;
	}

	free(buffer);
	fclose(file);
	printf("Matrix read from %s\n", filename);
}

void encryptDecrypt(char *data, char key)
{
	while (*data)
	{
		*data ^= key;
		data++;
	}
}