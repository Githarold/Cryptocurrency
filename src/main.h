/**
 @file      main.h
 @brief     각 모듈 헤더 파일 include 및 전역 변수 선언
 @author    이승헌, 이태겸
*/

#ifndef MAIN_H
#define MAIN_H

#include "defs.h"

#include "init.h"
#include "input.h"
#include "trade.h"
#include "get_info.h"
#include "draw_chart.h"
// #include "action.h"

/* 사용하는 전역 변수 */
char ticker[50];
char url[BUFF_SIZE];
short in_position_flag;                     // 0 : not in position / 1 : in position
short short_long_flag;                      // 0 : Short / 1 : Long
int i, check;
int leverage;
int mouse_x, mouse_y;
float trade_rate;
double left_money = 1000000.0;
double coef;
double max_min_percent = 3;
double coef_chart, coef_chart_before;

App app;
Data coin_data;
Entity layout;
Entity chart[40];
Entity chart_kkori[40];
Entity chart_volume[40];





// 레이아웃 상의 position 박스에 쓰일 텍스트 

Text coin_price_board;
Text left_money_board;
Text buy_price_board;
Text liquidation_money_board;
Text rate_of_return_board;
Text profits_board;



#endif