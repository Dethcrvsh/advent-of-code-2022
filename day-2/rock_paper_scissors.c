#include <stdio.h>
#include <string.h>


char FILE_NAME[] = "input";

int get_next_line(FILE* file, char* line, int size) {
    /* Return 1 on success, 0 on error or EOF */
    char* str = fgets(line, size, file);

    return str != NULL;
}

char get_move(char opponent, int strategy) {
    /* Get the move to win against the opponent. 
     * -1 for loosing, 0 for draw, 1 for winning 
     */
    return (((opponent - 65) + strategy) % 3 + 3) % 3 + 88;
}

int is_draw(char self, char opponent) {
    return self - 23 == opponent;
}

int is_win(char self, char opponent) {
    // Positive module is cursed
    return (((self - 88) - (opponent - 65)) % 3 + 3) % 3 == 1;
}

int get_point(char self, char opponent, int adv) {
    int win_point = 0;

    if (adv == 1) {
        self = get_move(opponent, self - 88 - 1);
    }
    
    // Displace by the integer value of char 'X'
    int hand_point = (int) self - 88 + 1;

    if (is_draw(self, opponent)) {
        win_point = 3;
    } else if (is_win(self, opponent)) {
        win_point = 6;
    }
    
    return win_point + hand_point;
}

int get_line_point(FILE* file, int adv) {
    /* Get the points for the next line. Return -1 on EOF*/
    char line[3];
    
    int status = get_next_line(file, line, sizeof(line) + 1);
        
    if (status && line[0] != '\n') {
        char opponent_draw = line[0];
        char self_draw = line[2];

        return get_point(self_draw, opponent_draw, adv);
    }
    return status - 1;
}

int get_total(FILE* file, int adv) {
    int total = 0;
    
    while(1) {
        int point = get_line_point(file, adv);

        if (point == -1) {
            return total;
        }

        total += point;
    }
}

int main() {
    FILE* file = fopen(FILE_NAME, "r"); 
    
    printf("Part 1:\n");
    printf("    Total score: %d\n\n", get_total(file, 0));

    rewind(file);

    printf("Part 2:\n");
    printf("    Total score: %d\n", get_total(file, 1));

    return 0;
}
