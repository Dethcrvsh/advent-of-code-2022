#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char FILE_NAME[] = "input";


int get_next_line(FILE* file, char* line, int size) {
    // Return 1 on success, 0 on EOF
    return fgets(line, size, file) != NULL;
}

void split_string(char* str, char* part1, char* part2) {
    // Splits a string into two equal parts
    int split = strlen(str) / 2;
    
    strncpy(part1, str, split);
    strncpy(part2, str + split, split);
}

void get_common_chars(char* part1, char* part2, char* common) {
    // Would prefer a better solution than O(N^2) but 
    // I have the brain of an egg sandwich
    int length = 0;
    
    // A cool way to loop over strings
    for (int index1 = 0; part1[index1]; index1++) {
        for (int index2 = 0; part2[index2]; index2++) {
            char c1 = part1[index1];
            char c2 = part2[index2];

            // strpbrk returns a pointer to the first 
            // common char between the strings
            if (c1 == c2 && !strpbrk(&c1, common)) {
                common[length] = c1;
                length++;
            }
        }
    }
}

int get_char_score(char* common) {
    // Get the total score from common characters
    int score = 0;

    for (int i = 0; common[i]; i++) {
        char c = common[i];
        //printf("c\n", c);
        
        // Uppercase
        if (65 <= c && c <= 90) {
            score += c - 65 + 27;
        } else if (97 <= c && c <= 122) {
            score += c - 97 + 1;
        }
    }

    return score;
}

void get_common(char** strings, int size, char* common) {
    // Get the common characters from a char array
    char accum[64];
    strcpy(accum, strings[0]);

    for (int i = 1; i < size; i++) {
        memset(common, 0, 64);
        get_common_chars(strings[i], accum, common);
        strcpy(accum, common);
    }
}

int main() {
    char common[16];

    FILE* file = fopen(FILE_NAME, "r");
    int status;
    int score = 0;
    int group_score = 0;
    int i = 0;
    char* group[3];

    do {
        char line[64];
        char part1[32];
        char part2[32];
        char common[32];

        // Make sure the strings are empty
        memset(line, 0, 64);
        memset(part1, 0, 32);
        memset(part2, 0, 32);
        memset(common, 0, 32);

        status = get_next_line(file, line, sizeof(line));

        // Add the line to the group
        char* line_group = (char*) malloc(sizeof(line));
        strcpy(line_group, line);
        group[i % 3] = line_group;

        split_string(line, part1, part2);
        get_common_chars(part1, part2, common);
        score += get_char_score(common);

        // Calculate the group score every third line
        if ((i+1) % 3 == 0) {
            get_common(group, sizeof(group) / sizeof(char*), common);
            group_score += get_char_score(common);
        }

        i++;
    } while(status);

    printf("Part 1:\n");
    printf("    Total score: %d\n\n", score);
    printf("Part 2:\n");
    printf("    Group score: %d\n", group_score);

    return 0;
}
