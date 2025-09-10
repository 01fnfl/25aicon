#include <windows.h>
#include <stdio.h>

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    int x = 1, y = 2, w = 6, h = 5;

    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            gotoxy(x + col, y + row);
            if (row == 0 || row == h - 1 || col == 0 || col == w - 1)
                putchar('*');
            else
                putchar(' ');
        }
    }
    return 0;
}
