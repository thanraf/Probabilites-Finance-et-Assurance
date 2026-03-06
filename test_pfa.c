/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */


int main() {
    // Initialisation avec Gauss3 et un pas fin pour coller au benchmark
    init_integration("gauss3", 0.01);

    printf("======================================================================\n");
    printf("                  Tests de la fonction optionPrice\n");
    printf("======================================================================\n");

    // --- TABLEAU 1 : CALL vs K ---
    printf("\n1. Prix Call vs K (S0=100, T=2, mu=0.05, sigma=0.02)\n");
    printf("%-10s | %-15s | %-15s\n", "K (Euro)", "Calcule", "Attendu");
    printf("-----------|-----------------|-----------------\n");
    double k1[] = {99, 100, 101, 102, 103};
    double a1[] = {11.5171, 10.5172, 9.51768, 8.51912, 7.52332};
    for(int i=0; i<5; i++) {
        Option o = {CALL, 100.0, k1[i], 2.0, 0.05, 0.02}; // Correction de l'ordre
        printf("%-10.0f | %-15.5f | %-15.5f\n", k1[i], optionPrice(&o), a1[i]);
    }

    // --- TABLEAU 2 : CALL vs T ---
    printf("\n2. Prix Call vs T (S0=100, K=101, mu=0.05, sigma=0.02)\n");
    printf("%-10s | %-15s | %-15s\n", "T (ans)", "Calcule", "Attendu");
    printf("-----------|-----------------|-----------------\n");
    double t2[] = {1.8, 1.9, 2.0, 2.1, 2.2};
    double a2[] = {8.41857, 8.9667, 9.51768, 10.0715, 10.6281};
    for(int i=0; i<5; i++) {
        Option o = {CALL, 100.0, 101.0, t2[i], 0.05, 0.02};
        printf("%-10.1f | %-15.5f | %-15.5f\n", t2[i], optionPrice(&o), a2[i]);
    }

    // --- TABLEAU 3 : PUT vs K ---
    printf("\n3. Prix Put vs K (S0=100, T=2, mu=0.05, sigma=0.02)\n");
    printf("%-10s | %-15s | %-15s\n", "K (Euro)", "Calcule", "Attendu");
    printf("-----------|-----------------|-----------------\n");
    double k3[] = {113, 114, 115, 116, 117};
    double a3[] = {2.87264, 3.70203, 4.59834, 5.53979, 6.50911};
    for(int i=0; i<5; i++) {
        Option o = {PUT, 100.0, k3[i], 2.0, 0.05, 0.02};
        printf("%-10.0f | %-15.5f | %-15.5f\n", k3[i], optionPrice(&o), a3[i]);
    }

    // --- TABLEAU 4 : PUT vs T ---
    printf("\n4. Prix Put vs T (S0=100, K=115, mu=0.05, sigma=0.02)\n");
    printf("%-10s | %-15s | %-15s\n", "T (ans)", "Calcule", "Attendu");
    printf("-----------|-----------------|-----------------\n");
    double t4[] = {1.8, 1.9, 2.0, 2.1, 2.2};
    double a4[] = {5.61998, 5.10223, 4.59834, 4.11292, 3.65046};
    for(int i=0; i<5; i++) {
        Option o = {PUT, 100.0, 115.0, t4[i], 0.05, 0.02};
        printf("%-10.1f | %-15.5f | %-15.5f\n", t4[i], optionPrice(&o), a4[i]);
    }

    printf("\n======================================================================\n");
    printf("                  Tests des fonctions assurance\n");
    printf("======================================================================\n");

    double p_annuel[3] = {0.9, 0.05, 0.05};
    InsuredClient client = {1.0, 1.0, p_annuel};
    double x_vals[] = {0, 1, 2, 3};

    // --- TABLEAU 5 : LOI X1+X2 ---
    printf("\n5. Loi de X1+X2 (m=s=1)\n");
    printf("%-5s | %-12s | %-12s | %-12s | %-12s\n", "x", "PDF Calc", "PDF Att", "CDF Calc", "CDF Att");
    printf("------|--------------|--------------|--------------|--------------\n");
    double pdf_att[] = {0, 0.0196294, 0.0726663, 0.101814};
    double cdf_att[] = {0, 0.00490103, 0.0517347, 0.141439};
    for(int i=0; i<4; i++) {
        printf("%-5.0f | %-12.7f | %-12.7f | %-12.7f | %-12.7f\n", 
               x_vals[i], clientPDF_X1X2(&client, x_vals[i]), pdf_att[i], 
               clientCDF_X1X2(&client, x_vals[i]), cdf_att[i]);
    }

    // --- TABLEAU 6 : LOI S ---
    printf("\n6. Loi de S (m=s=1, p={0.9, 0.05, 0.05})\n");
    printf("%-10s | %-15s | %-15s\n", "x", "clientCDF_S", "Attendu");
    printf("-----------|-----------------|-----------------\n");
    double s_att[] = {0.9, 0.908178, 0.921561, 0.934036};
    for(int i=0; i<4; i++) {
        printf("%-10.0f | %-15.6f | %-15.6f\n", x_vals[i], clientCDF_S(&client, x_vals[i]), s_att[i]);
    }

    return 0;
}