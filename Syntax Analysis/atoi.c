#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    unsigned char *key = "s";
    unsigned int hash = 0;

    while (*key)
    {
        printf("%s \n", key);
        hash += (unsigned char)*key++;
        printf("Value: %d \n", hash);
    }
    printf("Value FINAL: %d \n", hash);
}