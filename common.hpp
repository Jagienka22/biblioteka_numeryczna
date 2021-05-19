#ifndef common_hpp
#define common_hpp

#include <iostream>
#include <cmath>

using namespace std;

//parametry programu:
#define DOKLADNOSC 0.00001

extern int N;

double** odczytaj_dane_z_pliku(char *nazwa_pliku);
void mnozenie_macierzy(double **a, double **b, double **wynik);
void kopiuj_macierz(double **a, double **b);
void wypisanie_macierzy(double **macierz);
void wypisanie_wartosci_wlasnych(double **a);
void wypisanie_wektorow_wlasnych(double **a);
void transpozycja_macierzy(double **macierz, double **wynik);

#endif
