/**
 @file      input.h
 @brief     마우스 입력 발생 시 처리하는 함수 선언
 @author    이태겸

 */
#ifndef INPUT_H
#define INPUT_H

#include "init.h"
#include "defs.h"

/* main.h에 정의된 전역 변수 사용 */
extern App app;
extern Data data;
extern int mouse_x, mouse_y;

/**
 @brief 외부 입력을 받아 적절한 동작을 취하도록 한다.

 1. 창닫기 버튼을 누르면 프로그램 종료

 @return 리턴 값 없음
*/
void GetInput(void);

#endif