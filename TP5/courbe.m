clear all
close all
M=readmatrix('fort.txt');
errquad=M(:,1);
errmax=M(:,2);
h=M(:,3);
loglog(-h,errquad,'-b','LineWidth',2)
hold on
loglog(-h,errmax,'-r','LineWidth',2)
legend('erreur quadratique relative ', 'erreur maximum relative');
grid
xlabel('-h')
title('Courbes de convergences')
plot(w,z,'o')
cvquad = polyfit(h,errquad,1);
cvmax = polyfit(h,errmax,1);
ordrecvquad = cvquad(1);
ordrecvmax = cvmax(1);
display('Ordre de convergence erreur quadratique relative : ',ordrecvquad)
display('Ordre de convergence erreur maximum relative : ',ordrecvmax)