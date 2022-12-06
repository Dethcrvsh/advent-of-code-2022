#include <stdio.h>
#include <stdbool.h>
#include <string.h>


char FILE_NAME[] = "input";


void add_to_buffer(char buffer[], unsigned int buffer_size, char letter) {
    // Adds the letter to the front of the buffer
    // Pushes out the last character if the buffer is full
    for (int i = buffer_size - 1; i > 0; i--) {
        buffer[i] = buffer[i-1];
    }
    buffer[0] = letter;
}

bool is_buffer_unique(char buffer[]) {
    for (int i = 0; buffer[i]; i++) {
        if (strchr(&buffer[i] + 1, buffer[i])) {
            return false;
        }
    }
    return true;
}

int get_first_marker(unsigned int buffer_size) {
    FILE* file = fopen(FILE_NAME, "r");
    char buffer[buffer_size];
    buffer[0] = '\0';
    char line[4096];

    fgets(line, sizeof(line), file);

    for (int i = 0; line[i]; i++) {
        add_to_buffer(buffer, buffer_size, line[i]);

        if (i >= buffer_size - 1 && is_buffer_unique(buffer)) {
            return i + 1;
        }
    }

    return -1;
}

int main() {
    printf("Part 1:\n");
    printf("    First marker: %d\n", get_first_marker(4));
    printf("Part 2:\n");
    printf("    First marker: %d\n", get_first_marker(14));
    
    return 0;
}
