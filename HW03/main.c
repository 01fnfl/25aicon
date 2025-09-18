#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define PI 3.14159226535897

void moveCursor(int x, int y)
{
    printf("\x1b[%d;%dH", y, x);
}

//매개변수 isExploded
//0: 폭발전 폭탄
//1: 폭발함
void printBomb(int isExploded)
{
    //폭탄은 항상 7칸
    if (isExploded)
    {
        printf("\x1b[A^^^^^^^");
        printf("\x1b[B\x1b[7D!!BAM!!");
        printf("\x1b[B\x1b[7D^^^^^^^");
    }
    else
        printf("(  b  )");
}

int main()
{
    // 여기부터 코드를 작성하세요----------------------   

    int startX = 14, startY = 9;      // 불꽃 시작 좌표
    int x = startX, y = startY;

    int bombX = 2, bombY = 2;         // 폭탄 고정 좌표 (심지 시작점)
    const int BOMB_LEN = 7;           // "(  b  )" 폭 7칸

    /* 방향: ↓ → ↑ ← (반시계) */
    int dirX[4] = { 0, 1, 0, -1 };
    int dirY[4] = { 1, 0,-1,  0 };

    /* 이동 길이 패턴 */
    int moves[12] = { 1,2,4,4,6,6,8,8,10,10,12,13 };  // 총 66칸 이동 (폭탄)

    int tx, ty, nx, ny;
    int i, j, d;

    /* 1) 심지(#) 전체 그리기 */
    tx = x; ty = y;
    for (i = 0; i < 12; i++) {
        d = i % 4;
        for (j = 0; j < moves[i]; j++) {
            tx += dirX[d];
            ty += dirY[d];
            moveCursor(tx, ty);
            printf("#");
        }
    }

    /* 2) 폭탄 출력 */
    moveCursor(bombX, bombY);  // 폭탄 위치 커서 이동  (상대 ANSI라 반드시 필요)
    printBomb(0);  // 폭탄 전 폭탄 출력 

    /* 3) 불꽃 이동(200ms), 지나간 자리 ' ' 로 지움 */
    tx = x; ty = y;
    moveCursor(tx, ty); printf("*");

    for (i = 0; i < 12; i++) {
        d = i % 4;
        for (j = 0; j < moves[i]; j++) {
            Sleep(200);

            /* 현재 불꽃 지우기 */
            moveCursor(tx, ty); printf(" ");

            /* 다음 칸 미리 계산 */
            nx = tx + dirX[d];
            ny = ty + dirY[d];

            /* 다음 칸이 폭탄 문자열 영역이면: * 찍지 않고 즉시 폭발 */
            if (ny == bombY && nx >= bombX && nx <= bombX + BOMB_LEN - 1) {
                moveCursor(bombX, bombY);   // 폭발 위치 정렬(상대 ANSI라 반드시 필요)
                printBomb(1);
                moveCursor(10, 20);
                return 0;
            }

            /* 일반 이동: 불꽃 찍기 */
            tx = nx; ty = ny;
            moveCursor(tx, ty); printf("*");
        }
    }

    // 여기까지 코드를 작성하세요----------------------   

    moveCursor(10, 20);
    return 0;
}
