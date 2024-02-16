#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main() 
{
    FILE *fp;
    char c;

    const char CR = '\015';
    const char LF = '\012';

    char fname[20];
    puts("Введите имя файла: \n");
    gets(fname);

    if ((fp = fopen(fname, "w")) == NULL) 
    {
        printf("%s", strerror(errno));
        return 1;
    }

    while ((c =  getchar()) != '#')
    {
        if (c == '\n') 
        {
            // putc(CR, fp);
            putc(LF, fp);
        }
        else putc(c, fp);
    }

    fclose(fp);
    return 0;
}