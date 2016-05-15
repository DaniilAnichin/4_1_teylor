#include <stdio.h>
#include <math.h>
#include "trigo_calc.h"
#include "input_check.h"

void program_run();

int main(void)
{
    char cycle = 'y';

    do
    {
        if(cycle != 'y')
            printf("Unknown value: %c; repeat the choice\n", cycle);
        else
            program_run();
        printf("Do you want to continue?['y' to continue, 'n' to abort, and enter]\n");
        cycle = getchar();
        while(getchar() != '\n');
    }while(cycle != 'n');

    return 0;
}

void program_run()
{
    double x_min = 0, x_max = 0, x_step = 0;
    int errors = 0, type = 0, eps = 14;

    printf("Input the starting angle:\n");
    x_min = double_input(-9999, 9999);

    printf("Input the ending angle:\n");
    x_max = double_input(-9999, 9999);

    printf("Input the angle increment(abs more than 10^-5):\n");
    x_step = double_input(-999, 999);

    printf("Input '0' to caclulate sine, '1' - to cosine:\n");
    type = integer_input(0, 1);

    printf("Input the number of the digis of the precise:\n");
    eps = integer_input(0, 13);

//    test values:
//    errors += row_calc(0, 360, 1, 0, eps_2); //
//    errors += row_calc(90, 5, -10, 0, eps); //error
//    errors += row_calc(90, 0, 10, 0, eps); //
//    errors += row_calc(0, 90, -10, 0, eps); //error
//    errors += row_calc(90, 0, 0, 0, eps); //error
//    errors += row_calc(90, 95, 10, 0, 2); //
//    errors += row_calc(90, 90, 10, 0, 2); //
//    errors += row_calc(0, -3, -0.1, 0, eps); //
//    errors += row_calc(0, 1e-6, 0.1, 0, eps); // error
    errors += row_calc(x_min, x_max, x_step, type, eps);
}
