#include <stdio.h>
#include <windows.h>
#include "matrix.h"

void interactive_graph(void);

int main(int argc, char *argv[]) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    interactive_graph();
    
    return 0;
}

void interactive_graph(void) {
    Graph* graph = NULL;
    int choice, distance;
    char id[20], from_id[20], to_id[20], name[50];
    
    printf("\n\n===== 景区路径规划系统 =====\n");
    
    graph = graph_create(20);
    
    graph_add_spot(graph, "A", "大门");
    graph_add_spot(graph, "B", "碧玉潭");
    graph_add_spot(graph, "C", "红叶林");
    graph_add_spot(graph, "D", "赏花园");
    graph_add_spot(graph, "E", "飞云石");
    graph_add_spot(graph, "F", "九曲桥");
    graph_add_spot(graph, "G", "白虎岩");
    graph_add_spot(graph, "H", "观月阁");
    
    printf("已初始化默认景点: 大门、碧玉潭、红叶林、赏花园、飞云石、九曲桥、白虎岩、观月阁\n");
    
    while (1) {
        printf("\n请选择操作:\n");
        printf("1. 重置图\n");
        printf("2. 添加景点\n");
        printf("3. 添加路径\n");
        printf("4. 显示景区图（邻接表）\n");
        printf("5. 显示景点链表\n");
        printf("6. 显示景区景点分布图（邻接矩阵）\n");
        printf("7. 生成导游线路图（DFS遍历）\n");
        printf("8. 检测回路\n");
        printf("9. 查询最短路径（Dijkstra）\n");
        printf("10. 退出\n");
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
                graph = graph_create(20);
                
                graph_add_spot(graph, "A", "大门");
                graph_add_spot(graph, "B", "碧玉潭");
                graph_add_spot(graph, "C", "红叶林");
                graph_add_spot(graph, "D", "赏花园");
                graph_add_spot(graph, "E", "飞云石");
                graph_add_spot(graph, "F", "九曲桥");
                graph_add_spot(graph, "G", "白虎岩");
                graph_add_spot(graph, "H", "观月阁");
                
                printf("图已重置！已初始化默认景点: 大门、碧玉潭、红叶林、赏花园、飞云石、九曲桥、白虎岩、观月阁\n");
                break;
                
            case 2:
                printf("请输入景点ID: ");
                scanf("%s", id);
                printf("请输入景点名称: ");
                scanf("%s", name);
                int ret = graph_add_spot(graph, id, name);
                if (ret == 0) {
                    printf("景点添加成功！\n");
                } else if (ret == -1) {
                    printf("错误：图已满！\n");
                } else if (ret == -2) {
                    printf("错误：景点ID已存在！\n");
                }
                break;
                
            case 3:
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
                graph_display(graph);
                break;
                
            case 5:
                graph_display_spots(graph);
                break;
                
            case 6:
                graph_display_adjacency_matrix(graph);
                break;
                
            case 7:
                printf("请输入起点景点ID: ");
                scanf("%s", id);
                graph_dfs_tour(graph, id);
                break;
                
            case 8:
                graph_detect_cycle(graph);
                break;
                
            case 9:
                printf("请输入起点景点ID: ");
                scanf("%s", from_id);
                printf("请输入终点景点ID: ");
                scanf("%s", to_id);
                graph_shortest_path(graph, from_id, to_id);
                break;
                
            case 10:
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