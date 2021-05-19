#include "QR.hpp"

#include "common.hpp"

void QR_oblicz(double **macierz_A)
{
    double ***H = new double **[N]; //uzywamy tylko do N-1
    double **R = new double *[N];
    double **pr = new double *[N];
    double **Q = new double *[N];
    double **Q_mnozenie = new double *[N];
    double *wektor = new double [N];
    double *wektor_wynikowy = new double [N];

    for(int i=0; i<N; i++){
        H[i] = new double *[N];
        R[i] = new double[N];
        pr[i] = new double[N];
        Q[i] = new double[N];
        Q_mnozenie[i] = new double[N];
    }
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            H[i][j] = new double[N];
        }
    }

    double dzielnik;
    int i = 0;
    for(i=0; wyznacz_max_poza_diagonalia(macierz_A) && i < 10000; i++)
    {
        for(int k=0; k<N-1; k++)
        {
            if(k==0)
            {
                dzielnik = przygotuj_wektor_v(macierz_A, wektor, k);        //przygotowanie wektora
                mnozenie_wektorow(wektor, dzielnik, H[k]);                  //mnozenie specjalne wektora v * v
                mnozenie_macierzy(H[k], macierz_A, R);
            }
            else
            {
                dzielnik = przygotuj_wektor_v(R, wektor, k);                //przygotowanie wektora
                mnozenie_wektorow(wektor, dzielnik, H[k]);                  //mnozenie specjalne wektora v * v

                //wyznaczanie R
                kopiuj_macierz(H[k], R);
                for(int k_v2 = k-1; k_v2>=0; k_v2--){
                    mnozenie_macierzy(R, H[k_v2], pr);
                    kopiuj_macierz(pr, R);
                }
                mnozenie_macierzy(R, macierz_A, pr);
                kopiuj_macierz(pr, R);
            }
        }
        //wyznaczanie Q
        if(N == 2)
        {
            kopiuj_macierz(H[0], Q);
            /*cout<<"Q"<<endl;
            wypisanie_macierzy(Q);
            cout<<"R"<<endl;
            wypisanie_macierzy(R);*/

        }
        else
        {
            for(int k=0; k<N-2; k++)
            {
                if(k==0) mnozenie_macierzy(H[0], H[1], Q);
                else
                {
                    mnozenie_macierzy(Q, H[k+1], pr);
                    kopiuj_macierz(pr, Q);
                }
            }
        }

        if(i==0)
        {
            kopiuj_macierz(Q, Q_mnozenie);
        }
        else
        {
            mnozenie_macierzy(Q_mnozenie, Q, pr);
            kopiuj_macierz(pr, Q_mnozenie);
        }

        mnozenie_macierzy(R, Q, macierz_A);
        /*cout<<"Macierz A"<<endl;
        wypisanie_macierzy(macierz_A);*/
        //cout<<i<<endl;
    }
    cout<<"Dokladnosc: "<<DOKLADNOSC<<" lub 10 000 rotacji"<<endl;
    cout<<"Uzyto rotacji: "<<i<<endl;
    cout<<"Wartosci wlasne:"<<endl;
    wypisanie_wartosci_wlasnych(macierz_A);

    cout<<endl<<"wektory wlasne:"<<endl;
    for(int i=0; i<N; i++)
    {
        wyznacz_wektor_x(macierz_A, i, wektor);
        macierz_razy_wektor(Q_mnozenie, wektor, wektor_wynikowy);
        cout<<"{";
        for(int i=0; i<N; i++)
        {
            cout<<wektor_wynikowy[i];
            if(i+1 != N) cout<<", ";
        }
        cout<<"}"<<endl;
    }
}
//funkcja przygotowuje wektor v i zwraca jego dlugosc
double przygotuj_wektor_v(double **a, double *wektor, int numer)
{
    double dlugosc=0;
    double dzielnik=0;
    for(int i=0; i<N; i++)
    {
        if(i<numer) wektor[i] = 0;
        else
        {
            wektor[i] = a[i][numer];
            dlugosc += pow(wektor[i], 2);
        }
    }
    wektor[numer] += sqrt(dlugosc);

    for(int i=numer; i<N; i++)
        dzielnik += pow(wektor[i], 2);

    return (-2)/dzielnik;
}
//mnozenie wektora przez jego transpozycje, wynikiem macierz hausholdera
void mnozenie_wektorow(double *a, double dzielnik, double **wynik)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            wynik[i][j] = dzielnik*a[i]*a[j];
            if(i==j) wynik[i][j] = 1+wynik[i][j];
        }
    }
}
bool wyznacz_max_poza_diagonalia(double **macierz)
{
    double m = 0;
    double elem;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            if(i != j)
            {
                elem = abs(macierz[j][i]);
                if(elem > m) m = elem;
            }
        }
    return m > DOKLADNOSC;
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

void wyznacz_wektor_x(double **macierz, int numer, double *wektor)
{
    for(int j=N-1; j>numer; j--) wektor[j] = 0;
    wektor[numer] = 1;  //dla j == numer
    for(int j=numer-1; j>=0; j--)
    {
        double suma=0;
        for(int k=j+1; k<=numer; k++)
            suma += macierz[j][k] * wektor[k];
        wektor[j] = (1) * suma / (macierz[j][j] - macierz[numer][numer]);
    }
}
