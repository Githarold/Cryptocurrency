#define BUFSIZE 1024
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

char URL[BUFSIZE] = "https://api.bithumb.com/public/ticker/btc";

int main(void) {
    FILE *fp;
    fp = fopen("result.json", "w");

    if (fp == NULL) {
        printf("fopen ERR\n");
        return 1;
    }

    CURL *curl = curl_easy_init();

    if (!curl) {
        printf("curl ERR\n");
        return 1;
    }

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, URL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); // <- 이걸 지정해서 표준출력으로 나오는 curl의 결과를 파일로 바꿉니다
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    fclose(fp);

    //######################################################## 
    json_object *result = json_object_from_file("result.json");    

    //json_object *result_obj = json_tokener_parse(result);

    // char *buff = "{\"status\":\"0000\",\"data\":{\"opening_price\":\"22390000\",\"closing_price\":\"22349000\",\"min_price\":\"22346000\",\"max_price\":\"22414000\",\"units_traded\":\"53.72523138\",\"acc_trade_value\":\"1202107981.1507\",\"prev_closing_price\":\"22390000\",\"units_traded_24H\":\"4376.45251621\",\"acc_trade_value_24H\":\"98706032672.7421\",\"fluctate_24H\":\"-340000\",\"fluctate_rate_24H\":\"-1.5\",\"date\":\"1669648961894\"}}";
    // json_object *result = json_tokener_parse(buff);

    json_object *data, *price, *fluctuate_rate;
    data = json_object_object_get(result, "data");

    price = json_object_object_get(data, "closing_price");
    fluctuate_rate = json_object_object_get(data, "fluctate_rate_24H");
    printf("price : %s 원\n", json_object_get_string(price));
    printf("변동률 : %s %%\n", json_object_get_string(fluctuate_rate));
    return 0;
}