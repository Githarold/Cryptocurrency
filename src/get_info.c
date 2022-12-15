/**
 @file      get_info.c
 @brief     url 생성 및 데이터 수신 함수를 정의한 소스 파일
 @author    이승헌, 이태겸
 */

#include "get_info.h"

void make_url(void) {
    // ticker, url 초기화    
    strcpy(url, URL);
    strcpy(ticker, "");

    SDL_StartTextInput();
    SDL_bool done = SDL_FALSE;
    while (!done)
    {
        SDL_RenderCopy(app.renderer, search.texture, NULL, &(search.pos));
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = SDL_TRUE;
                    break;

                case SDL_TEXTINPUT:
                    strcat(ticker, event.text.text);
                    break;
            }
        }
    }
    SDL_StopTextInput();
    strcat(url, ticker);
    strcat(url, URL_OPTION);
    strcat(ticker, JSON);

    i = 0;
    check = 0;

    return;
}

void get_info(void) {
    // curl_perform의 결과로 나오는 표준 출력을 chart_data.json 파일에 저장하기 위해 fopen() 함수를 사용한다.
    FILE *fp = fopen(ticker, "w");
    if (fp == NULL) {
        printf("fopen ERR\n");
        return;
    }

    // CURL 구조체 타입의 curl 객체 생성. 생성 실패 시 에러코드 출력 후 종료한다.
    CURL *curl = curl_easy_init();
    if (!curl) {
        printf("curl ERR\n");
        return;
    }

    // 표준출력으로 나오는 curl_perform의 결과를 WRITEDATA 옵션의 easy_setopt 함수를 통해 버퍼 fp에 저장한다.
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url);  // debug(url)
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // 열었던 파일을 fclose() 함수를 통해 닫아준다.
    fclose(fp);

    return;
}

int data_processing(void) {
    // 결과로 저장된 json파일을 파싱할 수 있도록 json_object 구조체의 객체들을 만든다.
    json_object *chart_data = json_object_from_file(ticker);
    if (json_object_object_get(chart_data, "error"))
    {
        printf("[error] Invalid ticker!!!\n");
        make_url();
        return 1;
    }

    // 각 key값에 맞는 값들을 받아오는 데이터 파싱을 진행한다.
    json_object *data, *trade_price, *opening_price, *high_price, *low_price, *candle_acc_trade_volume, *candle_date_time_kst;
    data= json_object_array_get_idx(chart_data, 0);
    trade_price = json_object_object_get(data, "trade_price");
    opening_price = json_object_object_get(data, "opening_price");
    high_price = json_object_object_get(data, "high_price");
    low_price = json_object_object_get(data, "low_price");
    candle_acc_trade_volume = json_object_object_get(data, "candle_acc_trade_volume");
    candle_date_time_kst = json_object_object_get(data, "candle_date_time_kst");

    // coin_data 구조체의 멤버들을 실시간 값으로 초기화 + 실수형 데이터 타입으로 변환해준다.
    coin_data.trade_price = atof(json_object_get_string(trade_price));
    coin_data.opening_price = atof(json_object_get_string(opening_price));
    coin_data.high_price = atof(json_object_get_string(high_price));
    coin_data.low_price = atof(json_object_get_string(low_price));
    coin_data.candle_acc_trade_volume = atof(json_object_get_string(candle_acc_trade_volume));

    // coin_data 구조체의 시간정보를 담는 멤버를 실시간 값으로 초기화 + 데이터 파싱 결과(문자열)을 문자열 구조체 멤버에 카피하여 저장해준다.
    strcpy(coin_data.candle_date_time_kst, json_object_get_string(candle_date_time_kst));            

    return 0;
}

void data_coef(void) {
    // 밑에 세 개의 조건문은 프로그램 실행시 딱 한 번만 실행되어야 하므로 이 조건문 이외에 사용되지 않는 check 변수를 활용하여 구동시킨다.  
    if(check == 0)                                                                          
    {
        strcpy(coin_data.candle_date_time_kst_check, coin_data.candle_date_time_kst);       // 프로그램을 실행했을 때의 시간을 추출한다.
        printf("Let");                                                                      // 추출한 데이터는 draw_chart 소스파일의 check_time() 함수에서 사용한다.
        check++;
        
    }
    if(check == 1)
    {
        coin_data.pro_opening_price = coin_data.trade_price;                                // 프로그램을 실행했을 때의 가격을 추출한다. 
        printf("'s");                                                                       // 추출한 데이터는 line 138에서 차트 변환을 할 때 사용한다.
        check++;
    }
    if(check == 2)
    {
        coin_data.candle_acc_trade_volume_high = coin_data.candle_acc_trade_volume;         // 프로그램을 실행했을 때의 거래량을 추출하여 최고 거래량에 저장한다. 
                                                                                            // 이후에 더 큰 거래량이 나와 거래량 차트를 변환해야 할 때 사용한다.
        printf(" go!\n");                   
        coef_chart = (SCREEN_HEIGHT - CHART_HEIGHT)/coin_data.candle_acc_trade_volume_high; // 최고 거래량이 항상 168의 높이를 갖게 하도록 하는 변수 
        coef_chart_before = coef_chart;                                                     // 새로운 거래량이 나오게 되면 이전 거래량 차트를 변환해야 한다.
        check++;                                                                            // 하지만 이전 거래량 차트는 현재 새로 갱신된 coef값이 아니라 과거의 coef값을 통해 변환이 이루어졌다
    }                                                                                       // 따라서 새로운 coef값이 갱신될 때 이전의 coef값 또한 저장하고 있는다.

    if(coin_data.candle_acc_trade_volume_high <= coin_data.candle_acc_trade_volume)         // 새로운 거래량이 나왔을 때 coef값을 갱신해주고 이전 coef값을 저장 
    {
        coin_data.candle_acc_trade_volume_high = coin_data.candle_acc_trade_volume;
        coef_chart_before = coef_chart;
        coef_chart = (SCREEN_HEIGHT - CHART_HEIGHT)/coin_data.candle_acc_trade_volume_high;
    }

    // 가격 차트의 변동을 명확하게 보여주기 위해 변환을 실행한다.
    coin_data.low_coef = (coin_data.low_price-(1-max_min_percent/100)*coin_data.pro_opening_price)*CHART_HEIGHT*(50/max_min_percent)/coin_data.pro_opening_price;
    coin_data.high_coef = (coin_data.high_price-(1-max_min_percent/100)*coin_data.pro_opening_price)*CHART_HEIGHT*((50/max_min_percent))/coin_data.pro_opening_price;
    coin_data.trade_coef = (coin_data.trade_price-(1-max_min_percent/100)*coin_data.pro_opening_price)*CHART_HEIGHT*((50/max_min_percent))/coin_data.pro_opening_price;
    coin_data.opening_coef = (coin_data.opening_price-(1-max_min_percent/100)*coin_data.pro_opening_price)*CHART_HEIGHT*((50/max_min_percent))/coin_data.pro_opening_price;

    // 거래량 차트의 변동을 명확하게 보여주기 위해 변환을 실행한다.
    coin_data.candle_acc_trade_volume_coef = coin_data.candle_acc_trade_volume*coef_chart;
    
    return;
}

void GetBoardInfo(void) 
{
    // 남은 잔고 표현하는 TEXT
    sprintf(left_money_board.value_text, "%.0lf", left_money);                                  // trade 소스파일에서 계산된 left_money의 값을 해당 구조체의 문자열에 저장
    strcat(left_money_board.value_text, "  KRW");                                               // ex) 100 -> 100  원
    left_money_board.surface =
        TTF_RenderText_Solid(app.font, left_money_board.value_text, left_money_board.color);
    left_money_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, left_money_board.surface);

    // 현재 열람중인 코인의 실시간 가격을 표현하는 TEXT
    sprintf(coin_price_board.value_text, "%.1lf", coin_data.trade_price);                       // data_processing에서 가공된 현재 코인 가격 데이터를 해당 구조체의 문자열에 저장
    strcat(coin_price_board.value_text, "  KRW");
    coin_price_board.surface =
        TTF_RenderText_Solid(app.font, coin_price_board.value_text, coin_price_board.color);
    coin_price_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, coin_price_board.surface);
    
    // 진입한 포지션의 정보 중 매수가를 표현하는 TEXT
    sprintf(buy_price_board.value_text, "%.1lf", buy_price);                                    // trade 소스파일에서 계산된 buy_price의 값을 해당 구조체의 문자열에 저장
    buy_price_board.surface =
        TTF_RenderText_Solid(app.font, buy_price_board.value_text, buy_price_board.color);
    buy_price_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, buy_price_board.surface);

    // 진입한 포지션의 정보 중 청산가를 표현하는 TEXT
    sprintf(liquidation_money_board.value_text, "%.1lf", liquidation_price);                    // trade 소스파일에서 계산된 liquidation_price의 값을 해당 구조체의 문자열에 저장
    liquidation_money_board.surface =
        TTF_RenderText_Solid(app.font, liquidation_money_board.value_text, liquidation_money_board.color);
    liquidation_money_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, liquidation_money_board.surface);

    // 진입한 포지션의 정보 중 수익률을 표현하는 TEXT
    sprintf(rate_of_return_board.value_text, "%.4lf", rate_of_return);                          // trade 소스파일에서 계산된 rate_of_return의 값을 해당 구조체의 문자열에 저장
    strcat(rate_of_return_board.value_text, " %");                                              // ex) 100 -> 100 %
    rate_of_return_board.surface =
        TTF_RenderText_Solid(app.font, rate_of_return_board.value_text, rate_of_return_board.color);
    rate_of_return_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, rate_of_return_board.surface);
    
    // 진입한 포지션의 정보 중 수익금을 표현하는 TEXT
    sprintf(profits_board.value_text, "%.1lf", profits);                                        // trade 소스파일에서 계산된 profits의 값을 해당 구조체의 문자열에 저장

    if((int)profits == 0)                                                                       // profits을 표현할 칸이 글씨체 크기 22로 표현하기에 너무 작기 때문에 width와 height를 조정하여 글씨 크기를 바꿔주었음
    {                                                                                           // 기본 잔고가 백만원으로 주어지기 때문에 수익금은 기본적으로 만원 단위가 넘어감
        strcat(profits_board.value_text, "          ");                                         // 이를 생각해서 width를 조정하면 수익금이 0원일때 글씨가 어색하게 출력되는 문제가 있음
    }                                                                                           // 수익금이 0원일 때 뒤에 공백 문자를 붙여 문제 해결 
                                                                                                
    profits_board.surface =
        TTF_RenderText_Solid(app.font, profits_board.value_text, profits_board.color);
    profits_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, profits_board.surface);

    return;
}
