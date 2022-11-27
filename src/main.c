#include "main.h"

char URL[BUFF_SIZE] = "https://api.bithumb.com/public/ticker/";

void call_info(char *a) {
    

    FILE *fp = popen("./get_info", "r");

    if (fp == NULL) {
        perror("popen() 실패");
        exit(1);
    }

    fgets(a, BUFF_SIZE, fp);
 
    pclose(fp);
}

int main(void) {
    char ticker[10] = "";
    char info[BUFF_SIZE] = {0};
    char *price = malloc(BUFF_SIZE);
    char *status = malloc(5);
    
    printf("What's ticker? : ");
    fgets(ticker, 10, stdin);
    strcat(URL, ticker);
    printf("%s", URL);

    call_info(info);
    strncpy(status, info + 11, 4);

    if (!strncmp(status, "5500", 4)) {
        printf("상장 코인이 아닙니다.\n");
        exit(1);
    }

    while (1) {
        call_info(info);
        price = strtok(info, "\"");

        for(int i = 0 ; i < 13 ; i++)
        {
            price = strtok(NULL, "\"");
            
        }

        printf("%s\n", price);
    }
    
    free(price);
    free(status);

    return 0;
}