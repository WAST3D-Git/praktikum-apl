#ifndef COLOR_UTILS_H
#define COLOR_UTILS_H

#include <windows.h>
#include <string>

enum Color {
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    YELLOW = 14,
    WHITE = 15
};

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void resetColor() {
    setColor(WHITE);
}

#endif