/**
 @file      get_info.h
 @brief     데이터 수신부
 @author    이태겸
*/

#ifndef GETINFO_H
#define GETINFO_H

#include "defs.h"
extern Data coin_data;
extern double coef;

/**
 @brief 입력받은 티커를 통해 url을 생성한다.

 @return 리턴 값 없음
*/
void make_url(char *);

/**
 @brief API에서 정보를 받아온다.

 정보를 받아와 처리할 수 있도록 구조체 \ref Data 에 각 정보 할당

 @return 리턴 값 없음
*/
void get_info(const char*);



#endif