#include "common.hpp"

#include <fstream>

int N;

double** odczytaj_dane_z_pliku(char *nazwa_pliku)
{
    ifstream odczyt(nazwa_pliku);
    if(odczyt.good()==false)
    {
        odczyt.close();
        cout<<"Nie ma takiego pliku";
        return new double *[0];
    }
    odczyt>>N;

    double **macierz_A = new double *[N];

    for(int i=0; i<N; i++)
    {
        macierz_A[i] = new double[N];
        for(int j=0; j<N; j++)
        {
            odczyt>>macierz_A[i][j];
        }
    }
    odczyt.close();
    return macierz_A;
}
//macierz1, macierz2, macierz wynikowa
void mnozenie_macierzy(double **a, double **b, double **wynik)
{
    double t;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            t = 0;
            for(int k=0; k<N; k++)
                t += a[i][k]* b[k][j];
            wynik[i][j] = t;
        }
    }
}
//kopiuj z "a" do "b"
void kopiuj_macierz(double **a, double **b)
{
    for(int i=0; i<N; i++)  //wiersz
    {
        for(int j=0; j<N; j++)  //kolumna
        {
            b[i][j]=a[i][j];
        }
    }
}
void wypisanie_macierzy(double **macierz)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<macierz[i][j]<<" ";
        }
        cout<<endl;
    }
}

void wypisanie_wartosci_wlasnych(double **a)
{
    for(int i=0; i<N; i++)
        cout<<a[i][i]<<endl;
}
void wypisanie_wektorow_wlasnych(double **a)
{
    for(int i=0; i<N; i++)
    {
        cout<<"{";
        for(int j=0; j<N; j++)
        {
            cout<<a[j][i];
            if(j+1<N) cout<<", ";
        }

        cout<<"}"<<endl;
    }
}
void transpozycja_macierzy(double **macierz, double **wynik)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            wynik[i][j] = macierz[j][i];
        }
    }
}
void macierz_razy_wektor(double **macierz, double *wektor, double *wynik)
{
    for(int i=0; i<N; i++)
    {
        wynik[i] = 0;
        for(int j=0; j<N; j++)
            wynik[i] += macierz[i][j] * wektor[j];
    }
}
