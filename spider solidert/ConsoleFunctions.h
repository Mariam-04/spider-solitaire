#ifndef CONSOLE_FUNCTIONS_H
#define CONSOLE_FUNCTIONS_H

#include <iostream>
#include <windows.h>

class ConsoleFunctions {
public:
    // Set the cursor position in the console
    void SetCursorAt(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Set text and background color in the console
    void SetColor(WORD textColor, WORD bgColor) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | bgColor);
    }

    // Set the console window and buffer size
    void setConsoleWindowAndBufferSize(int width, int height) {
        SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
        COORD bufferSize = {width, height};

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
        SetConsoleScreenBufferSize(hConsole, bufferSize);
    }

private:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
};

// Console color definitions
enum ConsoleColor {
    black = 0,
    blue = 1,
    green = 2,
    cyan = 3,
    red = 4,
    magenta = 5,
    brown = 6,
    lightgray = 7,
    darkgray = 8,
    lightblue = 9,
    lightgreen = 10,
    lightcyan = 11,
    lightred = 12,
    lightmagenta = 13,
    yellow = 14,
    white = 15
};

#endif // CONSOLE_FUNCTIONS_H
