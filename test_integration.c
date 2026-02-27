/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you neeed to test the integration methods and show your numericzal results */

// La fonction à intégrer
double f(double x) {
    return 4*x * pow(x,x);
}

int main()
{
    QuadFormula qf;
    qf.wk = NULL; // Initialisation vitale
    qf.xk = NULL;
    double resultat = 1601.311877;
    double res;
    double a = 1.0, b = 4.0;
    int N = 20;

    printf("tests avec a=%f, b=%f, N=%d \n\n", a, b, N);

    // 1. RECTANGLE GAUCHE
    if (setQuadFormula(&qf, "left")) {
        res = integrate(f, a, b, N, &qf);
        double erreur = fabs(res -resultat);
        printf(">> Resultat Left: %f\n", res);
        printf("erreur : %f\n\n", erreur);
    }

    // 2. RECTANGLE MILIEU
    if (setQuadFormula(&qf, "middle")) {
        res = integrate(f, a, b, N, &qf);
        double erreur = fabs(res -resultat);
        printf(">> Resultat Middle: %f\n", res);
        printf("erreur : %f\n\n", erreur);
    }

    // 3. TRAPEZES
    if (setQuadFormula(&qf, "trapezes")) {
        res = integrate(f, a, b, N, &qf);
        double erreur = fabs(res -resultat);
        printf(">> Resultat Trapezes: %f\n", res);
        printf("erreur : %f\n\n", erreur);
    }

    // 4. SIMPSON
    if (setQuadFormula(&qf, "simpson")) {
        res = integrate(f, a, b, N, &qf);
        double erreur = fabs(res -resultat);
        printf(">> Resultat Simpson: %f\n", res);
        printf("erreur : %f\n\n", erreur);

    }

    // 5. GAUSS2
    if (setQuadFormula(&qf, "gauss2")) {
        res = integrate(f, a, b, N, &qf);
        double erreur = fabs(res -resultat);
        printf(">> Resultat Gauss2: %f\n", res);
        printf("erreur : %f\n\n", erreur);
    }

        // 5. GAUSS3
    if (setQuadFormula(&qf, "gauss3")) {
        res = integrate(f, a, b, N, &qf);
        double erreur = abs(res -resultat);
        printf(">> Resultat Gauss3: %f\n", res);
        printf("erreur : %f\n\n", erreur);
    }
  
    // NETTOYAGE FINAL
    free(qf.wk);
    free(qf.xk);
    
    return 0;
}
