#include <stdio.h>
#include <stdlib.h>

#define INF 2e9


typedef struct {
    int u, v, w;
} Edge;


void print_path(int current, int parent[], int src) {
    if (current == src) {
        printf("%d", src);
        return;
    }
    print_path(parent[current], parent, src);
    printf("->%d", current);
}

int main() {
    int V, E;
    if (scanf("%d", &V) != 1) return 0;
    if (scanf("%d", &E) != 1) return 0;


    Edge* edges = (Edge*)malloc(E * sizeof(Edge));
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    int src;
    if (scanf("%d", &src) != 1) {
        free(edges);
        return 0;
    }


    long long* dist = (long long*)malloc((V + 1) * sizeof(long long));
    int* parent = (int*)malloc((V + 1) * sizeof(int));

    for (int i = 1; i <= V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;


    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }


    int negative_cycle = 0;
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            negative_cycle = 1;
            break;
        }
    }

    if (negative_cycle) {
        printf("Negative cycle detected\n");
    } else {
		
        for (int i = 1; i <= V; i++) {
            if (i == src) {
                continue;
            }
            if (dist[i] == INF) {
                printf("%d INF None\n", i);
            } else {
                printf("%d %lld ", i, dist[i]);
                print_path(i, parent, src);
                printf("\n");
            }
        }
    }


    free(edges);
    free(dist);
    free(parent);

    return 0;
}

