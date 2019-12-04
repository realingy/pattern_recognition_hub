%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function [klasi1,klasi2]=bound(nw1,nb1,nw2,nb2,nw3,nb3);
global fig5 metrisis
klasi1=[];
klasi2=[];
for i=0:0.05:3.5
tempA3 = 5;
for j=0:0.05:3.5
simeio=[i;j];
A1 = logsig(nw1*simeio,nb1);
A2 = logsig(nw2*A1,nb2);
A3 = logsig(nw3*A2,nb3);
if ( ((A3>=0.5) & (tempA3<=0.5)) | ((A3<=0.5) & (tempA3>=0.5) & (tempA3 ~= 5)) );
klasi1=[klasi1,simeio];
end;
tempA3=A3;
end;
end;
malakia =12345678
tempA3 = 0.5;
for j=0:0.05:3.5
tempA3 = 5;
for i=0:0.05:3.5
simeio=[i;j];
A1 = logsig(nw1*simeio,nb1);
A2 = logsig(nw2*A1,nb2);
A3 = logsig(nw3*A2,nb3);
if ( ((A3>=0.5) & (tempA3<=0.5)) | ((A3<=0.5) & (tempA3>=0.5)) );
klasi2=[klasi2,simeio];
end;
tempA3=A3;
end;
end;

l=size(metrisis);
for i=1:3*l(2)/4;
metrisisa(1,i)=metrisis(1,i);
metrisisa(2,i)=metrisis(2,i);
end
for i=3*l(2)/4+1:l(2);
metrisisb(1,i-l(2)/2)=metrisis(1,i);
metrisisb(2,i-l(2)/2)=metrisis(2,i);
end
fig5=figure;
gcf=figure(fig5);
hold on
plot(metrisisa(1,:),metrisisa(2,:),'rx');
plot(metrisisb(1,:),metrisisb(2,:),'bx');
plot(klasi1(1,:),klasi1(2,:),'k.');
plot(klasi2(1,:),klasi2(2,:),'k.');
set(gcf,'color','w');
set(gca,'xcolor','k');
set(gca,'ycolor','k');
hold off
