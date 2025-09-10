#include <windows.h>  // Windows API �Լ� ����� ���� ��� (�ܼ� Ŀ�� ��ġ ����)
#include <stdio.h>    // ǥ�� ����� �Լ� ����� ���� ��� (printf �Լ�)

// Ŀ���� �ֿܼ��� Ư�� ��ġ(x, y)�� �̵���Ű�� �Լ�
void gotoxy(int x, int y) {
    COORD pos = { x, y };  // COORD ����ü�� x, y ��ǥ ����
    // ǥ�� ��� �ڵ�(�ܼ�)���� Ŀ�� ��ġ�� pos�� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    int x = 1, y = 2;   // �簢���� ���� �� �𼭸� ��ġ ��ǥ
    int w = 6, h = 5;   // �簢���� �ʺ�� ����

    int row = 0;        // �� �ε��� �ʱ�ȭ
    while (row < h) {   // ����(h)��ŭ �ݺ� (�� ����)
        int col = 0;    // �� �ε��� �ʱ�ȭ
        while (col < w) {   // �ʺ�(w)��ŭ �ݺ� (�� ����)

            // �׵θ��� �ش��ϴ� ��ġ���� �˻�
            // ù ��(row == 0), ������ ��(row == h - 1), ù ��(col == 0), ������ ��(col == w - 1)�� ���� ����
            if (row == 0 || row == h - 1 || col == 0 || col == w - 1) {
                gotoxy(x + col, y + row);  // Ŀ���� ����� ��ġ�� �̵�
                printf("*");                // �� ��� (�� ���� �� ���ھ� ���)
            }
            // ���� ����(��ĭ)�� ������� �ʰ� �׳� �Ѿ

            col++;  // ���� ���� �̵�
        }
        row++;  // ���� ������ �̵�
    }

    return 0;   // ���α׷� ���� ����
}
