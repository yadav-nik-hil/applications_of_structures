#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<math.h>

#define MAX 999999999

typedef struct _node
{
    int vrtx;
    int wght;
    struct _node *next;
}Node;

typedef struct _list
{
    Node *head;
}List;

typedef struct _graph
{
    int V;
    List *arr;
}Graph;

int    Bellman_Ford(Graph*,int[]);
Node  *makeNode(int,int);
Graph *createGraph(int);
void   display(Graph*);
void   addEdge(Graph*,int,int,int);


int main()
{
    int n,m,w,i,dir;
    printf("\nEnter the number of vertices : \t");
    scanf(" %d",&i);
    Graph *graph=createGraph(i);

    do{
        printf("\nThe Graph is Directed[1] or UnDirected[0] : \t");
        scanf(" %d",&dir);
    }while(dir!=0 && dir!=1);
    printf("\nEnter the edges [pairs of vertices: u->v, w = weight][ -99 TO STOP ] : \n");
    while(1)
    {
        scanf(" %d%d%d",&n,&m,&w);
        if(n==-99 || m==-99)
            break;
        if(n==m)                // avoiding self loops
            continue;
        addEdge(graph,n,m,w);
        if(dir==0)
            addEdge(graph,m,n,w);
    }

    display(graph);

    int dist[graph->V];
    int flag = Bellman_Ford(graph,dist);
    if(flag)
    {
        for(i=0;i<graph->V;i++)
            printf("dist[ 1 , %d ] =  %d \n",i+1,dist[i]);
    }
    else
        printf("\nNegative Cycle detected!!\n");



    printf("\n\n....EXITING....\n\n");
    return 0;
}

Node *makeNode(int v,int w)
{
    Node *nd = (Node*)malloc(sizeof(Node));
    nd->vrtx = v;
    nd->wght = w;
    nd->next = NULL;

    return nd;
}

Graph *createGraph(int V)
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->arr = (List*)malloc(sizeof(List) * V);

    int i;
    for(i=0;i<V;i++)
        graph->arr[i].head = NULL;
    /*
    for(i=1;i<=V;i++)                   // Here while initializing graph, we addEdge(i,i) already
        addEdge(graph,i,i,0);
    */
    return graph;
}

void addEdge(Graph *graph,int u,int v,int w)
{
    if(graph && u!=v && u>=1&&v>=1 && u<=graph->V&&v<=graph->V)     // avoiding self loops
    {
        u--;
        Node *nd = makeNode(v,w),*prv=NULL,*ptr=graph->arr[u].head;
        while(ptr)
        {
            if(ptr->vrtx < v)
            {
                prv = ptr;
                ptr = ptr->next;
            }
            else if(ptr->vrtx == v)
                return;
            else
                break;
        }
        nd->next = ptr;
        if(prv)
            prv->next = nd;
        else
            graph->arr[u].head = nd;
    }
}

void display(Graph *graph)
{
    if(graph)
    {
        printf("\nHere is the Graph : \n");
        int i;
        Node *ptr;
        for(i=0;i<graph->V;i++)
        {
            printf("%d --> ",i+1);
            ptr = graph->arr[i].head;
            while(ptr)
            {
                printf(" [ %d (w = %d)] ",ptr->vrtx,ptr->wght);
                ptr = ptr->next;
            }
            printf("\n");
        }
    }
    else
        printf("\n---\n---\n---\n");
    printf("\n");
}

int Bellman_Ford(Graph *graph,int dist[])
{
    int i,j,k;
    Node *ptr;
    int d[graph->V];
    for(i=0;i<(graph->V);i++)
        d[i] = MAX;
    do{
        printf("\nEnter the source vertex : \t");
        scanf(" %d",&i);
    }while(i<=0 || i>graph->V);
    d[i-1] = 0;

    for(i=1;i<(graph->V);i++)
    {
        for(j=0;j<(graph->V);j++)
        {
            ptr = graph->arr[j].head;
            while(ptr)
            {
                if(d[ptr->vrtx-1] > d[j] + ptr->wght)
                    d[ptr->vrtx-1] = d[j] + ptr->wght;
                ptr = ptr->next;
            }
        }
    }

    for(i=0;i<(graph->V);i++)               // Checks for -ve cycle
    {
        ptr = graph->arr[i].head;
        while(ptr)
        {
            if(d[ptr->vrtx-1] > d[i] + ptr->wght)
                return 0;
            ptr = ptr->next;
        }
    }

    for(i=0;i<graph->V;i++)
        dist[i] = d[i];

    return 1;
}
