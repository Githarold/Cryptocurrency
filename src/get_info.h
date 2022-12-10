/**
 @file      get_info.h
 @brief     데이터 수신부
 @author    이태겸
*/

#ifndef GETINFO_H
#define GETINFO_H

#include "defs.h"
#include "input.h"

#define URL_OPTION "&count=1"
#define JSON ".json"

extern int check, i;
extern char ticker[50];
extern char url[BUFF_SIZE];
extern double coef;
extern double max_min_percent;
extern double coef_chart, coef_chart_before;
extern Data coin_data;
extern Entity chart[30];
extern Entity chart_kkori[30];
extern Entity chart_volume[30];

/**
 @brief 입력받은 티커를 통해 url을 생성한다.

 @return 리턴 값 없음
*/
void make_url(void);

/**
 @brief API에서 정보를 받아와 json파일로 저장한다.

 정보를 받아와 처리할 수 있도록 json 파일 형식으로 저장

 @return 리턴 값 없음
*/
void get_info(void);

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