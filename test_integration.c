/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods and show your numericzal results */

// La fonction à intégrer
double f(double x) {
    return x * x;
}

int main()
{
    QuadFormula qf;
    qf.wk = NULL; // Initialisation vitale
    qf.xk = NULL;

    double res;
    double a = -1.0, b = 4.0;
    int N = 10;

    printf("=== DEBUT DE LA SUITE DE TESTS (a=%f, b=%f, N=%d) ===\n\n", a, b, N);

    // 1. RECTANGLE GAUCHE
    if (setQuadFormula(&qf, "left")) {
        printQuadFormula(&qf);
        res = integrate(f, a, b, N, &qf);
        printf(">> Resultat Left: %f\n\n", res);
    }

    // 2. RECTANGLE MILIEU
    if (setQuadFormula(&qf, "middle")) {
        printQuadFormula(&qf);
        res = integrate(f, a, b, N, &qf);
        printf(">> Resultat Middle: %f\n\n", res);
    }

    // 3. TRAPEZES
    if (setQuadFormula(&qf, "trapezes")) {
        printQuadFormula(&qf);
        res = integrate(f, a, b, N, &qf);
        printf(">> Resultat Trapezes: %f\n\n", res);
    }

    // 4. SIMPSON
    if (setQuadFormula(&qf, "simpson")) {
        printQuadFormula(&qf);
        res = integrate(f, a, b, N, &qf);
        printf(">> Resultat Simpson: %f\n\n", res);
    }

    // 5. GAUSS2
    if (setQuadFormula(&qf, "gauss2")) {
        printQuadFormula(&qf);
        res = integrate(f, a, b, N, &qf);
        printf(">> Resultat Gauss: %f\n\n", res);
    }

        // 5. GAUSS3
    if (setQuadFormula(&qf, "gauss3")) {
        printQuadFormula(&qf);
        res = integrate(f, a, b, N, &qf);
        printf(">> Resultat Gauss: %f\n\n", res);
    }
  
    // NETTOYAGE FINAL
    free(qf.wk);
    free(qf.xk);
    
    return 0;
}
