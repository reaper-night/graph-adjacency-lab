#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vertex2D vertex2d_create(double x, double y) {
    Vertex2D v;
    v.x = x;
    v.y = y;
    return v;
}

Vertex3D vertex3d_create(double x, double y, double z) {
    Vertex3D v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Matrix0 matrix0_create(double value) {
    Matrix0 m;
    m.value = value;
    return m;
}

double matrix0_get(const Matrix0* m) {
    return m->value;
}

void matrix0_set(Matrix0* m, double value) {
    m->value = value;
}

AdjacencyMatrix* adj_matrix_create(int size) {
    AdjacencyMatrix* mat = (AdjacencyMatrix*)malloc(sizeof(AdjacencyMatrix));
    mat->size = size;
    mat->data = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        mat->data[i] = (int*)calloc(size, sizeof(int));
    }
    return mat;
}

void adj_matrix_destroy(AdjacencyMatrix* mat) {
    for (int i = 0; i < mat->size; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void adj_matrix_set(AdjacencyMatrix* mat, int i, int j, int value) {
    if (i >= 0 && i < mat->size && j >= 0 && j < mat->size) {
        mat->data[i][j] = value;
    }
}

int adj_matrix_get(AdjacencyMatrix* mat, int i, int j) {
    if (i >= 0 && i < mat->size && j >= 0 && j < mat->size) {
        return mat->data[i][j];
    }
    return -1;
}

void adj_matrix_print(const AdjacencyMatrix* mat) {
    printf("Adjacency Matrix (%dx%d):\n", mat->size, mat->size);
    for (int i = 0; i < mat->size; i++) {
        for (int j = 0; j < mat->size; j++) {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
}

Graph* graph_create(int capacity) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->size = 0;
    graph->capacity = capacity;
    graph->spots = (ScenicSpot*)malloc(capacity * sizeof(ScenicSpot));
    graph->adj_list = (AdjNode**)malloc(capacity * sizeof(AdjNode*));
    for (int i = 0; i < capacity; i++) {
        graph->adj_list[i] = NULL;
    }
    return graph;
}

void graph_destroy(Graph* graph) {
    for (int i = 0; i < graph->size; i++) {
        AdjNode* curr = graph->adj_list[i];
        while (curr != NULL) {
            AdjNode* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->adj_list);
    free(graph->spots);
    free(graph);
}

static int find_spot_index(Graph* graph, const char* id) {
    for (int i = 0; i < graph->size; i++) {
        if (strcmp(graph->spots[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

int graph_add_spot(Graph* graph, const char* id, const char* name, const char* desc) {
    if (graph->size >= graph->capacity) {
        return -1;
    }
    if (find_spot_index(graph, id) != -1) {
        return -2;
    }
    strncpy(graph->spots[graph->size].id, id, sizeof(graph->spots[graph->size].id) - 1);
    strncpy(graph->spots[graph->size].name, name, sizeof(graph->spots[graph->size].name) - 1);
    strncpy(graph->spots[graph->size].desc, desc, sizeof(graph->spots[graph->size].desc) - 1);
    graph->size++;
    return 0;
}

int graph_add_path(Graph* graph, const char* from_id, const char* to_id, int distance) {
    int from_idx = find_spot_index(graph, from_id);
    int to_idx = find_spot_index(graph, to_id);
    if (from_idx == -1 || to_idx == -1) {
        return -1;
    }
    
    AdjNode* new_node = (AdjNode*)malloc(sizeof(AdjNode));
    strncpy(new_node->spot_id, to_id, sizeof(new_node->spot_id) - 1);
    new_node->distance = distance;
    new_node->next = graph->adj_list[from_idx];
    graph->adj_list[from_idx] = new_node;
    
    new_node = (AdjNode*)malloc(sizeof(AdjNode));
    strncpy(new_node->spot_id, from_id, sizeof(new_node->spot_id) - 1);
    new_node->distance = distance;
    new_node->next = graph->adj_list[to_idx];
    graph->adj_list[to_idx] = new_node;
    
    return 0;
}

void graph_display_spots(Graph* graph) {
    printf("景点链表:\n");
    for (int i = 0; i < graph->size; i++) {
        printf("[%s] %s - %s\n", graph->spots[i].id, graph->spots[i].name, graph->spots[i].desc);
    }
}

void graph_display(Graph* graph) {
    printf("\n景区图（邻接表）:\n");
    for (int i = 0; i < graph->size; i++) {
        printf("[%s] %s:\n", graph->spots[i].id, graph->spots[i].name);
        AdjNode* curr = graph->adj_list[i];
        while (curr != NULL) {
            int spot_idx = find_spot_index(graph, curr->spot_id);
            if (spot_idx != -1) {
                printf("    -> [%s]%s (距离: %dkm)\n", curr->spot_id, graph->spots[spot_idx].name, curr->distance);
            }
            curr = curr->next;
        }
    }
}