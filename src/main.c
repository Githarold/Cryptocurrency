/**
 @file      main.c
 @brief     YoungAndRich 프로그램 main 함수를 정의한 소스 파일
 @author    이승헌
 */
#include "main.h"


int main(void) {
    char url[BUFF_SIZE] = URL_CANDLE;
    make_url(url);
    // 초기화
    InitMemorySet();
    InitSDL();
    InitTTF();
    InitChart();

    while (1) {
        ClearWindow();
        get_info(url);
        data_processing();
        data_coef();
        GetInput();
        checktime();
        DefineChartHeight();
        DrawChart();
        ShowWindow();
        SDL_Delay(100);
    }

    return 0;
}