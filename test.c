#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    char *p;
    p = argv[1];
    printf("input:%ld\n",strtol(p,&p,10));
}