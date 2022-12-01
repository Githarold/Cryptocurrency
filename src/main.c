/**
 @file      main.c
 @brief     YoungAndRich 프로그램 main 함수를 정의한 소스 파일
 @author    이승헌
 */
#include "main.h"

int main(void) {
    char url[BUFF_SIZE] = URL;
    make_url(url);

    // 초기화
    InitSDL();
    InitTTF();

    while (1) {
        get_info(url);
        GetInput();

    }

    return 0;
}