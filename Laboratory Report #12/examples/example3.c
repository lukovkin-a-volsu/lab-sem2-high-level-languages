#include <stdio.h>

int main() 
{
    FILE *fp;
    int n;

    char path[] = "../files/example2.txt";

    if ((fp = fopen(path, "w")) == NULL)
    {
        perror(path);
        return 1;
    }

    for (n = 1; n < 11; n++)
    {
        fprintf(fp, "%d %d\n", n, n*n);
    }

    fclose(fp);
}