#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>

typedef struct _Stack
{
    float op;
    struct _Stack *next;
}Stack;

typedef struct
{
    char op;
    float val;
}SymbolTable;

Stack *push(Stack*,float);
Stack *pop(Stack*);
char  *postfix(char*);
int    isOperator(char);
int    isHigh(int,Stack*);
float  evaluate(char*);

int main()
{
    fflush(stdin);
    char ifx[50];
    char *pfx;
    float val;

    printf("\n");
    printf("\nEnter the Infix Expression     : ");
    gets(ifx);

    pfx = postfix(ifx);
    printf("\nPostfix Equivalent Expr        : %s\n",pfx);

    val = evaluate(pfx);
    printf("\nThe value of the expression is : %f",val);

    main();
    return 0;
}

Stack *push(Stack *top,float op)
{
    Stack *nd = (Stack*)malloc(sizeof(Stack));
    nd->op = op;
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

int isOperator(char op)
{
    if(op=='[' || op=='{' || op=='(')
        return '(';
    else if(op==']' || op=='}' || op==')')
        return ')';
    else
        return op=='^' || op=='+'|| op=='-'|| op=='*'|| op=='/';
}

int isHigh(int op,Stack *top)
{
    if(top=='\0'|| op=='('|| top->op=='(')
        return 1;
    if(op=='^' && (top->op=='*' || top->op=='/' || top->op=='+' || top->op=='-'))
        return 0;
    if((op=='/' || op=='*') && (top->op=='+' || top->op=='-'))
        return 1;

    return 0;
}

char *postfix(char *ifx)
{
    char *pfx,x;
    int i,j;
    Stack *top = '\0';

    for(i=0;ifx[i];i++);
    pfx = (char*)malloc(sizeof(char)*(i+1));

    for(i=j=0;ifx[i];i++)
    {
        x = ifx[i];
        if(isOperator(x))
        {
            if(isHigh(x,top))
                top = push(top,x);
            else
            {
                if(x==')')
                {
                    while(top->op!='(')
                    {
                        pfx[j++] = top->op;
                        top = pop(top);
                    }
                    top = pop(top);
                }
                else
                {
                    while(top && !(isHigh(x,top)))
                    {
                        pfx[j++] = top->op;
                        top = pop(top);
                    }
                    top = push(top,x);
                }
            }
        }
        else
            pfx[j++] = x;
    }
    while(top)
    {
        if(top->op==')')
            top = pop(top);
        else
            pfx[j++] = top->op;
        top = pop(top);
    }
    pfx[j] = '\0';

    return pfx;
}

float evaluate(char *pfx)
{
    SymbolTable st[10];
    int i,j,n;
    float x;
    Stack *top = '\0';

    printf("\n");
    for(n=i=0;pfx[i];i++)
    {
        if(!isOperator(pfx[i]))
        {
            for(j=0;j<n && pfx[i]!=st[j].op;j++);
            if(j==n)
            {
                float x;
                printf("Enter Value for Operand %c : ",pfx[i]);
                scanf("%f",&x);
                st[n].op = pfx[i];
                st[n].val = x;
                n++;
            }
        }
    }

    for(i=0;pfx[i];i++)
    {
        if(isOperator(pfx[i]))
        {
            float lft,ryt;

            ryt = top->op;
            top = pop(top);
            lft = top->op;
            top = pop(top);

            switch(pfx[i])
            {
                case '+' :  x = lft+ryt;
                            printf("+\n%f",x);
                            break;
                case '-' :  x = lft-ryt;
                            printf("-\n%f",x);
                            break;
                case '*' :  x = lft*ryt;
                            printf("*\n%f",x);
                            break;
                case '/' :  x = lft/ryt;
                            printf("/\n%f",x);
                            break;
                case '^' :  x = pow(lft,ryt);
                            printf("^\n%f",x);
                            break;
            }
            top = push(top,x);
        }
        else
        {
            for(j=0;st[j].op!=pfx[i];j++);
            top = push(top,st[j].val);
        }
    }

    x = top->op;
    top = pop(top);

    return x;
}
