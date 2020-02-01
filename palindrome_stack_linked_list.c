#include<stdio.h>
#include<stdlib.h>

typedef struct _Stack
{
    char c;
    struct _Stack *next;
}Stack;

Stack *push(Stack*,char);
Stack *pop(Stack*);
int    isPallindrome(char*);

int main()
{
    char str[200];

    printf("\nEnter a String : ");
    gets(str);

    if(isPallindrome(str))
        printf("\nThe String is a Pallindrome..\n");
    else
        printf("\nThe String is Not a Pallindrome..\n");

    main();
    return 0;
}

Stack *push(Stack *top,char c)
{
    Stack *nd = (Stack*)malloc(sizeof(Stack));
    nd->c = c;
    nd->next = top;

    return nd;
}

Stack *pop(Stack *top)
{
 if(top)
 {
  Stack *tmp = top;
  top = top->next;
  free(tmp);
 }
 return top;
}

int isPallindrome(char *str)
{
    Stack *top = '\0';
    int i;

    for(i=0;str[i];i++)
        top = push(top,str[i]);

    //The efficiency can be increased
    /*
    for(i=0;str[i];i++)
    {
        if(str[i]==top->c)
            top = pop(top);
        else
            break;
    }
    */

    //Just on cost of one int variable,we can reduce time by half of previous loop
    int j=0;
    for(i=0;str[i];i++)
    {
        if(str[i]==top->c)
        {
            top = pop(top);
            j++;
        }
        else if(j==i)
            break;
        else
            break;
    }

    return top=='\0';
}
