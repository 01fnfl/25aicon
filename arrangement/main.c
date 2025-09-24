#include <stdio.h>
#include <stdlib.h>

#define Key_a 97
#define Key_z 122

int swap(char* a, char* b)
{
    char c;
    c = *a;
    *a = *b;
    *b = c;
    return 0;
}

int main()
{
    char random[Key_z - Key_a + 1];

    // 배열 초기화
    int i = 0;
    for (i = 0; i < Key_z - Key_a + 1; i++)
    {
        random[i] = 0;
    }

    // 난수로 알파벳 무작위 배치
    for (i = 0; i < Key_z - Key_a + 1; i++)
    {
        while (1)
        {
            int rand_index = rand() % (Key_z - Key_a + 1);
            if (random[rand_index] == 0)
            {
                random[rand_index] = (char)(i + Key_a);
                break;
            }
        }
    }

    // 버블 정렬
    for (i = 0; i < Key_z - Key_a; i++)
    {
        for (int j = 0; j < Key_z - Key_a - i; j++)
        {
            if (random[j] > random[j + 1])
            {
                swap(&random[j], &random[j + 1]);
            }
        }
    }

    // 출력
    printf("\t\trandom\tsort");
    for (i = 0; i < Key_z - Key_a + 1; i++)
    {
        printf("\n\t%d\t%c\t%c", i, random[i], random[i]);
    }

    return 0;
}