clear
cd functions/fortran/
gfortran -c *.f 
cd ../../
gcc -g TP5.c functions/fortran/*.o functions/*.c -lm -lgfortran -o ../TP5.exe
cd functions/fortran/
rm *.o
cd ../../../
./TP5.exe