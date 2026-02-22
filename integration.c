#define INTEGRATION_C

#include "integration.h"

#include <string.h>
#include <math.h>

bool setQuadFormula(QuadFormula* qf, char* name)
{
    int longueur = strlen(name);

    // ----- rectangle gauche -----
    if (strcmp(name, "left") == 0) {
        // On enregistre le nom de la méthode choisie dans la structure
        strcpy(qf->name, name); 

        // On définit le n de la structure
        qf->n = 0;
        
        // Allocations en utilisant qf->n
        qf->wk = malloc((qf->n + 1) * sizeof(double));
        qf->xk = malloc((qf->n + 1) * sizeof(double));

        if(qf->wk == NULL || qf->xk == NULL) {
            return false;
        }

        // On remplit les cases
        qf->wk[0] = 1.;
        qf->xk[0] = 0.;
    
        return true;
    }

    // ----- rectangle droit -----
    else if (strcmp(name, "right") == 0) { 
        // On enregistre le nom de la méthode choisie dans la structure
        strcpy(qf->name, name); 
        
        // On définit le n de la structure
        qf->n = 0;
        
        // Allocations en utilisant qf->n
        qf->wk = malloc((qf->n + 1) * sizeof(double));
        qf->xk = malloc((qf->n + 1) * sizeof(double));

        if(qf->wk == NULL || qf->xk == NULL) {
            return false;
        }

        // On remplit les cases
        qf->wk[0] = 1.;
        qf->xk[0] = 1.;

        return true;
    }

    // ----- rectangle milieu -----
    else if (strcmp(name, "middle") == 0) {
       // On enregistre le nom de la méthode choisie dans la structure
        strcpy(qf->name, name); 
        
        // On définit le n de la structure
        qf->n = 0;
        
        // Allocations en utilisant qf->n
        qf->wk = malloc((qf->n + 1) * sizeof(double));
        qf->xk = malloc((qf->n + 1) * sizeof(double));

        if(qf->wk == NULL || qf->xk == NULL) {
            return false;
        }

        // On remplit les cases
        qf->wk[0] = 1.;
        qf->xk[0] = 0.5;

        return true;
   }

   // ----- trapeze -----
    else if (strcmp(name, "trapezes") == 0) {
       // On enregistre le nom de la méthode choisie dans la structure
        strcpy(qf->name, name); 
        
        // On définit le n de la structure
        qf->n = 1;
        
        // Allocations en utilisant qf->n
        qf->wk = malloc((qf->n + 1) * sizeof(double));
        qf->xk = malloc((qf->n + 1) * sizeof(double));

        if(qf->wk == NULL || qf->xk == NULL) {
            return false;
        }

        // On remplit les cases
        qf->wk[0] = 0.5;
        qf->wk[1] = 0.5;
        qf->xk[0] = 1.;

        return true;
    }

    // ----- Simpson -----
    else if (strcmp(name,"simpson")== 0) {
       // On enregistre le nom de la méthode choisie dans la structure
        strcpy(qf->name, name); 
        
        // On définit le n de la structure
        qf->n = 2;
        
        // Allocations en utilisant qf->n
        qf->wk = malloc((qf->n + 1) * sizeof(double));
        qf->xk = malloc((qf->n + 1) * sizeof(double));

        if(qf->wk == NULL || qf->xk == NULL) {
            return false;
        }

        // On remplit les cases
        qf->wk[0] = 1. / 6.;
        qf->wk[1] = 2. / 3.;
        qf->wk[2] = 1. / 6.;
        qf->xk[0] = 0.;
        qf->xk[1] = 0.5;
        qf->xk[2] = 1.;

        return true;
    }

    // ----- Gauss à 2 noeuds -----
    else if (strcmp(name,"gauss2")== 0) {
       // On enregistre le nom de la méthode choisie dans la structure
        strcpy(qf->name, name); 
        
        // On définit le n de la structure
        qf->n = 1;
        
        // Allocations en utilisant qf->n
        qf->wk = malloc((qf->n + 1) * sizeof(double));
        qf->xk = malloc((qf->n + 1) * sizeof(double));

        if(qf->wk == NULL || qf->xk == NULL) {
            return false;
        }

        // On remplit les cases
        qf->wk[0] = 0.5;
        qf->wk[1] = 0.5;
        qf->xk[0] = 0.5 - ( 1. / (2. * sqrt(3.)) );
        qf->xk[1] = 0.5 + ( 1. / (2. * sqrt(3.)) );
        
        return true;
    }

    // ----- Gauss à 3 noeuds -----
    else if (strcmp(name,"gauss3")== 0) {
       // On enregistre le nom de la méthode choisie dans la structure
        strcpy(qf->name, name); 
        
        // On définit le n de la structure
        qf->n = 2;
        
        // Allocations en utilisant qf->n
        qf->wk = malloc((qf->n + 1) * sizeof(double));
        qf->xk = malloc((qf->n + 1) * sizeof(double));

        if(qf->wk == NULL || qf->xk == NULL) {
            return false;
        }

        // On remplit les cases
        qf->wk[0] = 5. / 18.;
        qf->wk[1] = 4. / 9.;
        qf->wk[2] = 5. / 18.;
        qf->xk[0] = 0.5 * (1. - sqrt(3. / 5.));
        qf->xk[1] = 0.5;
        qf->xk[2] = 0.5 * (1. + sqrt(3. / 5.));
    }    

    return false;
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


