#include<stdio.h>
#include<stdlib.h>
#include "heap1.h"



#define left(i)(2*(i)+1)
#define right(i)(2*(i)+2)
#define parent(i)(((i)-1)/2)


int minind(int a, int b, heapdata*A){
    double u,v;
    u = A[b]->priority;
    v = A[a]->priority;

    if (u < v){
        return b;
    }else{
    return a;
    }
}

int heap_swap(heap H, int i, int largest){
    heapdata*A;
    A = H->A;
    heapdata temp;
    temp = A[i];
    A[i] = A[largest];
    A[largest] = temp;
    H->A = A;
    // 正常終了を示すため0を返す
    return 0;
}

void heapify(heap H, int i){
    int l, r, largest, size;
    heapdata*A;
    A = H->A;
    size = H->size;
    l = left(i);
    r = right(i);
    largest = i;
    if (size>r){
        largest = minind(largest, r, A);
        largest = minind(largest, l, A);
    }else if (size==l+1)
    {
        largest = minind(largest, l, A);
    }

    if (largest!=i){
        heap_swap(H, i, largest);
        heapify(H,largest);
    }
}

heap heap_build(int n, heapdata*A, int max_size){ 
    int i;
    heap H;
    NEW(H,1);
    H->max_size = max_size;
    H->size = n;
    H->A = A;
    
    for ( i = (n-1)/2; i >= 0; i--)
    {
        heapify(H,i);
        if (i == 0) break; 
    }
    return H;
}

heapdata extract_min(heap H){
    int k;
    heapdata B;
    k = H->size-1;
    B = H->A[0];
    heap_swap(H,0,k);
    H->size = k;
    heapify(H,0);
    return B;
}

// int heap_sort(int n, heapdata*A){
//     int i;
//     heap H; 
//     H = heap_build(n,A,n+1);
//     for ( i = 1; i < n ; i++)
//     {
//         extract_min(H);
//     }
//     return 0;
// }

void heap_insert(heap H, heapdata x){
    int i,n,p;
    heapdata*A;
    n = H->size;

    if (H->size >= H->max_size) {
        fprintf(stderr, "Heap overflow: cannot insert more than max_size elements\n");
        exit(1);
    }

    A = H->A;
    A[n] = x;
    H->size = n+1;
    i = n;

   
    while (i > 0) {
        p = parent(i);
        if (H->A[p]->priority > H->A[i]->priority) {
            heap_swap(H, i, p);
            i = p;
        } else {
            break;
        }
    }
}

slist slist_new(void)
{
    slist L;
    NEW(L,1);
    L->head=NULL;
    L->tail=NULL;
    return L;
}

slobj slobj_new(int x, double v)
{
    slobj p;
    NEW(p,1);
    p->v=x;
    p->d=v;
    p->next=NULL;
    return p;
}
heapdata heapdata_new(int i, double j){
    heapdata p;
    NEW(p,1);
    p->priority = j;
    p->value = i;
    return p;
}

void slist_insert_tail(slist L,slobj p)
{
    if (L->head == NULL)
    {
        L->head = p;
        L->tail=p;
    }else{
    L->tail->next=p;
    L->tail=p;
    }
}


graph graph_new(int n, int m){
    graph G;
    NEW(G,1);
    G->n = n;
    G->m = m;

    NEW(G->E,n);
    for (int i = 0; i < n; i++)
    {
        G->E[i] = slist_new();
    }
    return G;
}

graph graph_input(void){
    int n, m, v;
    double d;
    slobj p;
    graph G;

    scanf("%d %d",&n,&m);

    G = graph_new(n,m);

    for (int i = 0; i < n; i++)
    {
        while(1){
            scanf("%d",&v);
            if (v<0)
            {
                break;
            }else{
                scanf("%lf",&d);
                p = slobj_new(v,d);
                slist_insert_tail(G->E[i],p);
            }
            
        }
    }
    return G;
}


void slist_free(slist L){
    slobj p,q;
    p=L->head;
    while(p!=NULL)
    {
    q=p;
    p=p->next;
    free(q);
    }
    free(L);
}


void graph_free(graph G)
{
    int i;
    int n = G->n;
    for(i=0;i<n;i++){
        slist_free(G->E[i]);
    }
    free(G->E);
    free(G);
}

void dijkstra(graph G, int s, double*dist){
    int n,m,v,x;
    double y,w;
    heap H;
    heapdata*A;
    heapdata p,q;
    slobj r;

    n= G->n;

    m = G->m;


    NEW(A,m);
    // for (int i = 0; i < m+1; i++)
    // {
    //     A[i] = NULL;
    // }
    

    for (int i = 0; i < n; i++)
    {
        dist[i] = 999999;
    }
    dist[s-1] = 0;
    H = heap_build(0,A,m);
    p = heapdata_new(s,0);
    heap_insert(H,p);
    while (H->size > 0)
    {
        q = extract_min(H);
        v = q->value;
        y = q->priority;
        if (dist[v-1] >= y)
        {
            dist[v-1] = y;
            r = G->E[v-1]->head;
            while (r!=NULL)
            {
                x = r->v;
                w = r->d;
                if (dist[x - 1] > dist[v - 1] + w)
                {
                    dist[x - 1] = dist[v-1] + w;
                    p = heapdata_new(x,dist[x-1]);
                    heap_insert(H,p);
                }
                r = r->next;
            }
            
        }
        free(q);
        
    }

    // for (int i = 0; i < m+1; i++)
    // {
    //     if (A[i] != NULL)
    //     {
    //         free(A[i]);
    //     }
    // }
    
    free(A);
    free(H);
    
}