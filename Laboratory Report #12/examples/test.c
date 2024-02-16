#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char path[] = "../files/text1.txt";
    char mode[] = "r";

    if ((fp = fopen(path, mode)) == NULL) 
    {
        printf("NONONO");
        printf("%s", strerror(errno));
        exit(0);
    }

    int fclose(fp);
}