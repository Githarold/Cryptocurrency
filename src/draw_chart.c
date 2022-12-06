/**
 @file      draw_chart.c
 @brief     차트 구현 함수를 정의한 소스파일
 @author    이태겸
 */

#include "draw_chart.h"

void ClearWindow(void) 
{
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    SDL_RenderClear(app.renderer);

    return;
}

void ShowWindow(void)
{
    SDL_RenderPresent(app.renderer);

    return;
}

void checktime(void)
{
    // if((SDL_GetTicks()/1000 - check) == 0)              // 수정 필요 
    // if(coin_data.candle_date_time_kst_check[20] != coin_data.candle_date_time_kst[20])
    if(strcmp(coin_data.candle_date_time_kst, coin_data.candle_date_time_kst_check))
    {
        // check += 60;
        i = i + 1;
        // chart[i].pos.y = 600 - coin_data.trade_coef; 
        // chart_kkori[i].pos.y = 600 - coin_data.trade_coef; 
        // coin_data.candle_date_time_kst_check[20] = coin_data.candle_date_time_kst[20];
        strcpy(coin_data.candle_date_time_kst_check, coin_data.candle_date_time_kst);
        SDL_Delay(100);     
    }
    //printf("i : %d  chart[i].pos.y = %d  coin_data.trade_coef = %f", i, chart[i].pos.y, -coin_data.trade_coef + 900);
    //printf("%s   %s\n", coin_data.candle_date_time_kst_check[20], coin_data.candle_date_time_kst[20]);
    // printf("%d\n", i);
}


void DefineChartHeight(void)
{   
    if(coin_data.trade_coef < coin_data.opening_coef)
    {
        chart[i].pos.y = 600 - coin_data.opening_coef;
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/red.png");
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/redline.png");
    }
    else
    {
        chart[i].pos.y = 600 - coin_data.trade_coef; 
        chart[i].texture = IMG_LoadTexture(app.renderer, "./gfx/green.png");
        chart_kkori[i].texture = IMG_LoadTexture(app.renderer, "./gfx/greenline.png");
    }

    chart[i].pos.h = abs(round(coin_data.trade_coef - coin_data.opening_coef));   // 600 -> 900
    chart_kkori[i].pos.h = abs(round(coin_data.high_coef - coin_data.low_coef)); 

    if(chart[i].pos.h == 0)
    {
        chart[i].pos.h = 1;
    }

    chart_kkori[i].pos.y = 600 - coin_data.high_coef; 
    printf("%.2f   %.2f    %d\n", coin_data.trade_coef, coin_data.trade_price, i);

    // printf("%.2f  %.2f  %d  %d zzzz\n", coin_data.trade_price, 600 - coin_data.trade_coef, chart[i].pos.y, chart[i].pos.h);              // 12/6 
    // printf("%d  %d  %d  %d  가격 : %.2f\n", chart[i].pos.h, chart[i].pos.x, chart[i].pos.y, chart[i].pos.w, coin_data.trade_price);
}

void RenderChart(Entity *object)
{
    // SDL_QueryTexture(object->texture, NULL, NULL, &(object->pos.w), &(object->pos.h));
    SDL_RenderCopy(app.renderer, object->texture, NULL, &(object->pos));    //이미지를 Dst만큼의 사각형에 출력
}

void DrawChart(void)
{
    for (int i = 0; i < 60 ; i++) 
    {
        RenderChart(&(chart[i]));
        RenderChart(&(chart_kkori[i]));
    }
}

//##################################################################
// 

// if(SDL_GetTicks() == 60)
//     {
        
//     }

// void check_1m_and_get_chart_info(void)
// {
//     bar_chart_info.y2 = coin_data.trade_price;  // 원점이 좌측 상단이라 값 변환 해줌
//     line_chart_info.y1 = 600-coin_data.ath_1m*300/coin_data.start_trade_price;
//     printf("%d  %d  %d  %d  %d\n",SDL_GetTicks()/1000, check, SDL_GetTicks()/1000 - check, i, coin_data.trade_price);
//     if((SDL_GetTicks()/1000 - check) == 0)
//     {
//         check += 10;
//         bar_chart_info.y1 = coin_data.trade_price;
//         bar_chart_info.x1 += 20;
//         bar_chart_info.x2 = bar_chart_info.x1 + 20;
//         line_chart_info.x1 = (bar_chart_info.x1 + bar_chart_info.x2)/2;
//         bar_chart_info.y1 = coin_data.trade_price;
//         i++;
//     }
//     // rt[1] = {bar_chart_info.x1, bar_chart_info.y2, 20, bar_chart_info.y2-bar_chart_info.y1};
//     rt[i].x = bar_chart_info.x1;
//     rt[i].y = bar_chart_info.y2;
//     rt[i].w = 20;
//     rt[i].h = bar_chart_info.y2-bar_chart_info.y1;
// }


// void green_or_red(void)
// {
//     // bar_chart_info.y2 = coin_data.trade_price;
//     // line_chart_info.y1 = coin_data.ath_1m;

//     if(bar_chart_info.y1 <= bar_chart_info.y2)      // 양전, 초록색으로 그림
//     {
//         // COLOR[4] = GREEN[4];
//         // line_chart_info.color[4] = GREEN[4];
//         SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 1);
//     }

//     else      // 음전, 빨간색으로 그림
//     {
//         // COLOR[4] = RED[4];
//         // line_chart_info.color[4] = RED[4];
//         SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 1);
//     }
// }

// void draw_chart(void)
// {
//     SDL_RenderFillRects(app.renderer, &rt[i], 60);
//     SDL_RenderPresent(app.renderer);
//     // SDL_RenderClear(app.renderer);
// }
