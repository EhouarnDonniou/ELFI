echo "  "
echo "----Edition de l'éxécutable"
gcc -g -std=c99 -o creation.exe creation.c fonctions/error_handling.c fonctions/fonctions.c fonctions/alloctab.c fonctions/freetab.c
echo "  "
echo "----Execution"
creation.exe
echo "  "
echo "----Contenu de cad.txt : "
echo "  "
more cad.txt