#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<map>
#include<time.h>
#include<windows.h>

#include"snake.h"

using namespace std;

map<int, map<int, char>> frame;

float speed = 3.0;

int width = 50;
int height = 50;
int head_pos_x;
int head_pos_y;
int body_pos_x;
int body_pos_y;
int fruit_x;
int fruit_y;
int score;
int i, j;

Snake snake;

char head = '\351';
char body_part = 'o';
char fruit = '\242';

bool game_over;
bool direccion;
bool wich_ward;


void initialize();
void add_body();
void update();
void generate_fruit();
void change_direction(char d);
void move_head();
void print_map();

// funcion main
int main()
{
    initialize();
    generate_fruit();

    do
    {
        update();
        if (_kbhit())
        {
            change_direction(_getch());
        }
    } while (game_over == false);

    cout << "Fin del juego!" << endl;

    return 0;
}

void initialize()
{
    score = 0;

    for (i = 0; i < width; i++)
        frame[0][i] = '\262';

    for (i = 1; i < height - 1; i++)
    {
        frame[i][0] = '\262';
        for (j = 1; j < width - 1; j++)
            frame[i][j] = ' ';
        frame[i][j] = '\262';
    }

    for (i = 0; i < width; i++)
        frame[height - 1][i] = '\262';


    frame[1][1] = '\311';
    for (i = 2; i < width - 2; i++)
        frame[1][i] = frame[height - 2][i] = '\315';
    frame[1][i] = '\273';

    for (i = 2; i < height - 2; i++)
        frame[i][1] = frame[i][width - 2] = '\272';
    frame[i][1] = '\310';
    frame[i][width - 2] = '\274';

    srand(time(NULL));
    head_pos_x = (rand() % (width - 4)) + 4;
    head_pos_y = (rand() & (height - 5)) + 2;

    frame[head_pos_y][head_pos_x] = head;
    snake.insert_tail(head_pos_x - 2, head_pos_y);
    frame[head_pos_y][head_pos_x - 2] = body_part;
    snake.insert_tail(head_pos_x - 1, head_pos_y);
    frame[head_pos_y][head_pos_x - 1] = body_part;

    print_map();
    direccion = 0;
    wich_ward = 0;
    game_over = false;
    Sleep(1000 / speed);
}

void add_body()
{
    move_head();
    print_map();
    Sleep(1000 / speed);
}

void update()
{
    move_head();
    snake.clear_tail(body_pos_x, body_pos_y);
    frame[body_pos_y, body_pos_x] = ' ';
    print_map();
    Sleep(1000 / speed);
}

void generate_fruit()
{
    fruit_x = (rand() % (width - 7)) + 3;
    fruit_y = (rand() % (height - 6)) + 3;
    if (frame[fruit_y][fruit_x] == ' ')
        frame[fruit_y][fruit_x] = fruit;
    else generate_fruit();
}

void change_direction(char d)
{
    if ((d == 'w' || d == 'W' || d == 's' || d == 'S') && direccion == 0)
    {
		if (d == 'w' || d == 'W')
            wich_ward = 0;
		else
            wich_ward = 1;
        direccion = 1;
	}
	else if ((d == 'a' || d == 'A' || d == 'd' || d == 'D') && direccion == 1)
    {
		if (d == 'a' || d == 'A')
            wich_ward = 1;
		else
            wich_ward = 0;
		direccion = 0;
	}
}

void move_head()
{
    snake.insert_tail(head_pos_x, head_pos_y);
    frame[head_pos_y][head_pos_x] = body_part;

    if (direccion == 0 && wich_ward == 0)
        head_pos_x++;
    else if (direccion == 0 && wich_ward == 1)
        head_pos_x--;
    else if (direccion == 1 && wich_ward == 0)
        head_pos_y--;
    else if (direccion == 1 && wich_ward == 1)
        head_pos_y++;

    if (head_pos_x == fruit_x && head_pos_y == fruit_y)
    {
        score++;
        add_body();
        generate_fruit();
    }

    if (frame[head_pos_y][head_pos_x] == '\315'
        || frame[head_pos_y][head_pos_x] == '\272'
        || frame[head_pos_y][head_pos_x] == body_part)
        game_over = true;

    frame[head_pos_y][head_pos_x] = head;
}

void print_map()
{
    system("cls");
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            cout << frame[i][j];
        }
        if (i == 3)
            cout << "se w-a-s-d keys";
        if (i == 4)
            cout << "W";
        if (i == 5)
            cout << "A - D";
        if (i == 6)
            cout << "S";
        if (i == 10)
            cout << "Score: " << score;
        cout << endl;
    }
}
