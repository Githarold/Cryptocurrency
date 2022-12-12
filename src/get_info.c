/**
 @file      get_info.c
 @brief     url 생성 및 데이터 수신 함수를 정의한 소스 파일
 @author    이승헌
 */
#include "get_info.h"

void make_url(void) {
    // ticker, url 초기화
    strcpy(url, URL);
    strcpy(ticker, "");

    printf("What's ticker? : ");
    scanf(" %s", ticker);

    strncat(url, ticker, strlen(ticker));
    strncat(url, URL_OPTION, strlen(URL_OPTION));
    strncat(ticker, JSON, strlen(JSON));

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
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // 열었던 파일을 fclose() 함수를 통해 닫아준다.
    fclose(fp);

    return;
}

void data_processing(void) {
    // 결과로 저장된 json파일을 파싱할 수 있도록 json_object 구조체의 객체들을 만든다.
    json_object *chart_data = json_object_from_file(ticker);
    json_object *data, *trade_price, *opening_price, *high_price, *low_price, *candle_acc_trade_volume, *candle_date_time_kst;

    // 각 key값에 맞는 값들을 받아오는 데이터 파싱을 진행한다.
    data = json_object_array_get_idx(chart_data, 0);
    trade_price = json_object_object_get(data, "trade_price");
    opening_price = json_object_object_get(data, "opening_price");
    high_price = json_object_object_get(data, "high_price");
    low_price = json_object_object_get(data, "low_price");
    candle_acc_trade_volume = json_object_object_get(data, "candle_acc_trade_volume");
    candle_date_time_kst = json_object_object_get(data, "candle_date_time_kst");
    // coin_data.candle_date_time_kst = candle_date_time_kst;

    // coin_data 구조체의 멤버들을 실시간 값으로 초기화 + 실수형 데이터 타입으로 변환해준다.
    coin_data.trade_price = atof(json_object_get_string(trade_price));
    coin_data.opening_price = atof(json_object_get_string(opening_price));
    coin_data.high_price = atof(json_object_get_string(high_price));
    coin_data.low_price = atof(json_object_get_string(low_price));
    coin_data.candle_acc_trade_volume = atof(json_object_get_string(candle_acc_trade_volume));
    // coin_data.candle_date_time_kst[19] = *json_object_get_string(candle_date_time_kst); 
    strcpy(coin_data.candle_date_time_kst, json_object_get_string(candle_date_time_kst));

    return;
}

void data_coef(void) {
    // if(coin_data.candle_date_time_kst_check == NULL)
    if(check == 0)
    {
        strcpy(coin_data.candle_date_time_kst_check, coin_data.candle_date_time_kst);
        printf("Let");
        check++;
        
    }
    if(check == 1)
    {
        coin_data.pro_opening_price = coin_data.trade_price;
        printf("'s");
        check++;
    }
    if(check == 2)
    {
        coin_data.candle_acc_trade_volume_high = coin_data.candle_acc_trade_volume;

        printf(" go!\n");
        coef_chart = (SCREEN_HEIGHT - CHART_HEIGHT)/coin_data.candle_acc_trade_volume_high;
        coef_chart_before = coef_chart;
        check++;
    }
    if(coin_data.candle_acc_trade_volume_high <= coin_data.candle_acc_trade_volume)
    {
        coin_data.candle_acc_trade_volume_high = coin_data.candle_acc_trade_volume;
        coef_chart_before = coef_chart;
        coef_chart = (SCREEN_HEIGHT - CHART_HEIGHT)/coin_data.candle_acc_trade_volume_high;
    }

    // 가격 차트의 변동을 명확하게 보여주기 위해 변환을 실행한다.
    // coin_data.low_coef = (coin_data.low_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;
    // coin_data.high_coef = (coin_data.high_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;
    // coin_data.trade_coef = (coin_data.trade_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;
    // coin_data.opening_coef = (coin_data.opening_price-0.97*coin_data.pro_opening_price)*CHART_HEIGHT*((double)100/6)/coin_data.pro_opening_price;

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
    sprintf(left_money_board.value_text, "%.0lf", left_money);
    strcat(left_money_board.value_text, "  KRW");
    left_money_board.surface =
        TTF_RenderText_Solid(app.font, left_money_board.value_text, left_money_board.color);
    left_money_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, left_money_board.surface);

    sprintf(coin_price_board.value_text, "%.1lf", coin_data.trade_price);
    strcat(coin_price_board.value_text, "  KRW");
    coin_price_board.surface =
        TTF_RenderText_Solid(app.font, coin_price_board.value_text, coin_price_board.color);
    coin_price_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, coin_price_board.surface);

    sprintf(buy_price_board.value_text, "%.1lf", buy_price);
    buy_price_board.surface =
        TTF_RenderText_Solid(app.font, buy_price_board.value_text, buy_price_board.color);
    buy_price_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, buy_price_board.surface);

    sprintf(liquidation_money_board.value_text, "%.1lf", liquidation_price);
    liquidation_money_board.surface =
        TTF_RenderText_Solid(app.font, liquidation_money_board.value_text, liquidation_money_board.color);
    liquidation_money_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, liquidation_money_board.surface);

    sprintf(rate_of_return_board.value_text, "%.4lf", rate_of_return);
    strcat(rate_of_return_board.value_text, " %");     // 이거 warning뜨는거 무시하셈 %%하면 %%둘다붙어서 나옴
    rate_of_return_board.surface =
        TTF_RenderText_Solid(app.font, rate_of_return_board.value_text, rate_of_return_board.color);
    rate_of_return_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, rate_of_return_board.surface);
    
    sprintf(profits_board.value_text, "%.1lf", profits);
    if((int)profits == 0)
    {
        strcat(profits_board.value_text, "          ");
    }
    profits_board.surface =
        TTF_RenderText_Solid(app.font, profits_board.value_text, profits_board.color);
    profits_board.texture =
        SDL_CreateTextureFromSurface(app.renderer, profits_board.surface);
        // buy_money_board.pos

    return;
}
