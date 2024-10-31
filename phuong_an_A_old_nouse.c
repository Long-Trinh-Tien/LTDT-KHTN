#include <stdio.h>
// #define NUM_OF_ROOMS 9
#define NUM_OF_ROOMS 4
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

int main() {

    int adj_list[NUM_OF_ROOMS][NUM_OF_ROOMS] = {
    //  {D, A, B, C}
        {0, 1, 2, 2},  // D kết nối với A, B 2 lần, C 2 lần
        {1, 0, 1, 1},  // A kết nối với D, B, C
        {2, 1, 0, 1},  // B kết nối với D 2 lần, A, C
        {2, 1, 1, 0}   // C kết nối với D 2 lần, A, B
    };

    // int adj_list[NUM_OF_ROOMS][NUM_OF_ROOMS] = {
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
    int result = check_euler_circuit(adj_list, NUM_OF_ROOMS);
    if(result == 0) {
        result = check_euler_path_from_garden(adj_list, NUM_OF_ROOMS); 
    }
    printf("Result for 3) :%d\n", result);
    if(result != 0) {
        printf("Result for 4): ");
        traverse_rooms(adj_list);
    } else {
        printf("No Euler path/cycle\n");
    }
    return 0;
}
