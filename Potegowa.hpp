#ifndef POTEGOWA_HPP_INCLUDED
#define POTEGOWA_HPP_INCLUDED

extern int N;

void Potegowa_oblicz(double **macierz_A);
double mnozenie_wektorow(double *a, double *b);
void wypisanie_wektora(double *wektor);
double dlugosc_wektora(double *wektor);
void normalizacja_wektora(double *wektor);
void skracanie_wektora(double *wektor, double liczba, double *wynik);
void wydluzanie_wektora(double *wektor, double liczba, double *wynik);

#endif // POTEGOWA_HPP_INCLUDED
