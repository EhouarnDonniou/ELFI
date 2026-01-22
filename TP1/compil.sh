echo "  "
echo "----Edition de l'éxécutable"
gcc -o creation.exe creation.c error_handling.c fonctions.c alloctab.c freetab.c
echo "  "
echo "----Execution"
creation.exe
echo "  "
echo "----Contenu de cad.txt : "
echo "  "
more cad.txt