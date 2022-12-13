/**
 @file      input.h
 @brief     마우스 입력 발생 시 처리하는 함수 선언
 @author    이승헌, 이태겸
 */

#ifndef INPUT_H
#define INPUT_H

#include "init.h"
#include "defs.h"
#include "trade.h"
#include "get_info.h"

/* input.c에서 사용할 변수 정의 */
short trade_rate_on_flag;               // 투자비율 선택이 되었는지 확인하기 위한 플래그
int leverage_on_flag;                   // 배율 선택이 되었는지 확인하기 위한 플래그

/* main.h에 정의된 전역 변수 사용 */
extern App app;
extern Data data;
extern Entity layout;
extern char ticker[50];
extern char url[BUFF_SIZE];
extern short in_position_flag;
extern short short_long_flag;
extern int mouse_x, mouse_y, i;
extern int leverage;
extern float trade_rate;
extern double max_min_percent;

extern Text coin_price_board;
extern Text left_money_board;
extern Text buy_price_board;
extern Text liquidation_money_board;
extern Text rate_of_return_board;
extern Text profits_board;


/**
 @brief 외부 입력을 받아 적절한 동작을 취하도록 한다.

 1. 창닫기 버튼을 누르면 프로그램 종료
 2. 마우스 이벤트 발생 시 좌표를 받고 클릭한 범위에 대해 처리

 @return 리턴 값 없음
*/
void GetInput(void);

#endif