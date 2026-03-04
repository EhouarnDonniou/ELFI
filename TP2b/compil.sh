#
#--------------------------------------------------------------------------------
#    Ehouarn DONNIOU, Damien MALETTE, Dora PAPAI
#
#    Ecrit le 04/03/2026
#--------------------------------------------------------------------------------
#

clear
echo "  "
echo "----Edition de l'éxécutable creation.exe"
gcc -o test_intElem.exe TP2b.c 
echo "  "
more input_maillage.txt
creation.exe
echo " "
