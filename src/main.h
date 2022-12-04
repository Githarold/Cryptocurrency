/**
 @file      main.h
 @brief     각 모듈 헤더 파일 include 및 전역 변수 선언
 @author    이승헌
*/

#ifndef MAIN_H
#define MAIN_H

#include "defs.h"

#include "init.h"
#include "input.h"
#include "get_info.h"
#include "draw_chart.h"

#define URL "https://api.upbit.com/v1/ticker?markets=krw-"
#define URL_CANDLE "https://api.upbit.com/v1/candles/minutes/1?market=KRW-BTC&count=1"

/* 사용하는 전역 변수 */
int check = 60;
int mouse_x, mouse_y;
// int GREEN[4] = {0,255,0,1};
// int RED[4] = {255,0,0,1};
// int COLOR[4];
Data coin_data;
App app;
// Chart_info bar_chart_info, line_chart_info;
// RECT rect;
// SDL_Rect rt[60];
int i = 0;
Entity chart[60];
Entity chart_kkori[60];
double coef;



#endif