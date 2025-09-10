#include <windows.h>  // Windows API 함수 사용을 위한 헤더 (콘솔 커서 위치 조작)
#include <stdio.h>    // 표준 입출력 함수 사용을 위한 헤더 (printf 함수)

// 커서를 콘솔에서 특정 위치(x, y)로 이동시키는 함수
void gotoxy(int x, int y) {
    COORD pos = { x, y };  // COORD 구조체에 x, y 좌표 저장
    // 표준 출력 핸들(콘솔)에서 커서 위치를 pos로 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {
    int x = 1, y = 2;   // 사각형의 왼쪽 위 모서리 위치 좌표
    int w = 6, h = 5;   // 사각형의 너비와 높이

    int row = 0;        // 행 인덱스 초기화
    while (row < h) {   // 높이(h)만큼 반복 (행 단위)
        int col = 0;    // 열 인덱스 초기화
        while (col < w) {   // 너비(w)만큼 반복 (열 단위)

            // 테두리에 해당하는 위치인지 검사
            // 첫 행(row == 0), 마지막 행(row == h - 1), 첫 열(col == 0), 마지막 열(col == w - 1)일 때만 실행
            if (row == 0 || row == h - 1 || col == 0 || col == w - 1) {
                gotoxy(x + col, y + row);  // 커서를 출력할 위치로 이동
                printf("*");                // 별 출력 (한 번에 한 글자씩 출력)
            }
            // 내부 공간(빈칸)은 출력하지 않고 그냥 넘어감

            col++;  // 다음 열로 이동
        }
        row++;  // 다음 행으로 이동
    }

    return 0;   // 프로그램 정상 종료
}
