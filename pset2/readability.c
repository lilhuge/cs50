#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int letters = 0;    
int words = 1;     
int sentences = 0;
string text;

void count(int n);
void result(int index);

int main(void)
{
    letters = 0;    //Set counter variables to zero
    words = 1;      // Word count starts at 1
    sentences = 0;
    text = get_string("Text: ");     // Request user input for text

    int n = strlen(text);                   // Gets stringlength
    
    count(n);
    
    float L = ((float)letters / (float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);   // Apply formula

    result(index);
}




void count(n)
{
    for (int i = 0; i < n; i++)
    {
    
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            letters ++;         // Counts letters
        }
    
        if (text[i] == 32)
        {
            words ++;           // Counts words
        }
    
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences ++;       // Counts sentences
        }

    }
}


void result(index)
{
    if (index < 1)                      // Print results
    {
        printf("Before Grade 1\n");
    }

    else if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }

    else
    {
        printf("Grade 16+\n");
    }
    
}