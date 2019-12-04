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

k=gaussian(s,2.3,2.3,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,2,1.8,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,2.6,1.8,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,0.4,0.9,plithos);
klasi1=[klasi1,k'];

k=gaussian(s,1.5,3,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,3.3,2.6,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,1.5,1,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,1.9,1,plithos);
klasi2=[klasi2,k'];

metrisis=[klasi1,klasi2];
plot(klasi1(1,:),klasi1(2,:),'rx');
hold on;
plot(klasi2(1,:),klasi2(2,:),'bx');
axis([-s s+3.5 -s s+3.5]);
grid;
hold off;
