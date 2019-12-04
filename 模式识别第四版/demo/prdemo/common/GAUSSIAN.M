%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function y=gaussian(sigma,m1,m2,posa);
%sigma->variance
m(1)=m1;
m(2)=m2;
 for w=1:2;
   for p=1:posa;
    xin=rand;
    b=rand;
    u=2*pi*b;
    r=sqrt(2*(sigma)*log(1/(1-xin)));
    y(p,w)=real(r*cos(u)+m(w));
   end;
 end;
 
 