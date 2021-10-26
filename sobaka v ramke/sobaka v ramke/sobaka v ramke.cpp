// sobaka v ramke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
using namespace std;
#include <string>
#include <Windows.h>

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

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

void generate_new_apple() {
    apple_x = rand() % areaWidth;
    apple_y = rand() % areaHeight;
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
        generate_new_apple();
        score++;
    }
}



int main()
{
    generate_new_apple();
    while (true) {
        get_input();
        show_frame();
    }
    
    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
