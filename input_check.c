#include <stdio.h>
#include <math.h>

int integer_input(char* direction, int lower, int upper)
{
    /* Function to check if inputed number is an integer between
     * lower and upper */
    double recieved;
    short errors;

    // Simple check for inputing values
    do
    {
        errors = 0;
        recieved = 1;
        printf("%s", direction);
        printf("(May be an integer number between %d and %d)\n", lower, upper);
        if(!scanf("%lf", &recieved) || getchar() != '\n')
        {
            printf("\tYou have entered not a numeric value!(string, maybe)\n");
            while(getchar() != '\n'){;}
            errors = 1;
        }
        if((int)recieved != recieved)
        {
            printf("\tYou have entered not an integer number!\n");
            errors = 1;
        }
        if(recieved > upper)
        {
            printf("\tThis number is too high(less than %d required)\n", upper + 1);
            errors = 1;
        }
        if(recieved < lower)
        {
            printf("\tThis number is too small(more than %d required)\n", lower - 1);
            errors = 1;
        }
    }
    while(errors);
    return (int)recieved;
}


double double_input(char* direction, double lower, double upper)
{
    /* Function to check if inputed number is an float(double, actually)
     * between lower and upper */
    double recieved = 0;
    short errors = 0;

    // Simple check for inputing values
    do
    {
        errors = 0;
        recieved = 1;
        printf("%s", direction);
        printf("(May be a float number between %.6g and %.6g)\n", lower, upper);
        if(!scanf("%lf", &recieved) || getchar() != '\n')
        {
            printf("\tYou have entered not a numeric value!(string, maybe)\n");
            while(getchar() != '\n'){;}
            errors = 1;
        }
        if(recieved >= upper)
        {
            printf("\tThis number is too high(less than %.6g required)\n", upper);
            errors = 1;
        }
        if(recieved <= lower)
        {
            printf("\tThis number is too small(more than %.6g required)\n", lower);
            errors = 1;
        }
    }
    while(errors);
    return recieved;
}
