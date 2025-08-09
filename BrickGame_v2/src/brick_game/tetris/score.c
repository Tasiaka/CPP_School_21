// score.c
#include "tetris.h"
#include <stdio.h>

static void RemoveFullLine(int UsedField[][10], int line) {
    for (int j = 0; j < 10; j++) UsedField[line][j] = 0;
    for (int i = line; i > 0; i--)
        for (int j = 0; j < 10; j++)
            UsedField[i][j] = UsedField[i-1][j];
}

static int CheckFullLine(int UsedField[][10]) {
    int FullLine = 0;
    int Summarize = 0;
    for (int i = 19; i > 0; i--) {
        for (int j = 0; j < 10; j++) {
            Summarize += UsedField[i][j];
            if (Summarize == 10) {
                RemoveFullLine(UsedField, i);
                FullLine += 1;
                i++;
            }
        }
        Summarize = 0;
    }
    return FullLine;
}

void CalculateScore(FullGameStat *data_tetris_add) {
    int FullLine;
    if ((FullLine = CheckFullLine(data_tetris_add->UsedField))) {
        switch (FullLine) {
            case 1: data_tetris_add->data_tetris.score += 100;  break;
            case 2: data_tetris_add->data_tetris.score += 300;  break;
            case 3: data_tetris_add->data_tetris.score += 700;  break;
            case 4: data_tetris_add->data_tetris.score += 1500; break;
            default: break;
        }

        int new_level = data_tetris_add->data_tetris.score / 600 + 1;
        if (new_level > 10) new_level = 10;
        data_tetris_add->data_tetris.level = new_level;
    }

    if (data_tetris_add->data_tetris.score > data_tetris_add->data_tetris.high_score) {
        data_tetris_add->data_tetris.high_score = data_tetris_add->data_tetris.score;
        FILE *file = fopen("BestScore", "w");
        if (file) {
            fprintf(file, "%d", data_tetris_add->data_tetris.high_score);
            fclose(file);
        }
    }
}
