clear
gfortran -c functions/fortran/*.f 
gcc -g TP3.c *.o functions/*.c -lm -lgfortran -o TP3.exe
TP3.exe

