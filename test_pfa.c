/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */

int main()
{
    // 1. Initialisation du moteur d'intégration
    // On utilise la méthode de Simpson avec un pas de 0.01 pour une bonne précision
    if (!init_integration("gauss3", 2.0)) {
        printf("Erreur : Impossible d'initialiser l'intégration.\n");
        return 1;
    }

    printf("--- TEST FINANCE (Black-Scholes) ---\n");
    // Configuration d'une option standard
    Option opt;
    opt.S0  = 100.0;  // Prix actuel de l'action
    opt.K   = 100.0;  // Prix d'exercice (Strike)
    opt.T   = 1.0;    // Échéance dans 1 an
    opt.mu  = 0.05;   // Taux d'intérêt (5%)
    opt.sig = 0.2;    // Volatilité (20%)
    
    opt.type = CALL;
    printf("Prix du CALL : %.4f (Attendu: ~10.45)\n", optionPrice(&opt));
    
    opt.type = PUT;
    printf("Prix du PUT  : %.4f\n\n", optionPrice(&opt));


    printf("--- TEST ASSURANCE (Loi Log-Normale) ---\n");
    // Configuration d'un client assuré
    double probas_sinistres[3] = {0.1, 0.7, 0.2}; // 10% de chance d'avoir 0 accident, 70% pour 1, 20% pour 2
    
    InsuredClient client;
    client.m = 7.0;  // Paramètre m de la loi log-normale
    client.s = 0.5;  // Paramètre s (écart-type log)
    client.p = probas_sinistres; //

    double x_test = 2000.0;
    printf("Pour un seuil de x = %.2f euros :\n", x_test);
    printf(" - Probabilité d'un sinistre unique < x : %.4f\n", clientCDF_X(&client, x_test));
    printf(" - Probabilité de deux sinistres (somme) < x : %.4f\n", clientCDF_X1X2(&client, x_test));
    printf(" - Risque annuel total (S < x) : %.4f\n", clientCDF_S(&client, x_test));

    return 0;
}
