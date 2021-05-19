#include "common.hpp"
#include "Jacobiego.hpp"
//#include "QR.hpp"

using namespace std;

int main(int argc, char * const argv[])
{
    if(argc > 1)
    {
        if(argv[1] == string("-QR") && argc == 3)
        {
            cout<<"Wybrales QR"<<endl<<endl;
            double **macierz_A = odczytaj_dane_z_pliku(argv[2]);
            cout<<endl<<"Wynik:"<<endl;
            //QR_oblicz(macierz_A, argv[3]);
        }
        else if (argv[1] == string("-Jacobiego") && argc == 4)
        {
            cout<<"Wybrales Jacobiego"<<endl<<endl;
            double **macierz_A = odczytaj_dane_z_pliku(argv[2]);
            cout<<endl<<"Wynik:"<<endl;
            Jacobiego_oblicz(macierz_A, argv[3]);
        }
        else if (argv[1] == string("-h"))
        {
            cout<<"Mozliwe parametry:"<<endl;
            cout<<"-QR nazwa_pliku - oblicza wektory i wartoœci w³asne za pomoca algorytmu QR"<<endl;
            cout<<"-Jacobiego nazwa_pliku (meteoda(c lub m)) - oblicza wektory i wartoœci w³asne za pomoca algorytmu Jacobiego"<<endl;
        }
        else
            cout<<"Niepoprawne parametry, mozesz podac parametr '-h' aby dowiedziec sie wiecej";
    }
    else
        cout<<"Niepoprawne parametry, mozesz podac parametr '-h' aby dowiedziec sie wiecej";

    return 0;
}
