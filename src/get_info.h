/**
 @file      get_info.h
 @brief     데이터 수신부
 @author    이태겸
*/

#ifndef GETINFO_H
#define GETINFO_H

#include "defs.h"

#define URL_OPTION "&count=1"

extern int check;
extern double coef_chart, coef_chart_before;
extern double coef;
extern Data coin_data;
extern Entity chart[60];
extern double max_min_percent;

/**
 @brief 입력받은 티커를 통해 url을 생성한다.

 @return 리턴 값 없음
*/
void make_url(char *);

/**
 @brief API에서 정보를 받아와 json파일로 저장한다.

 정보를 받아와 처리할 수 있도록 json 파일 형식으로 저장

 @return 리턴 값 없음
*/
void get_info(const char*);

/**
 @brief json 파싱을 통해 정보를 추출 및 가공한다.

 정보를 받아와 처리할 수 있도록 구조체 \ref Data 에 각 정보 할당

 @return 리턴 값 없음
*/
void data_processing(void);

/**
 @brief 가격 변동이 더욱 명확하게 보일 수 있도록 가격을 조정한다.

 차트에 가격 변동이 명확히 보이도록 구조체 \ref Data 에 각 정보 할당

 @return 리턴 값 없음
*/
void data_coef(void);

#endif