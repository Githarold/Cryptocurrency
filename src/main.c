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
    InitScoreBoard();
    
    ShowWindow();

    while (1) {
        ClearWindow();
        get_info();
        GetBoardInfo(); 
        data_processing();
        data_coef();
        GetInput();
        // position에 들어가 있을 경우
        // if (in_position_flag)                // 이거 밑으로 옮김 렌더링 순서때문에 상관없겟지??
        // {
        //     calculate_position(leverage);
        //     DrawPositionInfo();
        //     // ShowWindow();
        // }
        checktime();
        DefineChartHeight();
        DrawChart();
        if (in_position_flag)
        {
            calculate_position(leverage);
            DrawPositionInfo();
        }
        ShowWindow();
        SDL_Delay(100);
        // app.font = TTF_OpenFont("./ttf/KoPubWorld Dotum Bold.ttf", 22);
    }

    return 0;
}