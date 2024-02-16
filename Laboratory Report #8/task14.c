#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int count_zeroes(double *array, size_t length);
double sum_after_min(double *array, size_t length);
void sort_by_abs(double *array, size_t length);
int count_max(double *array, size_t length);
void print_array(double *array, size_t length);
void fill_array(double *array, size_t length);
void fill_random_array(double *array, size_t length);

int main()
{
    int length; 

    printf("Input array length: ");
    scanf("%d", &length);

    if (length <= 0)
    {
        printf("Length can't be equals to or less zero.");
        return 0;
    }

    double *array = (double*) malloc (length * sizeof(double));

    // fill_random_array(array, length);
    fill_array(array, length);
    print_array(array, length);

    printf("1) %d \n", count_zeroes(array, length));
    printf("2) %lf \n", sum_after_min(array, length));
    sort_by_abs(array, length);
    printf("3) \n");
    print_array(array, length);
    printf("4) %d \n", count_max(array, length));

    free(array);
}

int count_zeroes(double *array, size_t length)
{
    int counter = 0;

    for (int i = 0; i < length; i++)
    {
        if (array[i] == 0)
            counter++;
    }    

    return counter;
}

double sum_after_min(double *array, size_t length)
{
    double min = array[0];
    double sum = 0;

    for (int i = 1; i < length; i++)
    {
        if (array[i] < min)
        {
            sum = 0;
            min = array[i];
        }
        else
        {
            sum += array[i];
        }
    }

    return sum;
}

void sort_by_abs(double *array, size_t length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < length; j++)
        {
            if (abs(array[minIndex]) > abs(array[j]))
                minIndex = j;
        }

        double temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}

int count_max(double *array, size_t length)
{
    const double eps = .001;
    int count = 1;
    double max = array[0];

    for (int i = 1; i < length; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
            count = 1;
        }
        else if (abs(array[i] - max) <= eps)
        {
            count++;
        }
    }

    return count;
}

void fill_random_array(double *array, size_t length)
{
    srand(time(NULL));
    
    for (int i = 0; i < length; i++)
    {
        double randomNumber = (double) rand();
        array[i] = randomNumber;
    }
}

void fill_array(double *array, size_t length)
{
    for (int i = 0; i < length; i++)
    {
        printf("Input %d element: ", i + 1);
        scanf("%lf", &array[i]);
    }
}

void print_array(double *array, size_t length)
{
    for (int i = 0; i < length; i++)
    {
        printf("Element #%d: %.2lf \n", i + 1, array[i]);
    }
}