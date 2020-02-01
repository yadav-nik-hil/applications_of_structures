#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int i,j;

    // Minimizing the wastage of space
    char *stra = (char*)malloc(sizeof(char)*100);
    char *strb = (char*)malloc(sizeof(char)*100);
    printf("\nEnter the strings : \n");
    scanf(" %s",stra);
    scanf(" %s",strb);
    char *a = (char*)malloc(sizeof(char)*(strlen(stra)+1));
    char *b = (char*)malloc(sizeof(char)*(strlen(strb)+1));
    strcpy(a,stra);
    strcpy(b,strb);
    free(stra);
    free(strb);

    int c[strlen(a)+1][strlen(b)+1];
    for(i=0;i<=strlen(a);i++)                   //Initializing the 2D array
        c[i][0] = 0;
    for(j=0;j<=strlen(b);j++)
        c[0][j] = 0;

    for(i=1;i<=strlen(a);i++)                   // Iterating the array with specified relations
    {
        for(j=1;j<=strlen(b);j++)
        {
            if(a[i-1]==b[j-1])
                c[i][j] = c[i-1][j-1] +1;
            else
                c[i][j] = (c[i-1][j]>c[i][j-1]) ? c[i-1][j] : c[i][j-1];
        }
    }

    const int len = c[strlen(a)][strlen(b)];
    printf("\nLongest Common Subsequence Length = %d\n",len);
    /*
    for(i=0;i<=strlen(a);i++)
    {
        for(j=0;j<=strlen(b);j++)
            printf(" %d ",c[i][j]);

        printf("\n");
    }
    */

    char LCS[len+1];
    LCS[len] = '\0';
    int k = len-1;

    //Finding the longest common subsequence
    i = strlen(a);
    j = strlen(b);
    while(i>0&&j>0&&k>=0)
    {

        if(a[i-1]==b[j-1])
        {
            LCS[k--] = a[i-1];
            i--;
            j--;
        }
        else if(c[i-1][j] > c[i][j-1])
            i--;
        else        //c[i][j-1] > c[i-1][j]
            j--;
    }
    printf("\nLongest Common Subsequnce = %s\n",LCS);


    return 0;
}
