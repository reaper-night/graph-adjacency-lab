#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include "logger.h"
#include "utils.h"
#include "sort.h"
#include "matrix.h"

void test_sort_algorithms(void);
void test_matrix(void);
void test_scenic_graph(void);
void interactive_graph(void);

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "");
    logger_init();
    
    LOG_INFO("C Project Template - Starting application");
    LOG_INFO("Arguments: %d", argc);
    
    int result = utils_add(10, 20);
    LOG_INFO("utils_add(10, 20) = %d", result);
    
    test_sort_algorithms();
    test_matrix();
    test_scenic_graph();
    
    interactive_graph();
    
    LOG_INFO("Application finished successfully");
    
    logger_cleanup();
    return 0;
}

void test_sort_algorithms(void) {
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int arr3[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    
    LOG_INFO("Testing sorting algorithms...");
    LOG_INFO("Original array:");
    print_array(arr1, n);
    
    LOG_INFO("Selection Sort:");
    selection_sort(arr1, n);
    print_array(arr1, n);
    
    LOG_INFO("Insertion Sort:");
    insertion_sort(arr2, n);
    print_array(arr2, n);
    
    LOG_INFO("Bubble Sort:");
    bubble_sort(arr3, n);
    print_array(arr3, n);
}

void test_matrix(void) {
    LOG_INFO("Testing adjacency matrix...");
    
    AdjacencyMatrix* mat = adj_matrix_create(4);
    
    adj_matrix_set(mat, 0, 1, 1);
    adj_matrix_set(mat, 1, 0, 1);
    adj_matrix_set(mat, 1, 2, 1);
    adj_matrix_set(mat, 2, 1, 1);
    adj_matrix_set(mat, 2, 3, 1);
    adj_matrix_set(mat, 3, 2, 1);
    adj_matrix_set(mat, 3, 0, 1);
    adj_matrix_set(mat, 0, 3, 1);
    
    adj_matrix_print(mat);
    adj_matrix_destroy(mat);
}

void test_scenic_graph(void) {
    LOG_INFO("Testing scenic spot graph...");
    
    Graph* graph = graph_create(10);
    
    graph_add_spot(graph, "1", "西湖", "杭州著名景点");
    graph_add_spot(graph, "2", "灵隐寺", "千年古刹");
    graph_add_spot(graph, "3", "雷峰塔", "传奇故事");
    graph_add_spot(graph, "4", "断桥", "浪漫传说");
    
    graph_add_path(graph, "1", "2", 5);
    graph_add_path(graph, "1", "3", 3);
    graph_add_path(graph, "2", "4", 4);
    graph_add_path(graph, "3", "4", 2);
    
    graph_display_spots(graph);
    graph_display(graph);
    
    graph_destroy(graph);
}

void interactive_graph(void) {
    Graph* graph = NULL;
    int choice, distance, capacity;
    char id[20], from_id[20], to_id[20], name[50], desc[100];
    
    printf("\n\n===== 景区路径规划系统 =====\n");
    
    while (1) {
        printf("\n请选择操作:\n");
        printf("1. 创建图\n");
        printf("2. 添加景点\n");
        printf("3. 添加路径\n");
        printf("4. 显示景区图\n");
        printf("5. 显示景点链表\n");
        printf("6. 退出\n");
        printf("请输入选择: ");
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                if (graph != NULL) {
                    graph_destroy(graph);
                }
                printf("请输入图的容量: ");
                if (scanf("%d", &capacity) != 1) {
                    printf("输入无效，请输入数字！\n");
                    while (getchar() != '\n');
                    continue;
                }
                graph = graph_create(capacity);
                printf("图创建成功！容量: %d\n", capacity);
                break;
                
            case 2:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                printf("请输入景点ID: ");
                scanf("%s", id);
                printf("请输入景点名称: ");
                scanf("%s", name);
                printf("请输入景点描述: ");
                scanf("%s", desc);
                int ret = graph_add_spot(graph, id, name, desc);
                if (ret == 0) {
                    printf("景点添加成功！\n");
                } else if (ret == -1) {
                    printf("错误：图已满！\n");
                } else if (ret == -2) {
                    printf("错误：景点ID已存在！\n");
                }
                break;
                
            case 3:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                printf("请输入起点景点ID: ");
                scanf("%s", from_id);
                printf("请输入终点景点ID: ");
                scanf("%s", to_id);
                printf("请输入路径距离(km): ");
                if (scanf("%d", &distance) != 1) {
                    printf("输入无效，请输入数字！\n");
                    while (getchar() != '\n');
                    continue;
                }
                ret = graph_add_path(graph, from_id, to_id, distance);
                if (ret == 0) {
                    printf("路径添加成功！\n");
                } else {
                    printf("错误：景点ID不存在！\n");
                }
                break;
                
            case 4:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                graph_display(graph);
                break;
                
            case 5:
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                graph_display_spots(graph);
                break;
                
            case 6:
                if (graph != NULL) {
                    graph_destroy(graph);
                }
                printf("退出系统！\n");
                return;
                
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
}