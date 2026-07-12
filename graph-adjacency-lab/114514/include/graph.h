#ifndef GRAPH_H
#define GRAPH_H

#define MAX_SPOT_ID 20
#define MAX_SPOT_NAME 50
#define MAX_SPOT_DESC 100
#define INF 99999

typedef struct {
    char id[MAX_SPOT_ID];
    char name[MAX_SPOT_NAME];
    char desc[MAX_SPOT_DESC];
} ScenicSpot;

typedef struct {
    ScenicSpot* spots;
    int** adj_matrix;
    int size;
    int capacity;
} Graph;

Graph* graph_create(int capacity);
void graph_destroy(Graph* graph);
int graph_add_spot(Graph* graph, const char* id, const char* name, const char* desc);
int graph_add_path(Graph* graph, const char* from_id, const char* to_id, int distance);
void graph_display(Graph* graph);
void graph_display_spots(Graph* graph);

#endif