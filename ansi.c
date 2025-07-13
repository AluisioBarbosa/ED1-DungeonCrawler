#include "ansi.h"
#include <stdio.h>

void moveCursorPara(int y, int x) {
    printf("\033[%d;%dH", y + 1, (x * 2) + 1); 
}