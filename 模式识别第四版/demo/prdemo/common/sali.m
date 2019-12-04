%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function [maskw1,maskw2,maskw3,maskb1,maskb2,maskb3]=saliency(maskw1,maskw2,maskw3,maskb1,maskb2,maskb3,W1,W2,W3,dW1,dW2,dW3,B1,B2,B3,dB1,dB2,dB3,lr);
global  s1 s2 numclass
if numclass==2
  outlayer=1
else
  outlayer=numclass
end
Q=outlayer;
R=size(W1,2);
plithos=30;
limit=0.00000000001;
limitb=0.00000000001;
gtemp1=[];
gtemp2=[];
gtemp3=[];

rlr=1/lr;
dw1=dW1*rlr;
dw2=dW2*rlr;
dw3=dW3*rlr;
db1=dB1*rlr;
db2=dB2*rlr;
db3=dB3*rlr;
k=size(dw1);
for i=1:k(1);
 for j=1:k(2);
  gtemp1=[gtemp1,dw1(i,j)]; 
 end;
end;
k=size(dw2);
for i=1:k(1);
 for j=1:k(2);
  gtemp2=[gtemp2,dw2(i,j)];
 end;
end;
k=size(dw3);
for i=1:k(1);
 for j=1:k(2);
  gtemp3=[gtemp3,dw3(i,j)];
 end;
end;

g = [gtemp1,db1',gtemp2,db2',gtemp3,db3'];
hess =(1/plithos)*g'*g;

salw1=[];
for k=1:s1;
  for l=1:R;
    salw1 = [salw1;(W1(k,l)^2 )*hess(k*l,k*l)];
  end;
end;
sw1=salw1;

salb1=[];
for i=1:s1;
  salb1 = [salb1;(B1(i)^2)*hess(R*s1+i,R*s1+i)];
end;
point1=(R+1)*s1;
sb1=salb1;
salw2=[];
for k=1:s2;
  for l=1:s1;
    salw2 = [salw2;(W2(k,l)^2 )*hess(k*l+point1,k*l+point1)];
  end;
end;
sw2=salw2;
salb2=[];
for i=1:s2;
  salb2 = [salb2;(B2(i)^2)*hess(point1+s1*s2+i,point1+s1*s2+i)];
end;
point2=point1+s1*s2+s2;
salw3=[];
for k=1:Q;
  for l=1:s2;
    salw3 = [salw3;(W3(k,l)^2 )*hess(point2+k*l,point2+k*l)];
  end;
end;
salb3=[];
for i=1:Q;
  salb3 = [salb3;(B3(i)^2)*hess(point2+Q*s2+i,point2+Q*s2+i)];
end;



[a]=find(abs(salw1)<limit);
if ( isempty(maskw1) & ~isempty(a) )
temp=[ceil(a(1)/R),a(1)-(ceil(a(1)/R)-1)*R];
maskw1 = [maskw1;temp(1),temp(2)];
end;
q=size(a);
for k=1:q(1);
 temp=[ceil(a(k)/R),a(k)-(ceil(a(k)/R)-1)*R];
 sz=size(maskw1);
 vrethike=0;
 for i=1:sz(1)
   if ( maskw1(i,1)==temp(1) & maskw1(i,2)==temp(2) )
     vrethike=1;
   end;
 end;
 if vrethike==0 
   maskw1 = [maskw1;temp(1),temp(2)];
 end;
end;

  

[a]=find(abs(salb1)<limitb);
for k=1:size(a);
if find(maskb1==a(k)) 
   maskb1 = [maskb1;a(k)];
 end;
end;


[a]=find(abs(salw2)<limit);
if ( isempty(maskw2) & ~isempty(a) )
 temp=[ceil(a(1)/s1),a(1)-(ceil(a(1)/s1)-1)*s1];
 maskw2 = [maskw2;temp(1),temp(2)];
end;
for k=1:size(a);
 vrethike=0;
 temp=[ceil(a(k)/s1),a(k)-(ceil(a(k)/s1)-1)*s1];
 sz=size(maskw2);
 for i=1:sz(1)
   if ( maskw2(i,1)==temp(1) & maskw2(i,2)==temp(2) )
     vrethike=1;
   end;
 end;
 if vrethike==0
   maskw2 = [maskw2;temp(1),temp(2)];
 end;
end;


[a]=find(abs(salb2)<limitb);
for k=1:size(a);
if find(maskb2==a(k)) 
   maskb2 = [maskb2;a(k)];
 end;
end;

[a]=find(abs(salw3)<limit);
if ( isempty(maskw3) & ~isempty(a) )
 temp=[ceil(a(1)/s2),a(1)-(ceil(a(1)/s2)-1)*s2];
 maskw3 = [maskw3;temp(1),temp(2)];
end;
for k=1:size(a);
 vrethike=0;
 temp=[ceil(a(k)/s2),a(k)-(ceil(a(k)/s2)-1)*s2];
 sz=size(maskw3);
 for i=1:sz(1)
   if ( maskw3(i,1)==temp(1) & maskw3(i,2)==temp(2) )
     vrethike=1;
   end;
 end;
 if vrethike==0
   maskw3 = [maskw3;temp(1),temp(2)];
 end;
end;

[a]=find(abs(salb3)<limitb);
for k=1:size(a);
if find(maskb3==a(k)) 
   maskb3 = [maskb3;a(k)];
 end;
end;


