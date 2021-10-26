// sobaka v ramke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;
#include <string>
#include <Windows.h>
#include <time.h>       /* time */

const char Border_char = '#';

const char DogChar = '@';
short direction = 0;
const short areaWidth = 80;
const short areaHeight = 20;
short dog_x = areaHeight / 2; //place in center
short dog_y = 5;
short apple_x;
short apple_y;
const char AppleChar = 'Q';
int score = 0;
int mode = 0;
const int Levels = 3;
const string Level_list[Levels] = {"Easy", "Colored", "Imposibble"};

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77
#define ENTER_KEY 'o'

void generate_new_apple() {

    switch (mode)
    {
    case 0://normal mode
        srand(time(NULL));
        apple_x = rand() % areaWidth;
        srand(time(NULL));
        apple_y = rand() % areaHeight;
        break;
    case 1: //harder mode
        srand(time(NULL));
        apple_x = rand() % areaWidth;
        srand(time(NULL));
        apple_y = rand() % areaHeight;
        if (score % 5 > 1 && score > 1) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            srand(time(NULL));
            SetConsoleTextAttribute(hConsole, rand() % 256);
        }
        break;
    case 2: // Imposible 
        apple_x = areaWidth + 5;
        apple_y = areaHeight/2;
        break;

    }
    
}

void ClearScreen()
{
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void show_frame() {
    string output_string = "";

    //Display Frame
    for (int i = 0; i < areaWidth + 2; i++) {
        output_string += Border_char;
    }   
    output_string += '\n';
    for (int i = 0; i < areaHeight; i++) {
        output_string += Border_char;
        for (int j = 0; j < areaWidth; j++) {
            if (i == dog_y && j == dog_x) {
                output_string += DogChar;
            }
            else if (i == apple_y && j == apple_x) {
                output_string += AppleChar;
            }
            else output_string += ' ';
        }
        output_string += Border_char;
        if (mode == 2 && apple_y == i) {
            for (int b = 0; b < apple_x - areaWidth; b++)
            {
                output_string += ' ';
            }
            output_string += AppleChar;
        }
        
        output_string += '\n';
    }
    for (int i = 0; i < areaWidth + 2; i++) {
        output_string += Border_char;
    }
    //clear console
    ClearScreen();
    //output
    cout << output_string;
    cout << '\n';
    cout << "Score: " << score;

}

void get_input() {
    int direction_key = _getch();
    if (direction_key == UP_KEY && dog_y != 0) { dog_y--; }
    if (direction_key == DOWN_KEY && dog_y != areaHeight - 1) { dog_y++; }
    if (direction_key == LEFT_KEY && dog_x != 0) { dog_x--; }
    if (direction_key == RIGHT_KEY && dog_x != areaWidth - 1) { dog_x++; }
    
    if (dog_x == apple_x && dog_y == apple_y) {
        score++;
        generate_new_apple();
    }
}

int menu() {
    int cursor = 0;
    while (true)
    {
        cout << "Choose your mode:\n";
        for (int i = 0; i < Levels; i++) {
            if (cursor == i) {
                cout << '>';
            }
            else {
                cout << ' ';
            }
            cout << i + 1 << ". " << Level_list[i] << '\n';
        }

        int direction_key = _getch();
        if (direction_key == UP_KEY && cursor > 0) { cursor--; }
        else if (direction_key == DOWN_KEY && cursor < Levels-1) { cursor++; }
        else if (direction_key == ENTER_KEY) {  return cursor; }
        //clear console
        ClearScreen();

        
    }

}

int main()
{
    mode = menu();
    generate_new_apple();
    while (true) {
        show_frame();
        get_input();
    }
    
    return 0;
}
