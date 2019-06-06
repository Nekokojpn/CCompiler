#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum{
    TK_NUM=256,
    TK_EOF,
};

typedef struct{
    int ty;
    int val;
    char *input;
}Token;

char *input;

Token tokens[100];

void error(char *fmt,...){
    va_list ap;
    va_start(ap,fmt);
    vfprintf(stderr,fmt,ap);
    fprintf(stderr,"\n");
    exit(1);
}

void error_at(char *loc, char *msg){
    int pos = loc - input;
    fprintf(stderr, "%s\n",input);
    fprintf(stderr,"%*s",pos,"");
    fprintf(stderr,"^ %s\n",msg);
    exit(1);
}
void tokenize(){
    char *p = input;
    int i = 0;
    while(*p){
        if(isspace(*p)){
            p++;
            continue;
        }
        if(*p=='+'||*p=='-'){
            tokens[i].ty = *p;
            tokens[i].input = p;
            i++;
            p++;
            continue;
        }
        if(isdigit(*p)){
            tokens[i].ty = TK_NUM;
            tokens[i].input = p;
            tokens[i].val = strtol(p,&p,10);
            i++;
            continue;
        }
        error_at(p,"Unknown token, Exit.");
    }
    tokens[i].ty=TK_EOF;
    tokens[i].input = p;
}
int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Invalid args.\n");
        return 1;
    }

    char *p = argv[1];

    printf(".intel_syntax noprefix\n");
    printf(".global main\n");
    printf("main:\n");
    printf("  mov rax, %ld\n", strtol(p, &p, 10));

    while(*p){
        if(*p == '+'){
            p++;
            printf("    add rax, %ld\n",strtol(p,&p,10));
            continue;
        }
        if(*p == '-'){
            p++;
            printf("    sub rax, %ld\n",strtol(p,&p,10));
            continue;
        }

        fprintf(stderr, "Unanticipated char: '%c'\n",*p);
        return 1;
    }
    printf("    ret\n");
    return 0;
}