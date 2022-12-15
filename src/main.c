/**
 @file      main.c
 @brief     YoungAndRich 프로그램 main 함수를 정의한 소스 파일
 @author    이승헌, 이태겸
 */

#include "main.h"

int main(void) {
    // 초기화
    InitMemorySet();    
    InitSDL();
    InitSearchCoin();
    InitTTF();
    InitLayout();
    InitChart();
    InitBoard();
    ClearWindow();  // debug
    make_url();

    ShowWindow();

    while (1) {
        ClearWindow();
        get_info();
        GetBoardInfo();
        if (data_processing())
        {
            continue;
        }
        data_coef();
        GetInput();
        checktime();
        DefineChartHeight();
        DrawChart();
        // position에 들어가 있을 경우
        if (in_position_flag)
        {
            DrawPositionInfo();            
            calculate_position(leverage);
        }
        ShowWindow();
        SDL_Delay(100);
    }

    return 0;
}