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

k=gaussian(s,1,1,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,1,0,plithos);
klasi1=[klasi1,k'];
k=gaussian(s,0.8,0.5,plithos);
klasi1=[klasi1,k'];

k=gaussian(s,0,0,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,0,1,plithos);
klasi2=[klasi2,k'];
k=gaussian(s,0.2,0.5,plithos);
klasi2=[klasi2,k'];

metrisis=[klasi1,klasi2];
plot(klasi1(1,:),klasi1(2,:),'rx');
hold on;
plot(klasi2(1,:),klasi2(2,:),'bx');
axis([-s-0.5 s+1.5 -s-0.5 s+1.5]);
grid;
hold off;
