#include "Jacobiego.hpp"

#include "common.hpp"

void Jacobiego_oblicz(double **macierz_A, char *param1)
{
    double **pierwotna = new double *[N];
    double **macierz_R = new double *[N];
    double **macierz_A_prim = new double *[N];
    double **wektory = new double *[N];
    double **tymczasowa = new double *[N];
    double **tymczasowa2 = new double *[N];

    for(int i=0; i<N; i++){
        pierwotna[i] = new double[N];
        macierz_R[i] = new double [N];
        macierz_A_prim[i] = new double[N];
        wektory[i] = new double[N];
        tymczasowa[i] = new double[N];
        tymczasowa2[i] = new double[N];
    }

    bool (*wskfun) (double**, int*, int*);

    if(param1[0] == 'm') wskfun = wyznacz_max_poza_diagonalia;
    else if(param1[0] == 'c') wskfun = wyznacz_nastepny_cyklicznie;
    else {cout<<"podales niepoprawny parametr QR"; return;}

    int i_m, j_m;
    double s, c;
    int i = 0;
    for(i=0; wskfun(macierz_A, &i_m, &j_m) && i < 10000; i++)
    {
        wyznacz_s_i_c(macierz_A, i_m, j_m, &s, &c);

        wyznacz_macierz_A_prim(macierz_A, i_m, j_m, s, c, macierz_A_prim);

        wyznacz_macierz_R(i_m, j_m, s, c, macierz_R);
/*
        mnozenie_macierzy(macierz_R, macierz_A, tymczasowa);
        transpozycja_macierzy(macierz_R, pierwotna);
        mnozenie_macierzy(tymczasowa, pierwotna, macierz_A);
*/
        if(i==0) kopiuj_macierz(macierz_R, wektory);
        else
        {
            mnozenie_macierzy(wektory, macierz_R, tymczasowa);
            kopiuj_macierz(tymczasowa, wektory);
        }
        //cout<<i<<endl;
    }

    cout<<"Dokladnosc: "<<DOKLADNOSC<<" lub 10 000 rotacji"<<endl;
    cout<<"Uzyto rotacji: "<<i<<endl;
    cout<<"Wartosci wlasne:"<<endl;
    wypisanie_wartosci_wlasnych(macierz_A);
    cout<<endl<<"wektory wlasne:"<<endl;
    wypisanie_wektorow_wlasnych(wektory);
}
bool wyznacz_max_poza_diagonalia(double **macierz, int *i_m, int *j_m)
{
    double m = 0;
    double elem;

    for(int i=0; i<N; i++)
        for(int j=i+1; j<N; j++)    //zawsze w gornej polowce
        {
            elem = abs(macierz[j][i]);
            if(elem > m)
            {
                m = elem;
                *i_m = i;
                *j_m = j;
            }
        }
    return m > DOKLADNOSC;
}
bool wyznacz_nastepny_cyklicznie(double **macierz, int *i_m, int *j_m)
{
    static int i_x, j_x;
    double elem;
    int j_startowe = j_x +1;

    for(int i=i_x; i<N; i++)
    {
        for(int j=j_startowe; j<N; j++)
        {
            elem = abs(macierz[j][i]);
            if(elem > DOKLADNOSC && i != j)
            {
                *i_m = i;
                *j_m = j;
                i_x = i;
                j_x = j;
                return true;
            }
            if(i == i_x && j == j_x)
                return false;
        }
        if(j_startowe != 0) j_startowe = 0;
        if(i+1 == N) i=-1;
    }
    return false;
}

void wyznacz_s_i_c(double **macierz, int i_m, int j_m, double *s, double *c)
{
    double omega = (macierz[j_m][j_m] - macierz[i_m][i_m]) / macierz[i_m][j_m] / 2;
    double t;
    if(omega > 0)
        t = ((-1) * omega) + sqrt(pow(omega, 2) + 1);
    else
        t = ((-1) * omega) - sqrt(pow(omega, 2) + 1);

    *s = t / sqrt(1 + pow(t, 2));
    *c = 1 / sqrt(1 + pow(t, 2));
}

void wyznacz_macierz_R(int i_m, int j_m, double s, double c, double **macierz_R)
{
    for(int i = 0; i<N; i++)
        for(int j=0; j<N; j++)
        {
            if(i==j) macierz_R[i][j] = 1;
            else macierz_R[i][j] = 0;
        }
    macierz_R[i_m][i_m] = c;
    macierz_R[j_m][j_m] = c;
    macierz_R[j_m][i_m] = (-1) * s;
    macierz_R[i_m][j_m] = s;
}

void wyznacz_macierz_A_prim(double **macierz_A, int i_m, int j_m, double s, double c, double **macierz_A_prim)
{
    macierz_A_prim[i_m][i_m] = pow(c, 2)*macierz_A[i_m][i_m] - 2*c*s*macierz_A[i_m][j_m] + pow(s, 2)*macierz_A[j_m][j_m];
    macierz_A_prim[j_m][j_m] = pow(s, 2)*macierz_A[i_m][i_m] + 2*c*s*macierz_A[i_m][j_m] + pow(c, 2)*macierz_A[j_m][j_m];
    double x = (pow(c, 2)-pow(s, 2))*macierz_A[i_m][j_m] + c*s*(macierz_A[i_m][i_m] - macierz_A[j_m][j_m]);
    macierz_A_prim[i_m][j_m] = x;
    macierz_A_prim[j_m][i_m] = x;

    for(int k = 0; k<N; k++)
    {
        if(k != i_m && k != j_m)
        {
            x = c*macierz_A[i_m][k] - s*macierz_A[j_m][k];
            macierz_A_prim[i_m][k] = x;
            macierz_A_prim[k][i_m] = x;

            x = s*macierz_A[i_m][k] + c*macierz_A[j_m][k];
            macierz_A_prim[j_m][k] = x;
            macierz_A_prim[k][j_m] = x;
        }
    }
    //przepisanie do macierzy A
    macierz_A[i_m][i_m] = macierz_A_prim[i_m][i_m];
    macierz_A[j_m][j_m] = macierz_A_prim[j_m][j_m];
    macierz_A[i_m][j_m] = macierz_A_prim[i_m][j_m];
    macierz_A[j_m][i_m] = macierz_A_prim[j_m][i_m];

    for(int k = 0; k<N; k++)
    {
        if(k != i_m && k != j_m)
        {
            macierz_A[i_m][k] = macierz_A_prim[i_m][k];
            macierz_A[k][i_m] = macierz_A_prim[k][i_m];
            macierz_A[j_m][k] = macierz_A_prim[j_m][k];
            macierz_A[k][j_m] = macierz_A_prim[k][j_m];
        }
    }
}
