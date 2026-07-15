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

int graph_add_spot(Graph* graph, const char* id, const char* name) {
    if (graph->size >= graph->capacity) {
        return -1;
    }
    if (find_spot_index(graph, id) != -1) {
        return -2;
    }
    strncpy(graph->spots[graph->size].id, id, sizeof(graph->spots[graph->size].id) - 1);
    strncpy(graph->spots[graph->size].name, name, sizeof(graph->spots[graph->size].name) - 1);
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
        printf("[%s] %s\n", graph->spots[i].id, graph->spots[i].name);
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

#define INF 99999

void graph_display_adjacency_matrix(Graph* graph) {
    if (graph->size == 0) {
        printf("图中没有景点！\n");
        return;
    }
    
    int n = graph->size;
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = INF;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        AdjNode* curr = graph->adj_list[i];
        while (curr != NULL) {
            int j = find_spot_index(graph, curr->spot_id);
            if (j != -1) {
                matrix[i][j] = curr->distance;
            }
            curr = curr->next;
        }
    }
    
    printf("\n景区景点距离矩阵（邻接矩阵）:\n");
    printf("      ");
    for (int i = 0; i < n; i++) {
        printf("%-8s", graph->spots[i].name);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-6s", graph->spots[i].name);
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF) {
                printf("%-8s", "∞");
            } else {
                printf("%-8d", matrix[i][j]);
            }
        }
        printf("\n");
    }
    
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

static void dfs_helper(Graph* graph, int start_idx, int* visited, int* path, int* path_len, int* total_distance) {
    visited[start_idx] = 1;
    path[(*path_len)++] = start_idx;
    
    AdjNode* curr = graph->adj_list[start_idx];
    while (curr != NULL) {
        int next_idx = find_spot_index(graph, curr->spot_id);
        if (next_idx != -1 && !visited[next_idx]) {
            *total_distance += curr->distance;
            dfs_helper(graph, next_idx, visited, path, path_len, total_distance);
        }
        curr = curr->next;
    }
}

void graph_dfs_tour(Graph* graph, const char* start_id) {
    if (graph->size == 0) {
        printf("图中没有景点！\n");
        return;
    }
    
    int start_idx = find_spot_index(graph, start_id);
    if (start_idx == -1) {
        printf("错误：起点景点ID不存在！\n");
        return;
    }
    
    int* visited = (int*)calloc(graph->size, sizeof(int));
    int* path = (int*)malloc(graph->size * sizeof(int));
    int path_len = 0;
    int total_distance = 0;
    
    dfs_helper(graph, start_idx, visited, path, &path_len, &total_distance);
    
    printf("\n===== 导游线路图（DFS遍历）=====\n");
    printf("起点: %s (%s)\n", graph->spots[start_idx].id, graph->spots[start_idx].name);
    printf("线路: ");
    
    for (int i = 0; i < path_len; i++) {
        printf("%s", graph->spots[path[i]].name);
        if (i < path_len - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
    
    printf("路径详情:\n");
    int segment_distance = 0;
    for (int i = 0; i < path_len - 1; i++) {
        AdjNode* curr = graph->adj_list[path[i]];
        while (curr != NULL) {
            int next_idx = find_spot_index(graph, curr->spot_id);
            if (next_idx == path[i + 1]) {
                segment_distance += curr->distance;
                printf("  %d. %s -> %s (%dkm)\n", i + 1, 
                       graph->spots[path[i]].name, 
                       graph->spots[path[i + 1]].name, 
                       curr->distance);
                break;
            }
            curr = curr->next;
        }
    }
    
    printf("\n覆盖景点数: %d / %d\n", path_len, graph->size);
    printf("总路程: %dkm\n", segment_distance);
    
    if (path_len < graph->size) {
        printf("\n未访问的景点（不可达）:\n");
        for (int i = 0; i < graph->size; i++) {
            if (!visited[i]) {
                printf("  - %s (%s)\n", graph->spots[i].id, graph->spots[i].name);
            }
        }
    }
    
    free(visited);
    free(path);
}

static int cycle_dfs(Graph* graph, int start_idx, int* visited, int* rec_stack, int* parent, int* cycle_start, int* cycle_end) {
    visited[start_idx] = 1;
    rec_stack[start_idx] = 1;
    
    AdjNode* curr = graph->adj_list[start_idx];
    while (curr != NULL) {
        int next_idx = find_spot_index(graph, curr->spot_id);
        if (next_idx != -1) {
            if (!visited[next_idx]) {
                parent[next_idx] = start_idx;
                if (cycle_dfs(graph, next_idx, visited, rec_stack, parent, cycle_start, cycle_end)) {
                    return 1;
                }
            } else if (rec_stack[next_idx] && next_idx != parent[start_idx]) {
                *cycle_start = next_idx;
                *cycle_end = start_idx;
                return 1;
            }
        }
        curr = curr->next;
    }
    
    rec_stack[start_idx] = 0;
    return 0;
}

void graph_detect_cycle(Graph* graph) {
    if (graph->size == 0) {
        printf("图中没有景点！\n");
        return;
    }
    
    int* visited = (int*)calloc(graph->size, sizeof(int));
    int* rec_stack = (int*)calloc(graph->size, sizeof(int));
    int* parent = (int*)malloc(graph->size * sizeof(int));
    
    for (int i = 0; i < graph->size; i++) {
        parent[i] = -1;
    }
    
    int cycle_start = -1;
    int cycle_end = -1;
    
    for (int i = 0; i < graph->size; i++) {
        if (!visited[i]) {
            if (cycle_dfs(graph, i, visited, rec_stack, parent, &cycle_start, &cycle_end)) {
                break;
            }
        }
    }
    
    if (cycle_start != -1) {
        printf("\n===== 回路检测结果 =====\n");
        printf("检测到回路！\n");
        
        int* cycle_path = (int*)malloc(graph->size * sizeof(int));
        int cycle_len = 0;
        
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle_path[cycle_len++] = v;
        }
        cycle_path[cycle_len++] = cycle_start;
        
        printf("回路路径: ");
        for (int i = cycle_len - 1; i >= 0; i--) {
            printf("%s", graph->spots[cycle_path[i]].name);
            if (i > 0) {
                printf(" -> ");
            }
        }
        printf(" -> %s\n", graph->spots[cycle_start].name);
        
        printf("回路详情:\n");
        int total_distance = 0;
        for (int i = cycle_len - 1; i > 0; i--) {
            int from_idx = cycle_path[i];
            int to_idx = cycle_path[i - 1];
            AdjNode* curr = graph->adj_list[from_idx];
            while (curr != NULL) {
                int next_idx = find_spot_index(graph, curr->spot_id);
                if (next_idx == to_idx) {
                    total_distance += curr->distance;
                    printf("  %s -> %s (%dkm)\n", 
                           graph->spots[from_idx].name, 
                           graph->spots[to_idx].name, 
                           curr->distance);
                    break;
                }
                curr = curr->next;
            }
        }
        
        int from_idx = cycle_path[0];
        int to_idx = cycle_start;
        AdjNode* curr = graph->adj_list[from_idx];
        while (curr != NULL) {
            int next_idx = find_spot_index(graph, curr->spot_id);
            if (next_idx == to_idx) {
                total_distance += curr->distance;
                printf("  %s -> %s (%dkm)\n", 
                       graph->spots[from_idx].name, 
                       graph->spots[to_idx].name, 
                       curr->distance);
                break;
            }
            curr = curr->next;
        }
        
        printf("\n回路总路程: %dkm\n", total_distance);
        
        free(cycle_path);
    } else {
        printf("\n===== 回路检测结果 =====\n");
        printf("未检测到回路！\n");
        printf("导游线路图是无环图（树或森林）。\n");
    }
    
    free(visited);
    free(rec_stack);
    free(parent);
}

void graph_shortest_path(Graph* graph, const char* start_id, const char* end_id) {
    if (graph->size == 0) {
        printf("图中没有景点！\n");
        return;
    }
    
    int start_idx = find_spot_index(graph, start_id);
    int end_idx = find_spot_index(graph, end_id);
    
    if (start_idx == -1) {
        printf("错误：起点景点ID不存在！\n");
        return;
    }
    if (end_idx == -1) {
        printf("错误：终点景点ID不存在！\n");
        return;
    }
    
    if (start_idx == end_idx) {
        printf("\n===== 最短路径查询结果 =====\n");
        printf("起点与终点相同：%s (%s)\n", 
               graph->spots[start_idx].id, 
               graph->spots[start_idx].name);
        printf("最短距离: 0km\n");
        return;
    }
    
    int n = graph->size;
    int* dist = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));
    int* prev = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start_idx] = 0;
    
    for (int count = 0; count < n - 1; count++) {
        int min_dist = INF;
        int u = -1;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }
        
        if (u == -1) break;
        visited[u] = 1;
        
        AdjNode* curr = graph->adj_list[u];
        while (curr != NULL) {
            int v = find_spot_index(graph, curr->spot_id);
            if (v != -1 && !visited[v] && dist[u] != INF && dist[u] + curr->distance < dist[v]) {
                dist[v] = dist[u] + curr->distance;
                prev[v] = u;
            }
            curr = curr->next;
        }
    }
    
    if (dist[end_idx] == INF) {
        printf("\n===== 最短路径查询结果 =====\n");
        printf("无法从 %s (%s) 到达 %s (%s)！\n", 
               graph->spots[start_idx].id, graph->spots[start_idx].name,
               graph->spots[end_idx].id, graph->spots[end_idx].name);
    } else {
        printf("\n===== 最短路径查询结果 =====\n");
        printf("从 %s (%s) 到 %s (%s)\n", 
               graph->spots[start_idx].id, graph->spots[start_idx].name,
               graph->spots[end_idx].id, graph->spots[end_idx].name);
        
        int* path = (int*)malloc(n * sizeof(int));
        int path_len = 0;
        for (int v = end_idx; v != -1; v = prev[v]) {
            path[path_len++] = v;
        }
        
        printf("最短路径: ");
        for (int i = path_len - 1; i >= 0; i--) {
            printf("%s", graph->spots[path[i]].name);
            if (i > 0) {
                printf(" -> ");
            }
        }
        printf("\n");
        
        printf("路径详情:\n");
        for (int i = path_len - 1; i > 0; i--) {
            int from_idx = path[i];
            int to_idx = path[i - 1];
            AdjNode* curr = graph->adj_list[from_idx];
            while (curr != NULL) {
                int next_idx = find_spot_index(graph, curr->spot_id);
                if (next_idx == to_idx) {
                    printf("  %s -> %s (%dkm)\n", 
                           graph->spots[from_idx].name, 
                           graph->spots[to_idx].name, 
                           curr->distance);
                    break;
                }
                curr = curr->next;
            }
        }
        
        printf("\n最短距离: %dkm\n", dist[end_idx]);
        
        free(path);
    }
    
    free(dist);
    free(visited);
    free(prev);
}