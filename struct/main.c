
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define N 5
#define LOG "log.txt"

// 물고기 이름 구조체
struct Fish { char* n; };
// 퀴즈 구조체 (문제, 정답, 맞았을 때 대사, 틀렸을 때 대사)
struct QuizSet { char* t; int a; char* o; char* x; };

// Y/N 입력 받기 (예외처리 포함)
char yn_getch() {
    char c;
    while (1) {
        c = (char)_getch();
        if (c == 'Y' || c == 'y') { printf("Y\n"); return 'Y'; }
        if (c == 'N' || c == 'n') { printf("N\n"); return 'N'; }
        printf("\nY 또는 N 중에서 선택하세요: ");
    }
}

// 로그에서 플레이 횟수와 정답 횟수 읽기
void get_stats(int* total, int* correct) {
    FILE* f = fopen(LOG, "r");
    *total = 0;
    *correct = 0;
    if (f == NULL) return; // 파일 없으면 0,0
    char buf[100];
    while (fgets(buf, sizeof(buf), f)) {
        // 물고기 이름 줄 건너뛰고 결과 줄 읽기
        if (fgets(buf, sizeof(buf), f)) {
            (*total)++;
            if (buf[0] == 'O') (*correct)++;
        }
    }
    fclose(f);
}

// 로그에 물고기 이름과 결과 저장 (O or X)
void save_log(const char* fish_name, char result) {
    FILE* f = fopen(LOG, "a");
    if (!f) {
        perror("로그 저장 실패");
        return;
    }
    fprintf(f, "%s\n%c\n", fish_name, result);
    fclose(f);
}

// 콘솔 텍스트 색상 설정 (Windows)
void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    struct Fish F[N] = { {"돌돔"}, {"참돔"}, {"광어"}, {"부시리"}, {"감성돔"} };
    struct QuizSet Q[N] = {
        {" 지브리 영화가 아닌 것은?\n(1) 천공의 성 라퓨타 (2) 센과 치히로의 모험 (3) 나의 라임 오렌지 나무 (4) 모노노케 히메", 3, "정답! 뭘 좀 아는군!", "땡! 영화를 잘 안보는구나."},
        {"유명한 소설 '어린 왕자'의 작가는 누구인가?\n(1) 생텍쥐페리 (2) 헤르만 헤세 (3) 톨스토이 (4) 셰익스피어", 1, "정확해! 책을 많이 읽나봐 .", "책 좀 읽어라"},
        {"같은 브랜드의 음식이 아닌 것은 ? \n(1) 뿌링클 (2) 콰삭킹 (3) 맛초킹 (4) 볼케이노", 4, "너 맛잘알이네!", "틀렸어. 쩝쩝박사 실패"},
        {"빛의 3원색에 들어가지 않는 색은? \n(1) 빨강 (2) 노랑 (3) 파랑 (4) 초록", 2, "정답! 상식이 꽤 있네!", "오답이야...상식을 키워봐."},
        {"이은석 교수님이 갖고 있지 않은건?\n(1) 외모 (2) 지식 (3) 친절함 (4) 패션 센스 ", 4, "은잘알!", "교수님 수업을 다시 수강하렴"}
    };

    int total_play = 0, correct_count = 0;
    get_stats(&total_play, &correct_count);

    system("cls");
    printf("===================================\n");
    printf("%d번째 게임입니다!!\n", total_play + 1);
    printf("정답률 %d/%d (%.1f%%)\n", correct_count, total_play, total_play > 0 ? (correct_count * 100.0f / total_play) : 0.0f);
    printf("===================================\n\n");

    printf("찌를 던진다 (Y/N) > ");
    char yn = yn_getch();

    if (yn == 'Y') {
        printf("찌를 던지고 기다린다");
        for (int i = 0; i < 5; i++) {
            printf(".");
            Sleep(500);
        }
        printf("\n");

        set_color(10); // 녹색 (0x0A)
        printf("입질이 왔다!!!!\n");
        set_color(7); // 기본색으로 복구

        Sleep(700);

        srand((unsigned int)time(NULL) + GetTickCount());

        int fn_i = rand() % N;
        int q_i = rand() % N;

        char* fish_name = F[fn_i].n;
        struct QuizSet quiz = Q[q_i];

        printf("\n[%s] : %s\n", fish_name, quiz.t);
        printf("답을 선택하세요 (1~4) > ");
        char ans_c = (char)_getch();
        printf("%c\n", ans_c);

        int ans = ans_c - '0';
        char log_result = 'X';

        if (ans >= 1 && ans <= 4) {
            if (ans == quiz.a) {
                printf("\n[%s] : %s\n", fish_name, quiz.o);
                printf("[성공] %s(이)를 잡았다!\n", fish_name);
                log_result = 'O';
            }
            else {
                printf("\n[%s] : %s\n", fish_name, quiz.x);
                printf("[실패] 물고기가 도망쳤다...\n");
            }
        }
        else {
            printf("\n[오류] 올바른 답(1~4)이 아니어서 물고기가 혼란스러워하며 도망갔습니다.\n");
        }

        save_log(fish_name, log_result);

        // 최신 기록 출력
        get_stats(&total_play, &correct_count);
        printf("\n===================================\n");
        printf(" 누적 결과 \n총 플레이 횟수: %d회\n정답률: %d/%d (%.1f%%)\n", total_play, correct_count, total_play, total_play > 0 ? (correct_count * 100.0f / total_play) : 0.0f);
        printf("===================================\n");
    }
    else {
        printf("낚시를 하지 않고 집으로 돌아갑니다");
        for (int i = 0; i < 5; i++) {
            printf(".");
            Sleep(500);
        }
        printf("\n");
    }

    printf("\n게임을 종료하려면 아무 키나 누르세요...\n");
    (void)_getch();

    return 0;
}
