#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


//
int sin_calc(double x, double eps, double *result)
{
    if(x < 0)
    {
        while(x < -180) x += 360;
    }
    else
    {
        while(x > 180) x -= 360;
    }
    x *= M_PI / 180.0;
    double sigma = x;
    int n = 1;
    *result = x;
    do
    {
        sigma *= -x * x / (2 * n * (2 * n + 1));
        n++;
        *result += sigma;
    }while(fabsl(sigma) >= eps);
    return 0;
}

//
int cos_calc(double x, double eps, double *result)
{
    if(x < 0)
    {
        while(x < -180) x += 360;
    }
    else
    {
        while(x > 180) x -= 360;
    }
    x *= M_PI / 180.0;
    double sigma = 1;
    int n = 1;
    *result = 1;
    do
    {
        sigma *= -x * x / (2 * n * (2 * n - 1));
        n++;
        *result += sigma;
    }while(fabsl(sigma) >= eps);
    return 0;
}


int row_calc(double phi_min, double phi_max, double phi_step, int type, int eps)
{
    double teylor_res = 0, trig_res = 0;
    double phi = 0, phi_rad = 0;
    double calc_eps = pow(10, -eps);

    int errors = 0;

    int i = 0;
    int this_line = 1;
    const int screen_len = 50;
    char *separ = " | ";
    char *char_sep;
    char *doub_sep;

    // Pretty formating
    eps = eps > 6 ? eps : 7;
    char_sep = (char*)calloc((sizeof(*separ) + sizeof("%*s"))/ sizeof(char), sizeof(char));
    doub_sep = (char*)calloc((sizeof(*separ) + sizeof("%*.*lf"))/ sizeof(char), sizeof(char));
    strcpy(char_sep, "%*s");
    strcpy(doub_sep, "%*.*lf");
    strcat(char_sep, separ);
    strcat(doub_sep, separ);


    double (*trig_foo) (double);  // C function
    int (*teylor_foo) (double, double, double*);  // Own function

    teylor_foo = type ? &cos_calc : &sin_calc;
    trig_foo = type ? &cos : &sin;

    // 0 step
    if(fabsl(phi_step) < 1e-5)
    {
        printf("\tSorry, this step is too small..\n");
        return 1;
    }

    // Wrong interval direction
    if((phi_max - phi_min) * phi_step < 0)
    {
        printf("\tYou entered incorrect interval\n");
        return 1;
    }

    // Too small values
    if((fabsl(phi_min) < 1e-5 && phi_min != 0) || (fabsl(phi_max) < 1e-5 && phi_max != 0))
    {
        printf("\tYou entered too small valuesf for angles\n");
        return 1;
    }
    printf(char_sep, eps / 2 + 6, "Angle");
    printf(char_sep, eps + 5, "Teylor res");
    printf(char_sep, eps + 5, "C result");
    printf("%*s\n", eps + 8, "Difference");

//    for(phi = phi_min; fabsl(phi_max - phi) >= fabsl(phi_step); phi += phi_step)
    for(i = 0; i < fabsl((phi_max - phi_min) / phi_step); i++)
    {
        phi = phi_min + i * phi_step;
        phi_rad = phi * M_PI / 180.0;

        errors += teylor_foo(phi, calc_eps, &teylor_res);
        trig_res = trig_foo(phi_rad);

        // for output:
        printf(doub_sep, eps / 2 + 6, eps / 2, phi);
        printf(doub_sep, eps + 5, eps + 2, teylor_res);
        printf(doub_sep, eps + 5, eps + 2, trig_res);
        printf("%*.*lf\n", eps + 8, eps + 5, trig_res - teylor_res);

        if(!(this_line++%screen_len))
        {
            printf("\t\tPress any key to continue;\n");
            getchar();
        }
    }

    // The last element output:
    if(phi != phi_max)
    {
        phi = phi_max;

        phi_rad = phi * M_PI / 180.0;

        errors += teylor_foo(phi, calc_eps, &teylor_res);
        trig_res = trig_foo(phi_rad);

        // for output:
        printf(doub_sep, eps / 2 + 6, eps / 2, phi);
        printf(doub_sep, eps + 5, eps + 2, teylor_res);
        printf(doub_sep, eps + 5, eps + 2, trig_res);
        printf("%*.*lf\n", eps + 8, eps + 5, trig_res - teylor_res);
    }
    printf("\n");

    return errors;
}
