#include<stdio.h>
#include<stdlib.h>
#include "heap1.h"

int main(){
    int n;
    graph G;
    double*dist;
    
    G = graph_input();
    n = G->n;
    NEW(dist,n);
    dijkstra(G,1,dist);

    for (int i = 1; i < n+1; i++)
    {
        printf("%d %lf\n", i, dist[i-1]);
    }
    free(dist);
    graph_free(G);
        
}