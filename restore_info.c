#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1024

//extern char URL[50];

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
    char URL[50] = "https://api.bithumb.com/public/ticker/";
    char ticker[10] = "";
    char info[BUFF_SIZE] = {0};
    char *price = malloc(BUFF_SIZE);
    char *status = malloc(5);
    
    printf("What's ticker? : ");
    scanf(" %s", ticker);
    strcat(ticker, "_KRW");
    strcat(URL, ticker);

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