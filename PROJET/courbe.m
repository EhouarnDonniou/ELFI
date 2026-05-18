clear all
figure(2)
Mq=readmatrix('output/d1_c2_q.txt');
errquadq=Mq(:,1);
errmaxq=Mq(:,2);
hq=Mq(:,3);
loglog(-hq,errquadq,'-b','LineWidth',2);hold on
loglog(-hq,errmaxq,'-r','LineWidth',2);hold on
xlabel('-h')
title('Courbes de convergences')
cvquad = polyfit(log10(hq),log10(errquadq),1);
cvmax = polyfit(log10(hq),log10(errmaxq),1);
ordrecvquad = cvquad(1);
ordrecvmax = cvmax(1);
display(['Ordre de convergence erreur quadratique relative quadrangles : ',num2str(ordrecvquad)])
display(['Ordre de convergence erreur maximum relative quadrangles : ',num2str(ordrecvmax)])

Mt=readmatrix('output/d1_c2_t.txt');
errquadt=Mt(:,1);
errmaxt=Mt(:,2);
ht=Mt(:,3);
loglog(-ht,errquadt,'--b','LineWidth',2);hold on
loglog(-ht,errmaxt,'--r','LineWidth',2)
hold on
legend('q-quad','q-max','t-quad','t-max');
grid
xlabel('-h')
grid on; axis tight;
cvquad = polyfit(log10(ht),log10(errquadt),1);
cvmax = polyfit(log10(ht),log10(errmaxt),1);
ordrecvquad = cvquad(1);
ordrecvmax = cvmax(1);
display(['Ordre de convergence erreur quadratique relative triangles : ',num2str(ordrecvquad)])
display(['Ordre de convergence erreur maximum relative triangles : ',num2str(ordrecvmax)])