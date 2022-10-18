#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n");   //Asks user for name input
    printf("hello, %s\n", name);                        //Prints user name
}