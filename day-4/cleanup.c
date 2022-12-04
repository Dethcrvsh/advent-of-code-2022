#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char FILE_NAME[] = "input";

int get_next_line(FILE* file, char* line, int size) {
    // Return 1 on success, 0 on EOF
    return fgets(line, size, file) != NULL;
}

void cut_string(char* str, char divider, char* a, char* b) {
    // Cut a string into two substrings at the first occurance
    // of the divider character (removing the divider)

    // Find the dividing character and split the string
    char* div = strchr(str, divider);

    if (div != NULL) {
        *div = '\0';
        strcpy(a, str);
        strcpy(b, div + 1);
        *div = divider;
    }
}

void get_boundaries(char* line, int* a_low, int* a_high, int* b_low, int* b_high) {
    char a[strlen(line)];
    char b[strlen(line)];
    char part1[strlen(line)];
    char part2[strlen(line)];

    cut_string(line, ',', a, b);
    
    cut_string(a, '-', part1, part2);
    *a_low = atoi(part1);
    *a_high = atoi(part2);
    
    cut_string(b, '-', part1, part2);
    *b_low = atoi(part1);
    *b_high = atoi(part2);
}

int is_overlapping(char* line) {
    int a_low;
    int a_high;
    int b_low;
    int b_high;
    
    get_boundaries(line, &a_low, &a_high, &b_low, &b_high);
    
    return !(a_high < b_low || b_high < a_low);
}

int is_overlapping_strict(char* line) {
    int a_low;
    int a_high;
    int b_low;
    int b_high;
    
    get_boundaries(line, &a_low, &a_high, &b_low, &b_high);

    return (a_low <= b_low && b_high <= a_high) ||
           (b_low <= a_low && a_high <= b_high);
}

int get_overlaps(int overlap_check (char*)) {
    FILE* file = fopen(FILE_NAME, "r");
    int overlaps = 0;

    while (1) {
        char line[16];

        int status = get_next_line(file, line, sizeof(line));

        if (!status) {
            break;
        }

        if ((*overlap_check)(line)) {
            overlaps++;
        }
    }
   return overlaps;
}

int main() {
    int (*overlap_check) (char*); 

    overlap_check = &is_overlapping_strict;

    printf("Part 1:\n");
    printf("    Overlapping pairs: %d\n", get_overlaps(overlap_check));

    overlap_check = &is_overlapping;

    printf("Part 2:");
    printf("    Overlapping pairs: %d\n", get_overlaps(overlap_check));
    
    return 0;
}

