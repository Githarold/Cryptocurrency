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
    InitMemorySet();
    InitSDL();
    InitTTF();
    InitChart();

    while (1) {
        ClearWindow();        
        get_info(url);
        // printf("%d  %d  %d  %d  %f\n", i, chart[i].pos.y, SDL_GetTicks()/1000 - check, check, coin_data.price);
        GetInput();        
        checktime();
        DefineChartHeight();
        DrawChart();
        ShowWindow();    
        SDL_Delay(16);
    }//printf("%.1lf\n",(double)SDL_GetTicks()/1000);

    return 0;
}