/**
 @file      input.h
 @brief     마우스 입력 발생 시 처리하는 함수 선언
 @author    이태겸

 */
#ifndef INPUT_H
#define INPUT_H

#include "init.h"
#include "defs.h"
#include "get_info.h"

/* main.h에 정의된 전역 변수 사용 */
extern App app;
extern Data data;
extern Entity layout;
extern int mouse_x, mouse_y, i;
extern char ticker[10];
extern char url[BUFF_SIZE];
extern double max_min_percent;

/**
 @brief 외부 입력을 받아 적절한 동작을 취하도록 한다.

 1. 창닫기 버튼을 누르면 프로그램 종료
 2. 마우스 이벤트 발생 시 좌표를 받고 클릭한 범위에 대해 처리
 3. 마우스 휠을 드래그 할 시 차트 확대 / 축소 실행

 @return 리턴 값 없음
*/
void GetInput(void);

#endif