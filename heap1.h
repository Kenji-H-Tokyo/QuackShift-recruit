typedef struct 
{
    int value;
    double priority;
}*heapdata;


typedef struct 
{
    int max_size;
    int size;
    heapdata*A;
}*heap;

typedef struct slobj_ 
{  
    struct slobj_*next;
    int v;
    double d;
}*slobj;

typedef struct {
    slobj head;
    slobj tail;
}*slist;

typedef struct 
{
    int n ; //節点数
    int m ; // 枝数
    slist*E; //枝リストの配列 
}*graph;

typedef slobj edge;

# define NEW(p,n){p = malloc((n*sizeof(p[0])));if((p)==NULL){printf("not enough memory\n");exit(1);};}

void graph_free(graph G);
graph graph_input(void);
void dijkstra(graph G, int s, double*dist);