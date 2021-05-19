#ifndef JACOBIEGO__HPP_INCLUDED
#define JACOBIEGO__HPP_INCLUDED

void Jacobiego_oblicz(double **macierz_A, char *param1);
bool wyznacz_max_poza_diagonalia(double **macierz, int *i_m, int *j_m);
bool wyznacz_nastepny_cyklicznie(double **macierz, int *i_m, int *j_m);
void wyznacz_s_i_c(double **macierz, int i_m, int j_m, double *s, double *c);
void wyznacz_macierz_R(int i_m, int j_m, double s, double c, double **macierz_R);
void wyznacz_macierz_A_prim(double **macierz_A, int i_m, int j_m, double s, double c, double **macierz_A_prim);



#endif // JACOBIEGO__HPP_INCLUDED
