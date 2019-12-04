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

k=gaussian(s,1.875,3,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,0.75,1.5,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,2.7,1.8,plithos);
klasi1=[klasi1,k'];

k=gaussian(s,0.75,3,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,3,3,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,1.875,0.45,plithos);
klasi2=[klasi2,k'];

metrisis=[klasi1,klasi2];
plot(klasi1(1,:),klasi1(2,:),'rx');
hold on;
plot(klasi2(1,:),klasi2(2,:),'bx');
axis([-s s+3.5 -s s+3.5]);
grid;
hold off;
 