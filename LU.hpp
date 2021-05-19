#ifndef LU_HPP_INCLUDED
#define LU_HPP_INCLUDED

extern int N;

void LU_oblicz(double **macierz_A);
void wypisanie_LU(double **macierz, double**L, double**U, int *wek);
bool faktoryzuj_LU(double **tab, double **m, int *wek, int pivot);


#endif // LU_HPP_INCLUDED
