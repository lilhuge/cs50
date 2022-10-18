#include <stdio.h>
#include <math.h>

int main(void)
{
    int x = 27;
    int y = 28;
    int z = 28;
    
    float average = (float)(x + y + z) / 3;
    
    printf("%f \n", average);
    
    int rounded = round(average);
    
    printf("%i \n",rounded);
}
