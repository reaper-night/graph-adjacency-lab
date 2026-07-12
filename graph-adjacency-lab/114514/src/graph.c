#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_spot_index(Graph* graph, const char* id) {
    for (int i = 0; i < graph->size; i++) {
        if (strcmp(graph->spots[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

Graph* graph_create(int capacity) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = 0;
    graph->capacity = capacity;
    graph->spots = (ScenicSpot*)malloc(capacity * sizeof(ScenicSpot));
    graph->adj_matrix = (int**)malloc(capacity * sizeof(int*));
    for (int i = 0; i < capacity; i++) {
        graph->adj_matrix[i] = (int*)malloc(capacity * sizeof(int));
        for (int j = 0; j < capacity; j++) {
            if (i == j) {
                graph->adj_matrix[i][j] = 0;
            } else {
                graph->adj_matrix[i][j] = INF;
            }
        }
    }
    return graph;
}

void graph_destroy(Graph* graph) {
    for (int i = 0; i < graph->capacity; i++) {
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph->spots);
    free(graph);
}

int graph_add_spot(Graph* graph, const char* id, const char* name, const char* desc) {
    if (graph->size >= graph->capacity) {
        return -1;
    }
    if (find_spot_index(graph, id) != -1) {
        return -2;
    }
    strncpy(graph->spots[graph->size].id, id, MAX_SPOT_ID - 1);
    strncpy(graph->spots[graph->size].name, name, MAX_SPOT_NAME - 1);
    strncpy(graph->spots[graph->size].desc, desc, MAX_SPOT_DESC - 1);
    graph->size++;
    return 0;
}

int graph_add_path(Graph* graph, const char* from_id, const char* to_id, int distance) {
    int from_idx = find_spot_index(graph, from_id);
    int to_idx = find_spot_index(graph, to_id);
    if (from_idx == -1 || to_idx == -1) {
        return -1;
    }
    graph->adj_matrix[from_idx][to_idx] = distance;
    graph->adj_matrix[to_idx][from_idx] = distance;
    return 0;
}

void graph_display_spots(Graph* graph) {
    printf("景点链表:\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < graph->size; i++) {
        printf("[%d] ID: %s\n", i + 1, graph->spots[i].id);
        printf("    名称: %s\n", graph->spots[i].name);
        printf("    描述: %s\n", graph->spots[i].desc);
    }
    printf("----------------------------------------\n");
}

void graph_display(Graph* graph) {
    printf("\n景区图（邻接矩阵）:\n");
    printf("          ");
    for (int i = 0; i < graph->size; i++) {
        printf("%-8s", graph->spots[i].id);
    }
    printf("\n");
    printf("          ");
    for (int i = 0; i < graph->size; i++) {
        printf("--------");
    }
    printf("\n");
    for (int i = 0; i < graph->size; i++) {
        printf("%-8s | ", graph->spots[i].id);
        for (int j = 0; j < graph->size; j++) {
            if (graph->adj_matrix[i][j] == INF) {
                printf("%-8s", "-");
            } else {
                printf("%-8d", graph->adj_matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n图例：数字表示两景点间距离(km)，\"-\"表示无直接路径\n");
}