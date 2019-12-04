%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function klasi=b2(W1,B1,W2,B2);
global metrisis
a=ceil(min(metrisis(1,:)))-1;
b=ceil(max(metrisis(1,:)));
c=ceil(min(metrisis(2,:)))-1;
d=ceil(max(metrisis(2,:)));
x=(b-a)/40;
y=(b-a)/40;
num1=(b-a)/x;
num2=(d-c)/y;
klasi=[];
inp=[];

for i=0:num2
  pin(1,:)=[a:x:b];
  pin(2,:)=zeros(1,num1+1)+(d-i*y);
  inp=[inp,pin];
end

  A1 = feval('logsig',W1*inp,B1);
  A2 = feval('logsig',W2*A1,B2);
  A=round(A2);
  thesi=find(A);

  klasi=inp(:,thesi);
  
  l=size(metrisis);
  size(klasi);
  if ~isempty(klasi)
plot(klasi(1,:),klasi(2,:),'.y');
end

hold on
plot(metrisis(1,1:l(2)/2),metrisis(2,1:l(2)/2),'rx');
plot(metrisis(1,l(2)/2+1:l(2)),metrisis(2,l(2)/2+1:l(2)),'bx');
drawnow
hold off  

