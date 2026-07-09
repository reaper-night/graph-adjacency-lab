#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    double x;
    double y;
} Vertex2D;

typedef struct {
    double x;
    double y;
    double z;
} Vertex3D;

typedef struct {
    double value;
} Matrix0;

typedef struct {
    int** data;
    int size;
} AdjacencyMatrix;

typedef struct {
    char id[20];
    char name[50];
    char desc[100];
} ScenicSpot;

typedef struct AdjNode {
    char spot_id[20];
    int distance;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    ScenicSpot* spots;
    AdjNode** adj_list;
    int size;
    int capacity;
} Graph;

Vertex2D vertex2d_create(double x, double y);
Vertex3D vertex3d_create(double x, double y, double z);
Matrix0 matrix0_create(double value);
double matrix0_get(const Matrix0* m);
void matrix0_set(Matrix0* m, double value);

AdjacencyMatrix* adj_matrix_create(int size);
void adj_matrix_destroy(AdjacencyMatrix* mat);
void adj_matrix_set(AdjacencyMatrix* mat, int i, int j, int value);
int adj_matrix_get(AdjacencyMatrix* mat, int i, int j);
void adj_matrix_print(const AdjacencyMatrix* mat);

Graph* graph_create(int capacity);
void graph_destroy(Graph* graph);
int graph_add_spot(Graph* graph, const char* id, const char* name, const char* desc);
int graph_add_path(Graph* graph, const char* from_id, const char* to_id, int distance);
void graph_display(Graph* graph);
void graph_display_spots(Graph* graph);

#endif