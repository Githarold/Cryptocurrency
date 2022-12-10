/**
 @file      draw_chart.h
 @brief     차트 구현을 위한 함수 선언
 @author    이태겸
*/

#ifndef DRAW_CHART_H
#define DRAW_CHART_H

#include "defs.h"

extern int check;
// extern int GREEN[4];
// extern int RED[4];
extern Data coin_data;
extern App app;
// extern Chart_info bar_chart_info, line_chart_info;
// extern int COLOR[4];
// extern RECT rect;
// extern SDL_Rect rt[60];
extern int i;
extern Entity chart[30];
extern Entity chart_kkori[30];
extern Entity chart_volume[30];
extern Entity layout;
extern double coef_chart, coef_chart_before;

extern Text coin_price_board;
extern Text left_money_board;
extern Text buy_money_board;
extern Text liquidation_money_board;
extern Text rate_of_return_board;
extern Text profits_board;

void ClearWindow(void);
void ShowWindow(void);
void checktime(void);
void DefineChartHeight(void);
void RenderChart(Entity *object);
void DrawChart(void);
void RenderBoard(Text *object);

// void check_1m_and_get_chart_info(void);
// void green_or_red(void);
// void draw_chart(void);

#endif