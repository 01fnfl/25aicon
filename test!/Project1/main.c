#include <windows.h>  // 윈도우 콘솔 조작을 위한 헤더 (커서 위치 이동에 필요)
#include <stdio.h>    // 표준 입출력 함수 사용을 위한 헤더 (printf 함수 사용)

// 커서를 콘솔 화면의 (x, y) 좌표로 이동시키는 함수
void gotoxy(int x, int y) {
    COORD pos = { x, y };  // COORD 구조체에 x, y 좌표 저장
    // 콘솔 표준 출력 핸들 가져와서 커서 위치를 pos로 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    int x = 1, y = 2;   // 사각형의 왼쪽 위 모서리 위치 (열, 행)
    int w = 6, h = 5;   // 사각형의 너비와 높이

    int row = 0;        // 현재 행 번호 초기화
    while (row < h) {   // 행이 사각형 높이보다 작으면 반복
        int col = 0;    // 현재 열 번호 초기화
        while (col < w) {   // 열이 사각형 너비보다 작으면 반복

            // 사각형 테두리 조건:
            // 첫 번째 행 또는 마지막 행, 첫 번째 열 또는 마지막 열인 경우
            if (row == 0 || row == h - 1 || col == 0 || col == w - 1) {
                gotoxy(x + col, y + row);  // 커서를 별 찍을 위치로 이동
                printf("*");                // 별 문자 출력
            }
            // 테두리가 아닌 내부 공간은 출력하지 않고 넘어감

            col++;  // 다음 열로 이동
        }
        row++;  // 다음 행으로 이동
    }

    return 0;   // 프로그램 정상 종료
}
