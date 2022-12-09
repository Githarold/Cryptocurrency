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

/* 사용하는 전역 변수 */
int check;
int mouse_x, mouse_y;
int i = 0;
char ticker[10], url[BUFF_SIZE];
double coef;

App app;
Data coin_data;
Entity chart[60];
Entity chart_kkori[60];
Entity chart_volume[60];
Entity layout;
double coef_chart, coef_chart_before;
double max_min_percent = 3;

#endif