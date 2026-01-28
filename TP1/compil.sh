echo "  "
echo "----Edition de l'éxécutable"
gcc -o creation.exe creation.c fonctions/error_handling.c fonctions/fonctions.c
echo "  "
echo "----Execution"
creation.exe
echo "  "
echo "----Contenu de cad.txt : "
echo "  "
more cad.txt
echo "  "