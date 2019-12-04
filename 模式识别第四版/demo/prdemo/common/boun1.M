%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function inp=b(w1,b1);
global metrisis
a=min(metrisis(1,:))-0.5;
b=max(metrisis(1,:))+0.5;
c=min(metrisis(2,:))-0.5;
d=max(metrisis(2,:))+0.5;
num1=round((b-a)/0.05);
num2=round((d-c)/0.05);
klasi=[];
inp=[];

for i=0:num2
  pin(1,:)=[a:0.05:b];
  pin(2,:)=zeros(1,num1)+(d-i*0.05);
  inp=[inp,pin];
end

  A = feval(f,W*p,B);
  A=round(A);
  thesi=find(A);

  klasi=inp(:,thesi);
  
  l=size(metrisis);
fig5=figure;
gcf=figure(fig5);
hold on
plot(metrisis(1,1:l(2)/2),metrisis(2,1:l(2)/2),'rx');
plot(metrisis(1,l(2)/2+1:l(2)),metrisis(2,l(2)/2+1:l(2)),'bx');
plot(klasi(1,:),klasi(2,:),'.y');
  
