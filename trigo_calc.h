#ifndef TRIGO_CALC_H
#define TRIGO_CALC_H

int sin_calc(double x, double eps, double *result);

int cos_calc(double x, double eps, double *result);


int row_calc(double phi_min, double phi_max, double phi_step, int type, int eps);

#endif // TRIGO_CALC_H

