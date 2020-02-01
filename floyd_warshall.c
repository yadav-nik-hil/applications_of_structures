#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int V=0,E=0;
#define MAX 999999999


void display(int[][V]);
int  FloydWarshall(int[][V],int[][V]);


int main()
{
    int n,m,w,i,j,dir;
    do{
        printf("\nEnter the number of vertices :\t");
        scanf(" %d",&V);
    }while(V<=0);
    int graph[V][V],weight[V][V];
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            graph[i][j] = 0;
            weight[i][j] = MAX;
            if(i==j)
                //graph[i][j] = 1;          //self loops
                weight[i][j] = 0;
        }
    }

    do{
        printf("\nGraph is Directed[1] or UnDirected[0] : \t");
        scanf(" %d",&dir);
    }while(dir!=1 && dir!=0);

    printf("\nEnter the edges [pairs of vertices: u->v,w : weight][ -99 TO STOP ] : \n");
    while(1)
    {
        scanf(" %d%d%d",&n,&m,&w);
        if(n== -99 || m== -99)
            break;
        if(V-n+1 && V-m+1 &&n&&m &&n!=m)            // avoiding self loops
        {
            if(graph[n-1][m-1]==0)
                E++;
            graph[n-1][m-1] = 1;
            weight[n-1][m-1] = w;
            if(dir==0)
            {
                if(graph[m-1][n-1]==0)
                    E++;
                graph[m-1][n-1] = 1;
                weight[m-1][n-1] = w;
            }
        }
    }
    printf("\nNo. of Edges[Directed] = %d\n",E);

    printf("\n\tGraph : \n");
    display(graph);
    printf("\nWeights : \n");
    display(weight);

    int flag = FloydWarshall(graph,weight);
    if(flag)
    {
        printf("\nMinimum distance array is : \n");
        display(weight);
    }
    else
        printf("\nNegative Cycle Detected...\n");



    printf("\n\n....EXITING....\n\n");
    return 0;
}

void display(int graph[V][V])
{
    int i,j;
    printf("\n");
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
            printf(" %d ",graph[i][j]);
        printf("\n");
    }
    printf("\n---\n---\n---\n");
}

int FloydWarshall(int graph[V][V],int d[V][V])
{
    int i,j,k;
    for(k=0;k<V;k++)
    {
        for(j=0;j<V;j++)
        {
            for(i=0;i<V;i++)
            {
                if(d[j][i] > d[j][k] + d[k][i])
                    d[j][i] = d[j][k] + d[k][i];
            }
        }
    }

    for(i=0;i<V;i++)            //checks negative cycle
    {
        if(d[i][i]<0)
            return 0;
    }

    return 1;
}
