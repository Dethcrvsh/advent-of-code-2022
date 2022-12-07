#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char FILE_NAME[] = "input";


struct FileSystem {
    struct Dir* root;
    struct Dir* stack[256];
};


struct Dir {
    struct Dir* dirs[256];
    struct File* files[256];
};


struct File {
    char name[64];
    unsigned int size;
};


bool is_command(char line[]) {
    return line[0] == '$';
}

bool is_dir(char line[]) {
    return strstr(line, "dir");
}

void run_command(struct FileSystem* file_system, char line[]) {
    char command[3];
    char argument[32];

    line[strlen(line) - 1] = '\0';

    // Separate the different parts of the command
    strncpy(command, &line[2], sizeof(command) - 1);
    strcpy(argument, &line[2 + 3]);
    
    printf("%s\n", argument);
    if (strcmp(command, "cd")) {
        printf("%s\n", argument);

        if (strcmp(argument, "/")) {
        } else if (strcmp(argument, "..")) {
            printf("up");
        }
    }
}

void add_dir() {

}

void add_file() {

}


void init_file_system(struct FileSystem* file_system) {
    FILE* file = fopen(FILE_NAME, "r");
    char line[32];

    // Initialize the file system
    file_system = (struct FileSystem*) malloc(sizeof(struct FileSystem));

    while (fgets(line, sizeof(line), file)) {
        if (is_command(line)) {
            run_command(file_system, line);
        } else if (is_dir(line)) {

        } else {

        }
    }
}


int main() {
    struct FileSystem* file_system;

    init_file_system(file_system);
    return 0;
}
