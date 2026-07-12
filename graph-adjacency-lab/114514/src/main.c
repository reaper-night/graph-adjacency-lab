#include <stdio.h>
#include <windows.h>
#include "graph.h"

void test_scenic_graph(void);
void interactive_graph(void);

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    printf("===== 景区路径规划系统（邻接矩阵实现）=====\n\n");
    
    test_scenic_graph();
    
    interactive_graph();
    
    return 0;
}

void test_scenic_graph(void) {
    printf("【功能测试】\n");
    
    Graph* graph = graph_create(10);
    
    printf("\n1. 创建图 - 容量: 10\n");
    
    printf("\n2. 添加景点:\n");
    graph_add_spot(graph, "S001", "西湖", "杭州著名景点");
    graph_add_spot(graph, "S002", "灵隐寺", "千年古刹");
    graph_add_spot(graph, "S003", "雷峰塔", "传奇故事");
    graph_add_spot(graph, "S004", "断桥", "浪漫传说");
    printf("   已添加4个景点\n");
    
    printf("\n3. 添加路径:\n");
    graph_add_path(graph, "S001", "S002", 5);
    graph_add_path(graph, "S001", "S003", 3);
    graph_add_path(graph, "S002", "S004", 4);
    graph_add_path(graph, "S003", "S004", 2);
    printf("   已添加4条路径\n");
    
    printf("\n4. 显示景点链表:\n");
    graph_display_spots(graph);
    
    printf("\n5. 显示景区图（邻接矩阵）:\n");
    graph_display(graph);
    
    graph_destroy(graph);
    
    printf("\n【测试完成】\n");
}

void interactive_graph(void) {
    Graph* graph = NULL;
    int choice, distance, capacity;
    char id[MAX_SPOT_ID], from_id[MAX_SPOT_ID], to_id[MAX_SPOT_ID];
    char name[MAX_SPOT_NAME], desc[MAX_SPOT_DESC];
    
    printf("\n\n===== 交互式操作 =====\n");
    
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
                if (scanf("%d", &capacity) != 1 || capacity <= 0) {
                    printf("输入无效，请输入正整数！\n");
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
                if (scanf("%d", &distance) != 1 || distance <= 0) {
                    printf("输入无效，请输入正整数！\n");
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