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
#include "trade.h"
#include "get_info.h"
#include "draw_chart.h"

/* 사용하는 전역 변수 */
char ticker[50];
char url[BUFF_SIZE];
short in_position_flag, short_long_flag;                      // 0 : Short / 1 : Long
int i, check;
int leverage;
int mouse_x, mouse_y;
float trade_rate;
double left_money = 26000000.0;
double coef;
double max_min_percent = 3;
double coef_chart, coef_chart_before;

App app;
Data coin_data;
Entity layout;
Entity chart[30];
Entity chart_kkori[30];
Entity chart_volume[30];

#endif