clear all
close all


N=100;
M=100;
d=0.3;

X11=3*rand(1,N);
X12=6*rand(1,N);
X1=[X11;X12];
X21=3*rand(1,M)+3 +d;
X22=6*rand(1,M);
X2=[X21;X22];

figure
plot(X11,X12,'b+')
hold on
plot(X21,X22,'r*')
axis([0 6 0 6]);

X=[X1 X2]';
Y=[ones(1,size(X1')) -1*ones(1,size(X2'))]'
pause

kernel = 'rbf';
kpar1 = 1;
kpar2 = 0;
C = 30000;
tol = 0.00001;
eps = 0.0000000001;
steps = 4000;
method = 1;
tic;
[alpha, b, w, evals, stp,glob]= SMO(X, Y, kernel, kpar1, kpar2, C, tol, steps, eps, method);
toc;
pause;



%wx-b=0
x1=-5:5;
 for i=1:size(x1')
  x2(i)=(+b-w(1,1)*x1(i))/w(1,2);
end
plot(x1,x2,'k')

%wx-b=1
x1=-5:5;
 for i=1:size(x1')
  x2(i)=(1+b-w(1,1)*x1(i))/w(1,2);
end
plot(x1,x2,'b')


%wx-b=-1
x1=-5:5;
 for i=1:size(x1')
  x2(i)=(-1+b-w(1,1)*x1(i))/w(1,2);
end
plot(x1,x2,'r')


 
