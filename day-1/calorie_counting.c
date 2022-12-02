#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

char INPUT_FILE[] = "input";
int BIGGEST_NUM = 3;


void get_row(FILE* file, char row[]) {
    int count = 0;
    
    while (count < 16) {
        char chr = fgetc(file);
        
        if (chr == '\n') {
            break;
        }

        row[count] = chr;
        count++;
    }
}

void add_biggest(int sum, int biggest[]) {
    // Move the elements further down the array
    int r_index = -1;

    for (int i = 0; i < BIGGEST_NUM; i++) {
        if (sum > biggest[i] && (r_index == -1 || biggest[i] < biggest[r_index])) {
            r_index = i;
        }
    }

    if (r_index != -1) {
        biggest[r_index] = sum;
    }
}

int sum_biggest(int biggest[]) {
    int sum = 0;

    for (int i = 0; i < BIGGEST_NUM; i++) {
        sum += biggest[i];
    }

    return sum;
}

int main() {
    FILE* file;
    char row[16];
    int sum;
    int biggest[BIGGEST_NUM];

    // Make sure the biggest array is empty
    memset(biggest, 0, sizeof(biggest));

    file = fopen(INPUT_FILE, "r");

    if (file == NULL) {
        return -1;
    } 

    while(1) {
        get_row(file, row);

        // Save the sum if the end of a sequence is reached
        if (row[0] == '\0') {
            add_biggest(sum, biggest);
            sum = 0;
        }

        // Stop the calculation on End of File
        if (row[0] == EOF) {
            break;
        }
        
        sum += atoi(row); 

        // Empty the string
        memset(row, 0, sizeof(row));
    }

    printf("Part 1:\n");
    printf("    Greatest amount of calories: %d\n", biggest[0]);
    printf("Part 2:\n");
    printf("    Sum of the 3 greatest: %d\n", sum_biggest(biggest));
}


