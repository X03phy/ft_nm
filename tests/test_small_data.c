// test_small_data.c
int global_var = 42;           // → .data (trop grand si on met -G4)
short small_global = 10;       // → .sdata (2 bytes)
char tiny = 'a';               // → .sdata (1 byte)

int big_array[100];            // → .bss (trop grand)
static short small_static;     // → .sbss (2 bytes)

int main(void)
{
    static char local_small = 5;  // → .sdata
    return small_global + tiny;
}