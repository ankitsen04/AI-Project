#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int start, int goal);

int main() {
    int graph[MAX_NODES][MAX_NODES];
    int n, start, goal;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix (use %d for no connection):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }

    printf("Enter the starting node (0 to %d): ", n - 1);
    scanf("%d", &start);

    printf("Enter the goal node (0 to %d): ", n - 1);
    scanf("%d", &goal);

    dijkstra(graph, n, start, goal);

    return 0;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int start, int goal) {
    int dist[MAX_NODES], visited[MAX_NODES], parent[MAX_NODES];
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int minDist = INF, u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break; 
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[goal] == INF) {
        printf("No path exists from node %d to node %d.\n", start, goal);
    } else {
        printf("Shortest path from node %d to node %d is %d.\n", start, goal, dist[goal]);
        printf("Path: ");
        int path[MAX_NODES], pathIndex = 0, current = goal;
        while (current != -1) {
            path[pathIndex++] = current;
            current = parent[current];
        }
        for (int i = pathIndex - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}