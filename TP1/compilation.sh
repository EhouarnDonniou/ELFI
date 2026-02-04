#
#--------------------------------------------------------------------------------
#    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI
#
#    Ecrit le 01/02/2026
#--------------------------------------------------------------------------------
#

rm output_maillage.txt verif.txt
clear
echo "  "
echo "----Edition de l'éxécutable creation.exe"
echo "Créé le fichier de maillage à partir d'un fichier générateur"
gcc -o creation.exe creation.c fonctions/error_handling.c fonctions/fonc_creation.c
echo "  "
echo "----Execution"
echo "- fichier générateur, input_maillage.txt : "
more input_maillage.txt
creation.exe
echo " "
echo "- fichier de maillage, output_maillage.txt: "
more output_maillage.txt
echo " "
echo "----Edition de l'éxécutable verifictaion.exe"
echo "Executable permettant de vérifier la fonction : lecfima"
echo "Lit un fichier de maillage, réécrit les données lues dans un autre fichier de vérification."
gcc -o verification.exe verification.c fonctions/gestion_tab.c fonctions/lecfima.c
echo "----Execution"
echo "entrée : output_maillage.txt"
echo "sortie : verif.txt"
verification.exe
echo " "
echo "--différence entre output_maillage.txt et verif.txt : "
diff output_maillage.txt verif.txt -s
echo " "



