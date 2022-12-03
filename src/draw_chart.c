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
    if((SDL_GetTicks()/1000 - check) == 0)
    {
        check += 60;
        i = i + 1;
        chart[i].pos.y = coin_data.price_coef; //+ 900;   // 600 -> 900
        chart_kkori[i].pos.y = coin_data.price_coef;
        
    }
    //printf("i : %d  chart[i].pos.y = %d  coin_data.price_coef = %f", i, chart[i].pos.y, -coin_data.price_coef + 900);
}


void DefineChartHeight(void)
{
    chart[i].pos.h = abs((int)coin_data.price_coef - chart[i].pos.y);   // 600 -> 900
    chart_kkori[i].pos.h = abs((int)coin_data.ath_coef - chart[i].pos.y); 

    
    printf("%d  %d  %d  %d  가격 : %.2f\n", chart[i].pos.h, chart[i].pos.x, chart[i].pos.y, chart[i].pos.w, coin_data.price);
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
//     bar_chart_info.y2 = coin_data.price;  // 원점이 좌측 상단이라 값 변환 해줌
//     line_chart_info.y1 = 600-coin_data.ath_1m*300/coin_data.start_price;
//     printf("%d  %d  %d  %d  %d\n",SDL_GetTicks()/1000, check, SDL_GetTicks()/1000 - check, i, coin_data.price);
//     if((SDL_GetTicks()/1000 - check) == 0)
//     {
//         check += 10;
//         bar_chart_info.y1 = coin_data.price;
//         bar_chart_info.x1 += 20;
//         bar_chart_info.x2 = bar_chart_info.x1 + 20;
//         line_chart_info.x1 = (bar_chart_info.x1 + bar_chart_info.x2)/2;
//         bar_chart_info.y1 = coin_data.price;
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
//     // bar_chart_info.y2 = coin_data.price;
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
