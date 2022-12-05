/**
 @file      main.c
 @brief     YoungAndRich 프로그램 main 함수를 정의한 소스 파일
 @author    이승헌
 */
#include "main.h"


int main(void) {
    char url[BUFF_SIZE] = URL;
    make_url(url);
    // printf("1");
    // 초기화
    InitMemorySet();
    // printf("2");
    InitSDL();
    // printf("3");
    InitTTF();
    // printf("4");
    InitChart();
    // printf("5");

    while (1) {
        ClearWindow();        
        get_info(url);
        // printf("%d  %d  %d  %d  %f\n", i, chart[i].pos.y, SDL_GetTicks()/1000 - check, check, coin_data.price);
        GetInput();        
        checktime();
        DefineChartHeight();
        DrawChart();
        ShowWindow();    
        SDL_Delay(40);
    }//printf("%.1lf\n",(double)SDL_GetTicks()/1000);

    return 0;
}