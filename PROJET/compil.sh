clear
cd functions/fortran/
gfortran -c *.f 
cd ../../
gcc -g TP3_4.c functions/fortran/*.o functions/*.c -lm -lgfortran -o TP3_4.exe
cd functions/fortran/
rm *.o
cd ../../
TP3_4.exe

