%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------

function y=cost_fun(f1,f2)
   f1size=size(f1);
   f2size=size(f2);
   f1col=f1size(1,2);
   f2col=f2size(1,2);
   for i=1:f2col
     for j=1:f1col
        temp=f1(:,j)-f2(:,i);
        temp=temp .^2;
        y(i,j)=sqrt(sum(temp));
     end
   end