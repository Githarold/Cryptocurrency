/**
 @file      defs.h
 @brief     데이터타입 및 상수 정의
 @author    이승헌
*/

#ifndef DEFS_H
#define DEFS_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "curl/curl.h"
#include "json-c/json.h"
#include "time.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

#define BUFF_SIZE 1024      // 문자열 버퍼 크기
#define SCREEN_WIDTH 640    // 화면 너피(픽셀)
#define SCREEN_HEIGHT 480   // 화면 높이(픽셀)

/* 구조체 정의 */
/**
 @brief  Data : 코인의 가격, 변동량, 거래량 등의 정보가 담겨있는 구조체
*/
typedef struct {
    unsigned long price;
    unsigned long fluctate_rate;
    unsigned long units_traded;
    unsigned long date;
} Data;

#endif