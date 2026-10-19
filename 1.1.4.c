#include <stdio.h>
#include <stdlib.h>
#include <limits.h>




void kruskalMST(int **cost, int V) {


typedef struct {
        int u;
        int v;
        int w;
        int id;
    } Edge;

    int max_edges = V * (V - 1) / 2;
    Edge *edges = (Edge *)malloc(max_edges * sizeof(Edge));
    int edge_count = 0;

 
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (cost[i][j] != 9999) {
                edges[edge_count].u = i;
                edges[edge_count].v = j;
                edges[edge_count].w = cost[i][j];
                edges[edge_count].id = edge_count; 
                edge_count++;
            }
        }
    }


    for (int i = 1; i < edge_count; i++) {
        Edge key = edges[i];
        int j = i - 1;
        while (j >= 0 && (edges[j].w > key.w || (edges[j].w == key.w && edges[j].id > key.id))) {
            edges[j + 1] = edges[j];
            j--;
        }
        edges[j + 1] = key;
    }


    int *parent = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    int mst_edges = 0;
    int min_cost = 0;


    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].u;
        int v = edges[i].v;


        int root_u = u;
        while (parent[root_u] != root_u) {
            root_u = parent[root_u];
        }
        int curr = u;
        while (curr != root_u) {
            int nxt = parent[curr];
            parent[curr] = root_u;
            curr = nxt;
        }


        int root_v = v;
        while (parent[root_v] != root_v) {
            root_v = parent[root_v];
        }
        curr = v;
        while (curr != root_v) {
            int nxt = parent[curr];
            parent[curr] = root_v;
            curr = nxt;
        }


        if (root_u != root_v) {
            parent[root_u] = root_v; // Union sets
            printf("Edge %d:(%d, %d) cost:%d\n", mst_edges, edges[i].u, edges[i].v, edges[i].w);
            min_cost += edges[i].w;
            mst_edges++;
            

            if (mst_edges == V - 1) {
                break;
            }
        }
    }

    printf("Minimum cost= %d\n", min_cost);


    free(edges);
    free(parent);
}



int main() {
    int V;
    printf("No of vertices: ");
    scanf("%d", &V);

    int **cost = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++)
        cost[i] = (int *)malloc(V * sizeof(int));

    printf("Adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &cost[i][j]);

    kruskalMST(cost, V);

    for (int i = 0; i < V; i++)
        free(cost[i]);
    free(cost);

    return 0;
}
