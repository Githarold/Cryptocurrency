#include "get_info.h"

void make_url(char *url) {
    char ticker[10] = "";

    printf("What's ticker? : ");
    fgets(ticker, 10, stdin);
    strcat(url, ticker);

    return;
}

void get_info(const char* url) {
    FILE *fp = fopen("result.json", "w");
    //fp = fopen("result.json", "w");

    if (fp == NULL) {
        printf("fopen ERR\n");
        exit(1);
    }

    CURL *curl = curl_easy_init();

    if (!curl) {
        printf("curl ERR\n");
        exit(1);
    }

    printf("url : %s", url);
    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);      // 표준출력으로 나오는 curl의 결과를 파일로 바꿉니다
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    fclose(fp);

    json_object *result = json_object_from_file("result.json");    

    //json_object *result_obj = json_tokener_parse(result);

    // char *buff = "{\"status\":\"0000\",\"data\":{\"opening_price\":\"22390000\",\"closing_price\":\"22349000\",\"min_price\":\"22346000\",\"max_price\":\"22414000\",\"units_traded\":\"53.72523138\",\"acc_trade_value\":\"1202107981.1507\",\"prev_closing_price\":\"22390000\",\"units_traded_24H\":\"4376.45251621\",\"acc_trade_value_24H\":\"98706032672.7421\",\"fluctate_24H\":\"-340000\",\"fluctate_rate_24H\":\"-1.5\",\"date\":\"1669648961894\"}}";
    // json_object *result = json_tokener_parse(buff);

    json_object *status, *data, *price, *fluctuate_rate;
    status = json_object_object_get(result, "status");
    // if (!strncmp(status, "5500", 4)) {
    //     printf("상장 코인이 아닙니다.\n");
    //     exit(1);
    // }

    data = json_object_object_get(result, "data");
    price = json_object_object_get(data, "closing_price");
    fluctuate_rate = json_object_object_get(data, "fluctate_rate_24H");
    printf("price : %s 원\n", json_object_get_string(price));
    printf("변동률 : %s %%\n", json_object_get_string(fluctuate_rate));

    return;
}
