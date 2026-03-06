// #define GRAPHIC

#define PFA_C

#include "pfa.h"

/* Initialize the integration variables.
   Arguments :
   - quadrature : name of the quadrature formula that will be used. It can be "left", "right", 
     "middle", "trapezes", "simpson", "gauss2" or "gauss3".
   - dt : a positive value, which will be used to decide the number of subdivisions of an 
          interval [a,b], when computing the integration.
          The number of subdivisions will be N such that (b-a)/N ~ dt
*/
  
bool init_integration(char* quadrature, double dt)
{
    if (dt <= 0.0) {
        return false;
    }

    pfa_dt = dt;

    pfaQF.xk = NULL;
    pfaQF.wk = NULL;

    return setQuadFormula(&pfaQF, quadrature);
} 


/* Density of the normal distribution */
double phi(double x)
{
	return 0.398942280401433 * exp( -x*x/2 );
}


/* Cumulative distribution function of the normal distribution */
double PHI(double x)
{
    if (x == 0.0) {
        return 0.5;
   }

    if (x > 0.0) {
        return 0.5 + integrate_dx(phi, 0.0, x, pfa_dt, &pfaQF);
    }
	
	else {
		double valeur_absolue = -x;
    	return 0.5 - integrate_dx(phi, 0.0, valeur_absolue, pfa_dt, &pfaQF);
	}
}

/* =====================================
   Finance function: price of an option 
*/
double optionPrice(Option* option)
{
    double S0  = option->S0;
    double K   = option->K;
    double T   = option->T;
    double mu  = option->mu;
    double sig = option->sig;

	if (sig <= 0.0 || T <= 0.0 || S0 <= 0.0 || K <= 0.0) {
		return 0.0;
	}

    // Calcul de sigma * sqrt(T)
    double sig_sqrt_T = sig * sqrt(T);

    // Calcul de z0
    double z0 = (log(K / S0) - (mu - (sig * sig) / 2.0) * T) / sig_sqrt_T;

    // facteur exponentiel
    double facteur = exp(mu * T);

    // Calcul du prix d'un call / put
    if (option->type == CALL) {
        return S0 * facteur * PHI(sig_sqrt_T - z0) - K * PHI(-z0);
    } 
    else {
        return K * PHI(z0) - S0 * facteur * PHI(z0 - sig_sqrt_T);
    }
}



/* ===============================================*/
/* Insurance functions */

/* Probability density function (PDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientPDF_X(InsuredClient* client, double x)
{
   // Sécurité
    if (x <= 0.0) {
        return 0.0;
    }

    double m = client->m;
    double s = client->s;

    if (s <= 0.0) {
      return 0.0;
    }

    double z = (log(x) - m) / s;

    // Formule de la densité log-normale avec phi(z)
    return (1.0 / (x * s)) * phi(z);
}


/* Cumulative distribution function (CDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientCDF_X(InsuredClient* client, double x)
{
    if (x <= 0.0) {
        return 0.0;
    }

    double m = client->m;
    double s = client->s;

   if (s <= 0.0) {
      return 0.0;
   }

    double z = (log(x) - m) / s;

    // Fonction PHI avec z
    return PHI(z);
}


/* ==========================================================*/
/* Distribution of X1+X2 : static intermediate functions     */

/* The static functions localProductPDF and localPDF_X1X2 take only one
   argument, of type double.
   They hence can be integrated: function integrate_dx takes as argument a function pointer f, 
   where f depends only on one argument (double t).
   The static functions below can be given as argument to integrate_dx.

   That's why we copy other variables of the final functions (client and x) to local static variables, 
   and define these static functions depending on only one argument (double t).
   These local functions can hence be arguments of integrate_dx.
*/
static InsuredClient* localClient;
static double localX;


/* This function assumes that static variables localClient and localX have been set.
   It can be an argument of integrate_dx (since it has the good signature)
*/
static double localProductPDF(double t)
{
  return clientPDF_X(localClient, localX - t) * clientPDF_X(localClient, t);
}

/* Density of X1+X2

   This function assumes that static variable localClient has been set.
   It is called by clientPDF_X1X2
   It can also be an argument of integrate_dx (since it has the good signature)
*/
static double localPDF_X1X2(double x)
{
   localX = x; 
   return integrate_dx(localProductPDF, 0.0, x, pfa_dt, &pfaQF);
} 

/* Probability density function (PDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/

double clientPDF_X1X2(InsuredClient* client, double x)
{
   if (x <= 0.0) {
      return 0.0;
   }

   localClient = client;
   return localPDF_X1X2(x);
}

/* Cumulative distribution function (CDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/

double clientCDF_X1X2(InsuredClient* client, double x)
{
    // Sécurité
    if (x <= 0.0) {
        return 0.0;
    }

   localClient = client;

   return integrate_dx(localPDF_X1X2, 0.0, x, pfa_dt, &pfaQF);
}



/* Cumulative distribution function (CDF) of variable S.
   Variable S is the sum of the reimbursements that the insurance company will pay to client.
*/
double clientCDF_S(InsuredClient* client, double x)
{
    // Sécurité
    if (x < 0.0) {
        return 0.0;
    }

    // probas de scénarios
    double p0 = client->p[0];
    double p1 = client->p[1];
    double p2 = client->p[2];

    // Pour chaque scénario
    double proba_cas0 = p0 * 1.0;
    double proba_cas1 = p1 * clientCDF_X(client, x);
    double proba_cas2 = p2 * clientCDF_X1X2(client, x);

    return proba_cas0 + proba_cas1 + proba_cas2;
}



