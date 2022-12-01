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

#define URL "https://api.bithumb.com/public/ticker/"

/* 사용하는 전역 변수 */
Data data;
App app;

#endif