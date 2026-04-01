#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

typedef struct 
{
    int x;
    int y;
} Vector2;

typedef struct
{
    int     head_pos_index;
    int     tail_pos_index;
    int    *snake_body_pos;
    int     map_size;
    Vector2 moveDir;
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
    clear();
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

int MoveSnake(char *map, Snake *snake, int width)
{
    int last_pos = snake->snake_body_pos[snake->head_pos_index]; 
    snake->head_pos_index = (snake->head_pos_index + 1) % snake->map_size;
    snake->snake_body_pos[snake->head_pos_index] = last_pos + snake->moveDir.y * width + snake->moveDir.x * 1;
    int isApple = map[snake->snake_body_pos[snake->head_pos_index]] == 'A';
    if (map[snake->snake_body_pos[snake->tail_pos_index]] == 'A')
        printf("WHYY\n");
    map[snake->snake_body_pos[snake->tail_pos_index]] = ' ';
    if (!isApple)
        snake->tail_pos_index = (snake->tail_pos_index + 1) % snake->map_size;
    map[snake->snake_body_pos[snake->head_pos_index]] = 'S';
    return isApple;
}

void PlaceApple(char *map, int size)
{
    int random;
    do
    {
        random = rand() % size - 1;
    } while (map[random] == 'S');

    map[random] = 'A';
}



int main(){
    printf("Hello World\n");
    int width = 5;
    int heigth = 5;
    int size = width * heigth;
    char *map = malloc(size);
    memset(map, ' ', size);
    int *snake_pos = malloc(size * sizeof(int));
    memset(snake_pos, -1, size * sizeof(int));
    snake_pos[0] = 5;
    map[GetMapCoords(3, 4, width)] = 'A';

    Snake snake = {
        .head_pos_index = 0,
        .tail_pos_index = 0,
        .snake_body_pos = snake_pos,
        .map_size = size,
        .moveDir = {0, 0},
    };
    int prev_time = 0;

    while (1){
        if (_kbhit()) {
            char key = _getch();
            if (key == 'w') snake.moveDir = (Vector2){0, -1};
            if (key == 's') snake.moveDir = (Vector2){0, 1};
            if (key == 'a') snake.moveDir = (Vector2){-1, 0};
            if (key == 'd') snake.moveDir = (Vector2){1, 0};
        }
        
        if (prev_time != time(NULL))
        {
            if (MoveSnake(map, &snake, width))
            {
                PlaceApple(map, size);
            }
            PrintMap(map, width, heigth);
            prev_time = time(NULL);
        }
        
    }

    return 0;
}