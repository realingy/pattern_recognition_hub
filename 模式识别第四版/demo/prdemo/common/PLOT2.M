%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function [plithos,metrisis]=pl(s,p);
global metrisis plithos;
plithos=round(p);
klasi1=[];klasi2=[];
k=gaussian(s,0,0,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,2,2,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,0,2,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,2,0,plithos);
klasi2=[klasi2,k'];
metrisis=[klasi1,klasi2];
metrisisa=klasi1;
metrisisb=klasi2;
plot(metrisisa(1,:),metrisisa(2,:),'rx');
hold on
plot(metrisisb(1,:),metrisisb(2,:),'bx');
axis([-s-0.5 s+2.5 -s-0.5 s+2.5]);
grid;
hold off
 