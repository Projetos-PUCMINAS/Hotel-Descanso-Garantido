#include "util.h"
#include <stdio.h>

void limpar_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
