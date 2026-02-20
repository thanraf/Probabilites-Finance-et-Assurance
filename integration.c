#define INTEGRATION_C

#include "integration.h"

// à garder ??*
#include <string.h>

bool setQuadFormula(QuadFormula* qf, char* name)
{
    int longueur = strlen(name);

    if (strcmp(name, "left") == 0) { // rectangle gauche
        qf->methode =1;
        n = 0;
        wk = 1;
        xk = 0;
        return true;
    }
    else if (strcmp(name, "right") == 0) { // rectangle droit
        qf->methode =2;
        return true;
    }
    else if (strcmp(name, "middle") == 0) { // rectangle milieu
        qf->methode =3;
        n = 0;
        wk = 1;
        xk = 1/2;
        return true;
   }
    else if (strcmp(name, "trapezes") == 0) { // trapeze
        qf->methode =4;
        n = 1;
        *(w+k + 1)  = 1/2;
        xk = 0;
        return true;
    }
    else if (strcmp(name,"simpson")== 0) { // simpson
        qf->methode = 5;
        n = 0;
        wk = 1;
        xk = 0;
        return true;
    }
    else if (strcmp(name,"gauss2")== 0) { // gauss 2 points
        qf->methode = 6;
        n = 0;
        wk = 1;
        xk = 0;
        return true;
    }
    else if (strcmp(name,"gauss3")== 0) { // gauss 3 points
        qf->methode = 7;
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
    double a_i = a;
    double b_i =0;
    int i = 0;
    double I = 0;

    while (i < N) {
        
        a_i = a + i * (b - a) / N;
        b_i = a + (i + 1) * (b - a) / N;
        
        if (qf->methode == 1) {
            I += f(a_i) * (b_i - a_i);
        }

        if (qf-> methode == 2) {
            I += f(b_i) * (b_i - a_i); 
        }
        
        if (qf-> methode == 3) {
            I +=  f((a_i + b_i) / 2) * (b_i - a_i);
        }

        if (qf->methode == 4) {
            I +=  (1/2* f(a_i) + 1/2*f(b_i)) * (b_i - a_i); 
        }

        if (qf->methode == 5) {
            I += (b_i -a_i) *(1/6 *f(a_i) +2/3*f((a_i + b_i)/2) + 1/6 *f(b_i));  
        }
        
        if (qf->methode == 6) {
            for 


            
         i++; 
    }

    return I;
  
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf){
  return 0.0;
}


