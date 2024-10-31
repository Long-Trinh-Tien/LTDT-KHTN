#include <stdio.h>
// #define NUM_OF_ROOMS 9
#define NUM_OF_ROOMS 4
#define MAX_VERTICES 25
int check_euler_circuit(int adj_list[][NUM_OF_ROOMS], int n) {
    for (int i = 0; i < n; i++) {
        int row_sum = 0;
        for (int j = 0; j < n; j++) {
            row_sum += adj_list[i][j];  
        }
        if (row_sum % 2 != 0) {
            return 0; 
        }
    }
    return 2;  
}


int check_euler_path_from_garden(int adj_list[][NUM_OF_ROOMS], int n) {
    int odd_count = 0;

 
    int first_row_sum = 0;
    for (int j = 0; j < n; j++) {
        first_row_sum += adj_list[0][j];
    }

 
    if (first_row_sum % 2 != 1) {
        return 0;  
    }


    for (int i = 1; i < n; i++) {  
        int row_sum = 0;
        for (int j = 0; j < n; j++) {
            row_sum += adj_list[i][j];
        }
        if (row_sum % 2 != 0) {
            odd_count++;
        }
    }

    
    return (odd_count == 1) ? 1 : 0;
}

void traverse_rooms(int adj_list[][NUM_OF_ROOMS]) {
    printf("%c -> ",'A' - 1 + NUM_OF_ROOMS);         

    
    int current_line = 0;

    while (1) {
        int found = 0;  

       
        for (int j = 0; j < NUM_OF_ROOMS; j++) {
            if (adj_list[current_line][j] > 0) {
                // Nếu tìm thấy kết nối
                if(j != 0){
                    printf("%c -> ", j + 'A' - 1); 
                } else {
                    printf("%c -> ", j + 'A' - 1 + NUM_OF_ROOMS);
                }
                adj_list[current_line][j]--;  
                adj_list[j][current_line]--;

                current_line = j;               
                found = 1;                     
                break;                          
            }
        }

        
        if (!found) {
            printf("end\n");
            break;
        }
    }
}

void convert_list_to_matrix(int adj[][NUM_OF_ROOMS], int adj_list[][MAX_VERTICES], int node) {
    // Khởi tạo ma trận kề với 0
    for (int i = 0; i < node; i++) {
        for (int j = 0; j < node; j++) {
            adj[i][j] = 0;
        }
    }

    // Chuyển đổi danh sách kề thành ma trận kề
    for (int i = 0; i < node; i++) {
        if( i == 0){
            for (int j = 0; adj_list[node - 1][j] != 0; j++) {
                int vertex = adj_list[node -1][j];
                adj[i][vertex - 1]++; // Tăng số lần kết nối
                if(adj_list[node -1][j+1] < 0){
                    break;
                }
            }
        } else {
            for (int j = 0; adj_list[i-1][j] != 0; j++) {
                int vertex = adj_list[i-1][j];
                adj[i][vertex - 1]++; // Tăng số lần kết nối
                if(adj_list[i-1][j+1] < 0){
                    break;
                }
            }
        }
    }
}
void read_graph_from_file(const char *filename, int *n, int adj_list[MAX_VERTICES][MAX_VERTICES]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Không thể mở tệp %s\n", filename);
        return;
    }

    // Đọc số lượng đỉnh
    fscanf(file, "%d", n);

    // Đọc danh sách kề
    for (int i = 0; i < *n; i++) {
        int m; // Số lượng đỉnh kề
        fscanf(file, "%d", &m); // Đọc số lượng đỉnh kề
        
        for (int j = 0; j < m; j++) {
           int temp;
            fscanf(file, "%d", &temp); // Đọc số vào tạm
            adj_list[i][j] = temp + 1; // Cộng 1 vào số và gán vào đỉnh kề
        }
        adj_list[i][m] = -1; // Đánh dấu kết thúc danh sách kề bằng -1
    }
    // for (int i = 0; i < *n; i++) {
    //     printf("Đỉnh %d kết nối với: ", i);
    //     for (int j = 0; adj_list[i][j] != -1; j++) {
    //         printf("%d ", adj_list[i][j]);
    //     }
    //     printf("\n");
    // }

    fclose(file);
}

int main() {
    int node; // Số lượng đỉnh
    int adj_list[MAX_VERTICES][MAX_VERTICES]; // Danh sách kề
    int adj_matrix[NUM_OF_ROOMS][NUM_OF_ROOMS]; // Ma trận kề
    read_graph_from_file("input.txt", &node, adj_list);
    // int adj_list[MAX_VERTICES][MAX_VERTICES] = {
    //     {2, 3, 3, 4, 4}, // Đỉnh 1 kết nối với 2, 3 (2 lần), 4 (2 lần)
    //     {1, 3, 4},       // Đỉnh 2 kết nối với 1, 3, 4
    //     {1, 1, 2, 4},    // Đỉnh 3 kết nối với 1 (2 lần), 2, 4
    //     {1, 1, 2, 3}     // Đỉnh 4 kết nối với 1, 2, 3
    // };
    convert_list_to_matrix(adj_matrix, adj_list, node);
    // int adj_matrix[NUM_OF_ROOMS][NUM_OF_ROOMS] = {
    // //  {D, A, B, C}
    //     {0, 1, 2, 2},  // D kết nối với A, B 2 lần, C 2 lần
    //     {1, 0, 1, 1},  // A kết nối với D, B, C
    //     {2, 1, 0, 1},  // B kết nối với D 2 lần, A, C
    //     {2, 1, 1, 0}   // C kết nối với D 2 lần, A, B
    // };

    // int adj_matrix[NUM_OF_ROOMS][NUM_OF_ROOMS] = {
    // //  {I, A, B, C, D, E, F, G, H}
    //     {0, 1, 0, 0, 0, 1, 0, 0, 0},  // I garden
    //     {1, 0, 0, 0, 0, 0, 0, 0, 1},  // A
    //     {0, 0, 0, 1, 0, 0, 0, 1, 0},  // B
    //     {0, 0, 1, 0, 1, 0, 0, 0, 0},  // C 
    //     {0, 0, 0, 1, 0, 0, 0, 1, 0},  // D 
    //     {1, 0, 0, 0, 0, 0, 1, 0, 0},  // E
    //     {0, 0, 0, 0, 0, 1, 0, 1, 0},  // F
    //     {0, 0, 1, 0, 1, 0, 1, 0, 1},  // G
    //     {0, 1, 0, 0, 0, 0, 0, 1, 0},  // H
    // };
    int result = check_euler_circuit(adj_matrix, NUM_OF_ROOMS);
    if(result == 0) {
        result = check_euler_path_from_garden(adj_matrix, NUM_OF_ROOMS); 
    }
    printf("Result for 3) :%d\n", result);
    if(result != 0) {
        printf("Result for 4): ");
        traverse_rooms(adj_matrix);
    } else {
        printf("No Euler path/cycle\n");
    }
    return 0;
}
