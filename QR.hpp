#ifndef QR_HPP_INCLUDED
#define QR_HPP_INCLUDED

extern int N;

void QR_oblicz(double **macierz_A);
double przygotuj_wektor_v(double **a, double *wektor, int numer);
void mnozenie_wektorow(double *a, double dzielnik, double **wynik);
bool wyznacz_max_poza_diagonalia(double **macierz);
void macierz_razy_wektor(double **macierz, double *wektor, double *wynik);
void wyznacz_wektor_x(double **macierz, int numer, double *wektor);

#endif // QR_HPP_INCLUDED
