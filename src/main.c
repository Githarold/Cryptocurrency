/**
 @file      main.c
 @brief     YoungAndRich 프로그램 main 함수를 정의한 소스 파일
 @author    이승헌
 */

#include "main.h"

int main(void) {
    make_url();
    // 초기화
    InitMemorySet();
    InitSDL();
    InitTTF();
    InitLayout();
    InitChart();
    
    ShowWindow();

    while (1) {
        ClearWindow();
        get_info();
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