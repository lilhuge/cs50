#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(void)
{

    char *f = "Hello World";      // Opens the file specified in function argument
    printf("%p\n", f);
    
    char *q = f + 5;
    printf("%p\n", q);
    
    
}