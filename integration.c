#define INTEGRATION_C

#include "integration.h"

// à garder ??*
#include <string.h>

bool setQuadFormula(QuadFormula* qf, char* name)
{
    int longueur = strlen(name);

    if (strcmp(name, "left") ==0) {
        qf->test =0;
        return true;
    }
    else if (strcmp(name, "right") ==0) {
        qf->test =1;
        return true;
    }
    else if (strcmp(name, "middle") ==0) {
        qf->test =2;
        return true;
   }
    else if (strcmp(name, "trapezes") ==0) {
        qf->test =3;
        return true;
    }
    else {
        return false;
    }
}


/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{


  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
    if (qf->test == 1){
        //pass

    }

  return 0.0;
  
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  return 0.0;
}


