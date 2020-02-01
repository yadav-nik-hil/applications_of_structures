#include<stdlib.h>
#include<stdio.h>
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


int   *BFS(Graph*,int);
Node  *makeNode(int,int);
Graph *createGraph(int);
void   display(Graph*);
void   addEdge(Graph*,int,int,int);


int main()
{
    int n,m,w,i;
    printf("\nEnter the number of vertices : \t");
    scanf(" %d",&i);
    Graph *graph = createGraph(i);

    printf("\nEnter the edges [pairs of vertices: u->v, w = weight][ -99 TO STOP ] : \n");
    while(1)
    {
        scanf(" %d%d%d",&n,&m,&w);
        if(n==-99 || m==-99)
            break;
        addEdge(graph,n,m,w);
    }

    display(graph);


    do{
        printf("\nEnter the source node for BFS : \t");
        scanf(" %d",&i);
    }while(i<=0 || i>(graph->V));

    int *dist = BFS(graph,i);

    printf("\nPrinting the distance array [ BFS ] : \n");
    for(i=0;i<graph->V;i++)
        printf("dist[%d] = %d\n",i+1,dist[i]);




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
    for(i=1;i<=V;i++)                   // self loops
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

int *BFS(Graph *graph,int s)
{
    Node *ptr;
    int i,u,front=0,rear=-1;
    int visited[graph->V],parent[graph->V],Queue[graph->V];
    int *d = (int*)malloc(sizeof(int)*(graph->V));

    for(i=0;i<graph->V;i++)
        visited[i] = d[i] = parent[i] = 0;
    parent[s-1] = s;
    visited[s-1] = 1;
    Queue[++rear] = s;

    while(rear>=front)              // ==   ! isEmpty(Queue)
    {
        u = Queue[front++];         //u = deQueue(Queue);
        ptr = graph->arr[u-1].head;
        while(ptr)
        {
            if(visited[ptr->vrtx -1]==0)
            {
                visited[ptr->vrtx -1] = 1;
                d[ptr->vrtx -1] = d[u-1] +1;
                parent[ptr->vrtx -1] = u;
                Queue[++rear] = (ptr->vrtx);
            }
            /*
            printf("\n\n");
            for(i=0;i<graph->V;i++)
                printf("parent[%d] = %d\nvisited[%d] = %d\nd[%d] = %d\n",i+1,parent[i],i+1,visited[i],i+1,d[i]);
            */
            ptr = ptr->next;
        }
    }

    printf("\n");
    for(i=0;i<graph->V;i++)
        printf("parent[%d] = %d\n",i+1,parent[i]);
    return d;
}
