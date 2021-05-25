#include "LU.hpp"

#include "common.hpp"

void LU_oblicz(double **macierz_A)
{
    double ** LU = new double * [N];
    double ** L = new double * [N];
    double ** U = new double * [N];
    int * wek = new int [N];

    for (int i = 0; i<N; i++)
    {
        LU[i] = new double [N];
        L[i] = new double [N];
        U[i] = new double [N];
    }

    bool trueFalse = faktoryzuj_LU(macierz_A, LU, wek, 0);
    if(trueFalse)
    {
        wypisanie_LU(LU, L, U, wek);
        cout<<endl<<"L x U"<<endl;
        mnozenie_macierzy(L, U, macierz_A);
        wypisanie_macierzy(macierz_A);
    }
    else cout<<"Faktoryzacja sie nie powiodla :("<<endl;
}

void wypisanie_LU(double **macierz, double**L, double**U, int *wek)
{
    cout<<"L x U = P x A"<<endl<<endl;
    cout<<"P:"<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(j==wek[i]) cout<<"1"<<" ";
            else cout<<"0"<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<"L:"<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(j<i) {cout<<macierz[i][j]<<" ";L[i][j] =macierz[i][j];}
            else if(i==j) {cout<<"1"<<" "; L[i][j]=1;}
            else L[i][j] = 0;// cout<<"0"<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<"U:"<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(j>=i) {cout<<macierz[i][j]<<" "; U[i][j] = macierz[i][j];}
            else {cout<<" "<<" "; U[i][j] = 0;}
        }
        cout<<endl;
    }
}
//ZMIENNA PIVOT
// 0 bez piwotow
// 1 z czesciowym wyborem elementu glownego
bool faktoryzuj_LU(double **tab, double **m, int *wek, int pivot)
{
    for(int i=0; i<N; i++) wek[i]=i;
    kopiuj_macierz(tab, m);
    int glowny, t;
    double tymczas;
    for(int k=0; k<N-1; k++)
    {
        if(pivot == 1)  //zezwolenie na pivot
        {//szukanie elementu glownego
            glowny=k;
            for(int i=k; i<N; i++) if(abs(m[i][k])>abs(m[k][k])) glowny = i;

            //zamiana wierszy
            if(glowny != k)
            {
                t = wek[k];
                wek[k] = wek[glowny];
                wek[glowny] = t;
                for(int i=0; i<N; i++)
                {
                    tymczas = m[k][i];
                    m[k][i] = m[glowny][i];
                    m[glowny][i] = tymczas;
                }
            }
        }

        //wyznaczanie kolumny macierzy L
        for(int i=k+1; i<N; i++)
        {
            if (m[k][k] == 0) //tu w specyficznych przypadkach moze byc zero
            {
                //jesli
                bool trueFalse = false;
                if(pivot == 0)
                    trueFalse = faktoryzuj_LU(tab, m, wek, 1);
                if(trueFalse) return true;
                else return false;
            }
            else m[i][k] = m[i][k]/m[k][k];
        }

        //uzupelnienie Schura
        for(int i=k+1; i<N; i++)
            for(int j=k+1; j<N; j++)
                m[i][j] = m[i][j] - m[i][k]*m[k][j];
    }
    return true;
}
