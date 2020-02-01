#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int V=0,E=0;
#define MAX 999999999


void display(int[][V]);
int  *DFS(int[][V],int);


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

    do{
        printf("\nEnter the source vertex : \t");
        scanf(" %d",&i);
    }while(i<=0 || i >V);
    int *dfs = DFS(graph,i);
    printf("\nDFS Traversal is : \n");
    for(i=0;i<V;i++)
        printf(" %d ",dfs[i]);



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

int *DFS(int graph[V][V],int s)
{
    int i,u,k;
    int visited[V],Stack[V],top= -1;
    int *arr = (int*)malloc(sizeof(int)*V);

    for(i=0;i<V;i++)
        visited[i] = 0;
    Stack[++top] = s;

    k=0;
    while(top>=0)
    {
        u = Stack[top--];
        if(visited[u-1]==0)
        {
            arr[k++] = u;
            visited[u-1] = 1;
            for(i=V;i>=1;i--)
            {
                if(graph[u-1][i-1])
                {
                    if(visited[i-1]==0)
                        Stack[++top] = i;
                }
            }
            printf("\nStack : ");
            for(i=0;i<=top;i++)
                printf(" %d ",Stack[i]);
            printf("\n\n");
        }
    }

    return arr;
}
