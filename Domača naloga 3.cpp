// Domača naloga 3.cpp : Izračun približka vrednosti integrala po trapeznem pravilu

#define _USE_MATH_DEFINES //Za definiranje mat. konstant

#include <iostream>
#include <cmath>

double tay_arctan(double x, double nz)

//Funkcija vrne vrednost razvoja arctan(x) v Taylorjevo funkcijo v točki "x", z "nz" členi vrste
{
	double arctan_zap = 0.0;
	for(int i = 0; i < nz; i++)
	{
		double ul_zgor = pow(-1, i) * pow(x, 2 * i + 1);
		double ul_spod = 2 * i + 1;

		arctan_zap += (ul_zgor / ul_spod);
	}
	
	return(arctan_zap);
}

double vrednost_f(double x, double nz)

//Funkcija vrne vrednost funkcije f(x) podane v domači nalogi v točki x
{
	double f = exp(3 * x) * tay_arctan(x / 2, nz);
	
	return(f);
}

double integral(double ni, double a, double b, double nz)
// ni... število podobmočij
// a... spodnja meja integrala
// b... zgornja meja integrala
// nz... število členov razvoja arctan(x) v Taylorjevo vrsto

//Funkcija vrne približek vrednsti integrala podanega v Domači nalogi 3 po trapeznem pravilu
{
	double vrednost_integrala = 0.0;
	double h = (b - a) / ni; //korak podobmočij
	double členi = 0.0;
	double zač = (b - a) / (2 * ni); //Ulomek na začetku formule za izračun integrala po trapeznem pravilu

	for (int o = 1; o < ni-1; o++)
	{
		členi += 2 * vrednost_f(h * o, nz); 
	}
	vrednost_integrala = zač * (vrednost_f(a, nz) + členi + vrednost_f(b, nz));

	return(vrednost_integrala);
}




int main()
{
	std::cout <<"Domaca naloga 3: Izracun priblizka integrala po trapeznem pravilu:" << "\n" << "\n" << "Priblizek integrala = " << integral(1000000, 0, M_PI_4, 30) << "\n";
}
