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

int apples = 0;

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void PrintMap(char *map, int width, int height){
    for (int i = 0; i < width + 2; ++i)
    {
        printf("-");
    }
    printf("\n");
    for (int y = 0; y < height; y++){
        printf("|");
        for (int x = 0; x < width; x++){
            printf("%c", map[y * width + x]);
        }
        printf("|\n");
    }
    for (int i = 0; i < width + 2; ++i)
    {
        printf("-");
    }
}

int GetMapCoords(int x, int y, int width){
    return y * width + x;
}

int MoveSnake(char *map, Snake *snake, int width, int height, int *isCollision)
{
    int last_pos = snake->snake_body_pos[snake->head_pos_index];
    int size = width * height;
    snake->head_pos_index = (snake->head_pos_index + 1) % snake->map_size;
    int old_x = ((last_pos) % width);
    int new_x = ((last_pos) % width) + snake->moveDir.x;
    Vector2 og_move = snake->moveDir;
    if (old_x == width - 1 && new_x == width)
    {
        snake->moveDir.y = -1;
    }
    if (new_x == -1)
    {
        snake->moveDir.x = width - 1;
    }
    last_pos += snake->moveDir.x;
    int new_y = last_pos + snake->moveDir.y * width;
    if (new_y < 0)
    {
        new_y = size + new_y;
    }
    if (size - 1 < new_y)
    {
        new_y = 0 + (new_y - size);
    }
    int new_pos = new_y;
    snake->moveDir = og_move;

    snake->snake_body_pos[snake->head_pos_index] = new_pos;

    int isApple = map[snake->snake_body_pos[snake->head_pos_index]] == 'A';

    map[snake->snake_body_pos[snake->tail_pos_index]] = ' ';
    if (!isApple)
    {
        snake->tail_pos_index = (snake->tail_pos_index + 1) % snake->map_size;
    }

    if (map[snake->snake_body_pos[snake->head_pos_index]] == 'S')
    {
        *isCollision = 1;
    }
    map[snake->snake_body_pos[snake->head_pos_index]] = 'S';

    return isApple;
}

void PlaceApple(char *map, int size)
{
    int random;
    do
    {
        random = rand() % (size - 1);
    } while (map[random] == 'S');
    map[random] = 'A';
}



int main(){
    printf("Hello World\n");
    int width = 20;
    int heigth = 10;
    int size = width * heigth;
    char *map = malloc(size);
    memset(map, ' ', size);
    int *snake_pos = malloc(size * sizeof(int));
    memset(snake_pos, -1, size * sizeof(int));
    snake_pos[0] = 5;
    srand(time(0));
    PlaceApple(map, size);
    int isCollision = 0;

    Snake snake = {
        .head_pos_index = 0,
        .tail_pos_index = 0,
        .snake_body_pos = snake_pos,
        .map_size = size,
        .moveDir = {0, 0},
    };
    int prev_time = 0;
    Vector2 snake_last_dir = snake.moveDir;

    while (1)
    {
        if (_kbhit()) 
        {
            char key = _getch();
            if (key == 'w' && snake_last_dir.y !=  1) snake.moveDir = (Vector2){ 0, -1};
            if (key == 's' && snake_last_dir.y != -1) snake.moveDir = (Vector2){ 0,  1};
            if (key == 'a' && snake_last_dir.x !=  1) snake.moveDir = (Vector2){-1,  0};
            if (key == 'd' && snake_last_dir.x != -1) snake.moveDir = (Vector2){ 1,  0};
        }
        
        if (prev_time != time(NULL))
        {
            clear();
            if (MoveSnake(map, &snake, width, heigth, &isCollision))
            {
                PlaceApple(map, size);
                ++apples;
            }
            snake_last_dir = snake.moveDir;
            printf("Apples eaten: %d\n", apples);
            PrintMap(map, width, heigth);
            prev_time = time(NULL);
        }

        if (isCollision)
        {
            break;
        }
    }

    printf("\nIt's over gang!\n");

    return 0;
}