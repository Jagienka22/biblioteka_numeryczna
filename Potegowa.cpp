#include "Potegowa.hpp"

#include "common.hpp"

void Potegowa_oblicz(double **macierz_A)
{
    double lambda1=0, lambda0;

    double * wektorY = new double [N];
    double * wektorZ = new double [N];
    double * wektorWlasny1 = new double [N];
    double * wektorPrzejscia = new double [N];
    double * wektorYv2 = new double [N];

    for(int i=0; i<N; i++) wektorY[i]=pow(i+1, 11);
    for(int i=0; i<N; i++) wektorYv2[i]=wektorY[i];
    normalizacja_wektora(wektorY);
    normalizacja_wektora(wektorYv2);

    //szukanie wiod¹cej wartoœci w³asnej
    do
    {
        lambda0 = lambda1;
        macierz_razy_wektor(macierz_A, wektorY, wektorZ);
        lambda1 = dlugosc_wektora(wektorZ);
        skracanie_wektora(wektorZ, lambda1, wektorY);
    }
    while(abs(lambda0-lambda1)>0.0000000000001);

    cout<<endl<<"wiodaca wartosc wlasna: " <<lambda1;
    cout<<endl<<"Wektor wlasny: "<<endl;
    normalizacja_wektora(wektorY);
    wypisanie_wektora(wektorY);
    for(int i=0; i<N; i++) wektorWlasny1[i]=wektorY[i];

    /////////////////////////////////////////////////////////////
    //szukanie podwiod¹cej wartoœci w³asnej
    for(int i=0; i<N; i++) wektorY[i]=pow(N/(i+1), 11);

    wektorY[N]=0;
    normalizacja_wektora(wektorY);
    double tymczas = mnozenie_wektorow(wektorY, wektorYv2);
    wektorY[N] = -tymczas/wektorYv2[N];
    normalizacja_wektora(wektorY);

    lambda1 = 0;
    do
    {
        lambda0 = lambda1;
        macierz_razy_wektor(macierz_A, wektorY, wektorZ);
        ///////////////////
        double mnozenie = mnozenie_wektorow(wektorWlasny1, wektorZ);
        wydluzanie_wektora(wektorWlasny1, mnozenie, wektorPrzejscia);
        for(int i=0; i<N; i++) wektorZ[i] = wektorZ[i]-wektorPrzejscia[i];
        ///////////////////
        lambda1 = dlugosc_wektora(wektorZ);
        skracanie_wektora(wektorZ, lambda1, wektorY);
    }
    while(abs(lambda0-lambda1)>DOKLADNOSC);

    cout<<endl<<"podwiodaca wartosc wlasna: " <<lambda1;
    cout<<endl<<"Wektor wlasny podwiodacej: "<<endl;
    normalizacja_wektora(wektorY);
    wypisanie_wektora(wektorY);
}
//mnozenie transpozycji wektora przez wektor = wynikiem liczba
double mnozenie_wektorow(double *a, double *b)
{
    double wynik = 0;
    for(int i=0; i<N; i++)
    {
       wynik +=a[i]*b[i];
    }
    return wynik;
}
void wypisanie_wektora(double *wektor)
{
    for(int i=0; i<N; i++)
    {
        cout<<wektor[i];
        cout<<endl;
    }
}
double dlugosc_wektora(double *wektor)
{
    double dlugosc = 0;
    for(int i=0; i<N; i++)
    {
        dlugosc += wektor[i]*wektor[i];
    }
    dlugosc = sqrt(dlugosc);
    return dlugosc;
}
void normalizacja_wektora(double *wektor)
{
    double dlugosc = dlugosc_wektora(wektor);
    for(int i=0; i<N; i++)
    {
        wektor[i] = wektor[i]/dlugosc;
    }
}
void skracanie_wektora(double *wektor, double liczba, double *wynik)
{
    for(int i=0; i<N; i++)
    {
        wynik[i] = wektor[i]/liczba;
    }
}
void wydluzanie_wektora(double *wektor, double liczba, double *wynik)
{
    for(int i=0; i<N; i++)
    {
        wynik[i] = wektor[i]*liczba;
    }
}
