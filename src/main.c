#include "main.h"

int main(void) {
    char url[BUFF_SIZE] = URL;
    make_url(url);

    while (1) {
        get_info(url);

    }

    return 0;
}