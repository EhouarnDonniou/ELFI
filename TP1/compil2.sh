clear
echo "  "
echo "----Edition de l'éxécutable"
gcc -o verification.exe verification.c fonctions/error_handling.c fonctions/fonctions.c fonctions/alloctabint.c fonctions/freetab.c fonctions/lecfima.c fonctions/alloctab.c
echo "  "
echo "----Execution"
verification.exe
echo "  "
echo "----"
echo "  "
#more output_maillage.txt
echo "  "