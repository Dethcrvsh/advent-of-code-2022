#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cargoInfo {
    int num, from, to;
};

char FILE_NAME[] = "input";


int get_next_line(FILE* file, char* line, int size) {
    // Return 1 on success, 0 on EOF
    return fgets(line, size, file) != NULL;
}

void print_stacks(char* stacks[], int size) {
    for (int i = 0; i < size; i++) {
        char* stack = stacks[i];
        printf("Stack %d: ", i + 1);

        for (int j = 0; stack[j]; j++) {
            printf("%c ", stack[j]);
        }
        printf("\n");
    } 
}

void reverse_stacks(char* stacks[], int size) {
    for (int i = 0; i < size; i++) {
        char* stack = stacks[i];
        int end = strlen(stack) - 1;

        for (int j = 0; j <= end/2; j++) {
            char front = stack[j]; 
            char back = stack[end - j];

            stack[j] = back;
            stack[end - j] = front;
        }
    }
}

void append_to_stack(char* stacks[], int stack_index, char elem) {
    char* stack = stacks[stack_index];
    stack[strlen(stack)] = elem;
}

char get_stack_top(char* stacks[], int stack_index) {
    char* stack = stacks[stack_index];
    return stack[strlen(stack) - 1];
}

char pop_stack_top(char* stacks[], int stack_index) {
    char* stack = stacks[stack_index];
    int length = strlen(stack);
    char elem = stack[length - 1];
    stack[length - 1] = '\0';
    return elem;
} 

void add_row_to_stacks(char* line, char* stacks[]) {
    int stack_size = 64;
    // The amount of space between characters
    int char_space = 4;
    int i = 0;
    // The index of the current char
    int char_i = i*char_space + 1;

    // Break if the end of the row is reached
    while(line[char_i + 2] != '\0') {

        if ('A' <= line[char_i] && line[char_i] <= 'Z') {
            append_to_stack(stacks, i, line[char_i]);
        }
        i++;
        char_i = i*char_space + 1;
    }
}

void init_stacks(FILE* file, char* stacks[], int size) {
    for (int i = 0; i < size; i++) {
        stacks[i] = (char*) malloc(sizeof(char*) * 64);
    }

    while(1) {
        char line[64];
        get_next_line(file, line, sizeof(line));

        if (line[1] == '1') {
            break;
        }

        add_row_to_stacks(line, stacks);
    }
    reverse_stacks(stacks, size);
}

struct cargoInfo get_cargo_info(char* line) {
    struct cargoInfo info;
    char* ptr = line;
    
    ptr = strchr(ptr, ' ') + 1;
    info.num = atoi(ptr);

    ptr = strchr(ptr, ' ') + 1;
    ptr = strchr(ptr, ' ') + 1;
    info.from = atoi(ptr) - 1;

    ptr = strchr(ptr, ' ') + 1;
    ptr = strchr(ptr, ' ') + 1;
    info.to = atoi(ptr) - 1;

    return info;
}

void move_cargo_9000(char* stacks[], struct cargoInfo info) {
    for (int i = 0; i < info.num; i++) {
        char crate = pop_stack_top(stacks, info.from);
        append_to_stack(stacks, info.to, crate);
    }
}

void move_cargo_9001(char* stacks[], struct cargoInfo info) {
    char* stack = stacks[info.from];
    int length = strlen(stack);

    for (int i = length - info.num; i < length; i++) {
        append_to_stack(stacks, info.to, stack[i]);
    }

    for (int i = 0; i < info.num; i++) {
        pop_stack_top(stacks, info.from);
    }
}

void parse_procedure(FILE* file, char* stacks[], int size, void (*movement_procedure) (char**, struct cargoInfo)) {
    while(1) {
        char line[64];
        int status = get_next_line(file, line, sizeof(line));

        if (!status) {
            break;
        }

        // Make sure the line has the right format
        if (line[0] == 'm') {
            struct cargoInfo info = get_cargo_info(line);
            (*movement_procedure)(stacks, info);
        }
    }
}

void get_secret_msg(char* stacks[], int stacks_size, char message[]) {
    for (int i = 0; i < stacks_size; i++) {
        char crate = get_stack_top(stacks, i);
        message[i] = crate;
    }
}

void part1() {
    FILE* file = fopen(FILE_NAME, "r");
    char* stacks[9];
    int stacks_size = sizeof(stacks) / sizeof(char*);

    void (*movement_procedure) (char**, struct cargoInfo);

    init_stacks(file, stacks, stacks_size);

    movement_procedure = &move_cargo_9000;
    parse_procedure(file, stacks, stacks_size, movement_procedure);

    char message[9];
    get_secret_msg(stacks, stacks_size, message);

    printf("Part 1:\n");
    printf("    Message: %s\n", message);

}

void part2() {
    FILE* file = fopen(FILE_NAME, "r");
    char* stacks[9];
    int stacks_size = sizeof(stacks) / sizeof(char*);

    void (*movement_procedure) (char**, struct cargoInfo);

    init_stacks(file, stacks, stacks_size);

    movement_procedure = &move_cargo_9001;
    parse_procedure(file, stacks, stacks_size, movement_procedure);

    char message[9];
    get_secret_msg(stacks, stacks_size, message);

    printf("Part 2:\n");
    printf("    Message: %s\n", message);
}

int main() {
    part1();
    part2();
    
    return 0;
}
