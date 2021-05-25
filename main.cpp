#include "common.hpp"
#include "QR.hpp"
#include "Jacobiego.hpp"
#include "LU.hpp"
#include "Potegowa.hpp"

using namespace std;

int main(int argc, char * const argv[])
{
    if(argc > 1)
    {
        if(argv[1] == string("-QR") && argc == 3)
        {
            cout<<"Wybrales QR"<<endl<<endl;
            double **macierz_A = odczytaj_dane_z_pliku(argv[2]);
            cout<<"Dane wejsciowe:"<<endl;
            wypisanie_macierzy(macierz_A);
            cout<<endl<<"Wynik:"<<endl;
            QR_oblicz(macierz_A);
        }
        else if (argv[1] == string("-Jacobiego") && argc == 4)
        {
            cout<<"Wybrales Jacobiego"<<endl<<endl;
            double **macierz_A = odczytaj_dane_z_pliku(argv[2]);
            cout<<"Dane wejsciowe:"<<endl;
            wypisanie_macierzy(macierz_A);
            cout<<endl<<"Wynik:"<<endl;
            Jacobiego_oblicz(macierz_A, argv[3]);
        }
        else if (argv[1] == string("-LU") && argc == 3)
        {
            cout<<"Wybrales LU"<<endl<<endl;
            double **macierz_A = odczytaj_dane_z_pliku(argv[2]);
            cout<<"Dane wejsciowe:"<<endl;
            wypisanie_macierzy(macierz_A);
            cout<<endl<<"Wynik:"<<endl;
            LU_oblicz(macierz_A);
        }
        else if (argv[1] == string("-Potegowa") && argc == 3)
        {
            cout<<"Wybrales Potegowa"<<endl<<endl;
            double **macierz_A = odczytaj_dane_z_pliku(argv[2]);
            cout<<"Dane wejsciowe:"<<endl;
            wypisanie_macierzy(macierz_A);
            cout<<endl<<"Wynik:"<<endl;
            Potegowa_oblicz(macierz_A);
        }
        else if (argv[1] == string("-h"))
        {
            cout<<"Mozliwe parametry:"<<endl;
            cout<<"-QR nazwa_pliku - oblicza wektory i wartosci wlasne za pomoca algorytmu QR"<<endl;
            cout<<"-Jacobiego nazwa_pliku (meteoda(c lub m)) - oblicza wektory i wartoœci wlasne za pomoca algorytmu Jacobiego"<<endl;
            cout<<"-LU nazwa_pliku - dokonuje rozkladu LU macierzy"<<endl;
            cout<<"-Potegowa nazwa_pliku - wypisuje wartosc wiodacej i podwiodacej oraz odpowiadajacej im wektorom wlasnym za pomoca metody potegowej"<<endl;
        }
        else
            cout<<"Niepoprawne parametry, mozesz podac parametr '-h' aby dowiedziec sie wiecej";
    }
    else
        cout<<"Niepoprawne parametry, mozesz podac parametr '-h' aby dowiedziec sie wiecej";

    return 0;
}
