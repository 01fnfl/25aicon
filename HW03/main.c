#include <stdio.h>
#include <Windows.h>
#include <math.h>

#define PI 3.141592653589793

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

void printBomb(int isExploded)
{
    if (isExploded)
    {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else {
        printf("(  b  )");
    }
}

int main() {

    int bombPosX = 1, bombPosY = 3;
    int startX = 14, startY = 9;

    printf("\x1b[?25l");

    // ��ź ����ϱ� 
    moveCursor(bombPosX, bombPosY);
    printBomb(0);
    fflush(stdout);

    // ���� ������ ���
    moveCursor(startX, startY);
    printf("*");
    fflush(stdout);

    int distances[] = { 2,2,4,4,6,6,8,8,10,10,12,12 };
    int distanceCount = sizeof(distances) / sizeof(distances[0]);

    int currentPathX = startX;
    int currentPathY = startY;
    double angle = 270.0;

    int pathX[200], pathY[200];
    int path_count = 0;

    // ������ ����
    pathX[path_count] = currentPathX;
    pathY[path_count] = currentPathY;
    path_count++;

    // ���� ��� ���
    for (int i = 0; i < distanceCount; i++) {
        double rad = angle * PI / 180.0;
        int dx = (int)round(cos(rad));
        int dy = -(int)round(sin(rad));

        for (int step = 0; step < distances[i]; step++) {
            currentPathX += dx;
            currentPathY += dy;
            pathX[path_count] = currentPathX;
            pathY[path_count] = currentPathY;
            path_count++;
        }
        angle += 90.0;
    }

    // ��ü ��� ���
    for (int i = 0; i < path_count; i++) {
        moveCursor(pathX[i], pathY[i]);
        printf("%c", (i == 0) ? '*' : '#');
    }
    fflush(stdout);
    Sleep(1500);

    // ���� �¿�� �ִϸ��̼�
    for (int i = 0; i < path_count; i++) {
        moveCursor(pathX[i], pathY[i]);
        printf(" ");
        if (i + 1 < path_count) {
            moveCursor(pathX[i + 1], pathY[i + 1]);
            printf("*");
        }
        fflush(stdout);
        Sleep(200);
    }

    // ����
    moveCursor(bombPosX, bombPosY);
    printBomb(1);

    moveCursor(0, 20);
    return 0;
}
