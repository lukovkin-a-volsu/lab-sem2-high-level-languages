#include <stdio.h>
#include <errno.h>

int main() 
{
    FILE *fp;
    char c;
    char fname[20];

    puts("Введите имя файла: \n");
    gets(fname);

    if ((fp = fopen(fname, "r")) == NULL) 
    {
        printf("%s", strerror(errno));
        return 1;
    }

    while ((c = getc(fp)) != EOF)
        putchar(c);
    
    fclose(fp);
    return 0;
}