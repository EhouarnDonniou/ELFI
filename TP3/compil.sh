clear
gfortran -c functions/fortran/*.f 
gcc TP3.c *.o functions/*.c functions/calcul_quadrature/*.c functions/calculs_elementaires/*.c functions/ecrit-lecture_maillage/*.c functions/fonctions_utilitaires/*.c -lm -lgfortran -o TP3.exe
TP3.exe
