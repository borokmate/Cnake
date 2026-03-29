#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct
{
    int snake_head_x;
    int snake_head_y;
    int snake_tail_x;
    int snake_tail_y;

    int head_pos;
    int tail_pos;
} Snake;

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void PrintMap(char *map, int width, int height){
    // clear();
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            printf("%c", map[y * width + x]);
        }
        printf("\n");
    }
}

int GetMapCoords(int x, int y, int width){
    return y * width + x;
}



int main(){
    printf("Hello World\n");
    int width = 5;
    int heigth = 5;
    int size = width * heigth;
    char *map = malloc(size);
    memset(map, 'O', size);
    int snake_head_x = 2;
    int snake_head_y = 2;
    int snake_tail_x = 2;
    int snake_tail_y = 2;

    int head_pos = GetMapCoords(snake_head_x, snake_head_y, width);
    int tail_pos = snake_tail_y * width + snake_tail_x;

    map[tail_pos] = 'T';
    map[head_pos] = 'H';

    while (1){
        
        if (_kbhit()) {
            char key = _getch();
            if (key == 'w') snake_head_y--;
            head_pos = GetMapCoords(snake_head_x, snake_head_y, width);
            tail_pos = GetMapCoords(snake_tail_x, snake_tail_y, width);
        }
        
        PrintMap(map, width, heigth);
        Sleep(1000 / 60);
    }

    return 0;
}