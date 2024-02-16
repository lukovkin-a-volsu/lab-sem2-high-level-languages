#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int size = 0;
    int i, imax, imin, ibeg, iend, counter;

    printf("Input array size: ");
    scanf("%d", &size);

    int *a = (int*) malloc(size * sizeof(int));

    for (i = imax = imin = 0; i < size; i++)
    {
        printf("Input %d element: ", i + 1);
        scanf("%d", &a[i]);

        if (a[i] > a[imax])
            imax = i;
        if (a[i] < a[imin])
            imin = i;
    }

    printf("\n max = %d\t min = %d\t \n", a[imax], a[imin]);
    ibeg = imax < imin ? imax : imin;
    iend = imax < imin ? imin : imax;
    printf("\n ibeg = %d\t iend = %d\t \n", ibeg, iend);

    for (counter = 0, i = ibeg + 1; i < iend; i++)
        if (a[i] > 0)
            counter++;

    printf("\n The number of positive elements = %d\n", counter);
    return 0;
}