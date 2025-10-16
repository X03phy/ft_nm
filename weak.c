// file: weak.c
__attribute__((weak)) void foo(void);

int main(void)
{
    foo(); // appelée, mais non définie
    return 0;
}