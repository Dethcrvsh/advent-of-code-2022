#include <stdio.h>
#include <string.h>


char FILE_NAME[] = "input";

int get_next_line(FILE* file, char* line, int size) {
    /* Return 1 on success, 0 on error or EOF */
    char* str = fgets(line, size, file);

    return str != NULL;
}

int get_point(char self, char opponent) {
    int win_point = 0;
    // Displace by the integer value of char 'X'
    int hand_point = (int) self - 88 + 1;

    // Draw (displace by the difference of char 'A' and 'X')
    if (self - 23 == opponent) {
        win_point = 3;
    // Win
    } else if (
            (self == 'X' && opponent == 'C') || 
            (self == 'Y' && opponent == 'A') ||
            (self == 'Z' && opponent == 'B')
            ) {
        win_point = 6;
    }

    return win_point + hand_point;
}

int get_line_point(FILE* file) {
    /* Get the points for the next line. Return -1 on EOF*/
    char line[3];
    
    int status = get_next_line(file, line, sizeof(line) + 1);
        
    if (status && line[0] != '\n') {
        char opponent_draw = line[0];
        char self_draw = line[2];
        return get_point(self_draw, opponent_draw);
    }

    return status - 1;
}

int get_total(FILE* file) {
    int total = 0;
    
    while(1) {
        int point = get_line_point(file);

        if (point == -1) {
            return total;
        }

        total += point;
    }
}

int main() {
    FILE* file = fopen(FILE_NAME, "r"); 

    printf("Total score: %d\n", get_total(file));

    return 0;
}
