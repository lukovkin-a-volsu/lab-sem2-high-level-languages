#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int rows, int columns);
void fill_random_matrix(int** matrix, int nrows, int ncolumns);
void fill_matrix(int** matrix, int nrows, int ncolumns);
void print_matrix(int** matrix, int nrows, int ncolumns);
void cyclical_shift(int** matrix, int offset, int i0, int j0, int i1, int j1);
int is_matrix_orthonormal(int** matrix, int nrows, int ncolumns);
double mean_multiple_of(int** matrix, int nrows, int ncolumns, int multipleOfRow, int multipleOfColumn);
int* numbers_of_rows_with_alternating_signs(int** matrix, int nrows, int ncolumns);

int main()
{
    int ROWS = 3;
    int COLUMNS = 3;  
    int r = 2, s = 2;

    /*
    printf("Please input quantity of rows and columns:\n");
    scanf("%d %d", &ROWS, &COLUMNS);
    printf("Please input numbers that will be the multiplicity, row and column:\n");
    scanf("%d %d", &r, &s);
    */  
    int** matrix = (int**) create_matrix(ROWS, COLUMNS);

    // initialize matrix
    // fill_random_matrix(matrix, ROWS, COLUMNS);
    fill_matrix(matrix, ROWS, COLUMNS);
    print_matrix(matrix, ROWS, COLUMNS);
    // function from task #4 called here, because they matrix will change in task #1
    int* numbers = numbers_of_rows_with_alternating_signs(matrix, ROWS, COLUMNS);

    // task #1
    cyclical_shift(matrix, 3, 0, 0, 2, 2);
    print_matrix(matrix, ROWS, COLUMNS); 
    
    // task #2
    // task #1 does not affect the orthonormality of the matrix
    int is_orthonormal = is_matrix_orthonormal(matrix, ROWS, COLUMNS);
    if (is_orthonormal == 0) 
        printf("\nMatrix is orthonormal.");
    else
        printf("\nMatrix IS NOT orthonormal.");

    // task #3
    double mean = mean_multiple_of(matrix, ROWS, COLUMNS, r, s);
    printf("\nThe mean value of elements, where row and column multiple of %d and %d is equals to %lf \n", r, s, mean);

    // task #4
    // int* numbers = numbers_of_rows_with_alternating_signs(matrix, ROWS, COLUMNS);
    if (numbers != NULL)
    {
        printf("Rows with alternating signs: \n");

        int size = sizeof(numbers) / sizeof(int);
        for (int i = 0; ; i++) 
        {
            if (numbers[i] == -1)
                break;

            printf("%d \t", numbers[i]);
        }
    }
    else
    {
        printf("Matrix has no rows with alernating signs.");
    }


    return 0;
}

int** create_matrix(int rows, int columns)
{
    int** matrix = (int**) malloc(sizeof(int*) * rows);

    for (int i = 0; i < rows; i++)
        matrix[i] = (int*) malloc(columns * sizeof(int));

    return matrix;
}

void fill_random_matrix(int** matrix, int nrows, int ncolumns)
{
    srand(time(NULL));

    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncolumns; j++)
            matrix[i][j] = 1000 + rand() % 9000;
}

void fill_matrix(int** matrix, int nrows, int ncolumns) 
{
    for (int i = 0; i < nrows; i++) 
        for (int j = 0; j < ncolumns; j++)
            scanf("%d", &matrix[i][j]);
}

void print_matrix(int** matrix, int nrows, int ncolumns)
{
    printf("\n---Array: %p---\n", &matrix);

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncolumns; j++)
            printf("%8d ", matrix[i][j]);
        
        printf("\n");
    }

    printf("---\n");
}

void cyclical_shift(int** matrix, int offset, int i0, int j0, int i1, int j1)
{
    offset %= 4;

    if (offset == 0)
        return;

    int** shifted_matrix = create_matrix(i1 - i0, j1 - j0);
    int is_debugging = 1;

    for (int k = 0; k < offset; k++)
    {
        for (int i = i0; i < i1; i++)
        {
            for (int j = j0; j < j1; j++)
            {
                shifted_matrix[j - j0][i1 - 1 - i - i0] = matrix[i][j];
            }
        }

        if (is_debugging == 1)
            print_matrix(shifted_matrix, i1 - i0, j1 - j0);

        for (int i = i0; i < i1; i++)
        {
            for (int j = j0; j < j1; j++)
            {
                matrix[i - i0][j - j0] = shifted_matrix[i][j];
            }
        }
    }
}

int is_matrix_orthonormal(int** matrix, int nrows, int ncolumns) 
{
    for (int i = 0; i < ncolumns - 1; i++) 
    {
        for (int j = i  + 1; j < ncolumns; j++) 
        {
            int sum = 0;

            for (int k = 0; k < nrows; k++) 
                sum += matrix[k][i] * matrix[k][j];

            if (sum != 0)
                return 1;
        }
    }

    return 0;
}

double mean_multiple_of(int** matrix, int nrows, int ncolumns, int multipleOfRow, int multipleOfColumn) 
{
    double sum = 0;
    int count = 0;

    for (int i = 0; i < nrows; i++) 
    {
        for (int j = 0; j < ncolumns; j++)
        {
            // 'cause the index starts with 0 we add 1 
            if ((i + 1) % multipleOfRow == 0 && (j + 1) % multipleOfColumn == 0)
            {
                count++;
                sum += matrix[i][j];
            }
        }
    }
    
    sum /= count;
    return sum;
}

int* numbers_of_rows_with_alternating_signs(int** matrix, int nrows, int ncolumns)
{
    if (nrows < 1 || ncolumns < 1) return NULL;

    int* numbers = (int*) malloc(sizeof(int) * nrows);
    int index = 0;

    for (int i = 0; i < nrows; i++)
    {
        int is_positive = matrix[i][0] > 0 ? 1 : -1;
        int is_acceptable = 0;

        for (int j = 0; j < ncolumns; j++)
        {
            // is_positive == 1 -> positive
            if (is_positive == 1 && matrix[i][j] != abs(matrix[i][j]))
            {
                is_acceptable = 1;
                break;
            }
            // is_positive == -1 -> negative
            else if (is_positive == -1 && matrix[i][j] == abs(matrix[i][j]))
            {
                is_acceptable = 1;
                break;
            } 

            is_positive *= -1;
        }

        if (is_acceptable == 0)
            numbers[index++] = i + 1; // add 1 because number of line starts with 1
    }

    if (index == 0) return NULL;

    numbers = (int*) realloc(numbers, ++index);
    numbers[index - 1] = -1;

    return numbers;
}