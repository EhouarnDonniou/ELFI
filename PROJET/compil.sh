clear
cd source/functions/fortran/
gfortran -c *.f 
cd ../../
gcc -g TP5.c functions/fortran/*.o functions/*.c -lm -lgfortran -o ../TP_ELFI.exe
cd functions/fortran/
rm *.o
cd ../../../
./TP_ELFI.exe