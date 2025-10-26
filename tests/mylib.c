#include <stdio.h>

int global_func(int x) {
    return x * 2;
}

static int internal_func(void) {
    return 42;
}

int exported_var = 100;
static int internal_var = 50;

void print_hello(void) {
    printf("Hello from shared library!\n");
}
