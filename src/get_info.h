/**
 @file      get_info.h
 @brief     데이터 수신부
 @author    공동
*/

#ifndef GETINFO_H
#define GETINFO_H

#include "defs.h"
#include "init.h"
#include "input.h"

#define URL_OPTION "&count=1"
#define JSON ".json"

/* main.h에 정의된 전역 변수 사용 */
extern int check, i;
extern char ticker[50];
extern char url[BUFF_SIZE];
extern double coef;
extern double max_min_percent;
extern double coef_chart, coef_chart_before;
extern double buy_price;
extern App app;
extern Data coin_data;
extern Entity chart[40];
extern Entity chart_kkori[40];
extern Entity chart_volume[40];

extern Text coin_price_board;
extern Text left_money_board;
extern Text buy_price_board;
extern Text liquidation_money_board;
extern Text rate_of_return_board;
extern Text profits_board;

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

 @return return 0 : 정상 티커 / 1 : 비정상 티커(종료 후 루프 재진입)
*/
int data_processing(void);

/**
 @brief 가격 변동이 더욱 명확하게 보일 수 있도록 가격을 조정한다.

 차트에 가격 변동이 명확히 보이도록 구조체 \ref Data 에 각 정보 할당

 @return 리턴 값 없음
*/
void data_coef(void);

/**
 @brief 코인 가격, 시드, 포지션 정보를 담고있는 문자열 생성 

 화면에 표시할 포지션 진입 후 남은 시드, 입력한 티커에 해당하는 코인의 현재 가격, 매수가, 청산가, 수익률, 수익금의 정보를 추출 및 가공

 추출 및 가공한 정보를 Text 타입 구조체에 각각 할당 

 @return 리턴 값 없음
*/
void GetBoardInfo(void);



#endif