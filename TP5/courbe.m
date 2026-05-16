clear all
close all
M=load('output/tab_err/d2_c3_t.txt');
errquad=M(:,1);
errmax=M(:,2);
h=M(:,3);
loglog(-h,errquad,'-b','LineWidth',2)
hold on
loglog(-h,errmax,'-r','LineWidth',2)
legend('erreur quadratique relative ', 'erreur maximum relative');
grid
xlabel('-h')
title('Courbes de convergences en échelle loglog')
cvquad = polyfit(log10(h),log10(errquad),1);
cvmax = polyfit(log10(h),log10(errmax),1);
ordrecvquad = cvquad(1);
ordrecvmax = cvmax(1);
display(['Ordre de convergence erreur quadratique relative : ',num2str(ordrecvquad)])
display(['Ordre de convergence erreur maximum relative : ',num2str(ordrecvmax)])
