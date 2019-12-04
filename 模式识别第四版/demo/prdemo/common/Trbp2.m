function [nw1,nb1,nw2,nb2,te,tr]=trbp2(w1,b1,f1,w2,b2,p,t,tp)
 global figmain fig 
global figt1 figt2 figt3 axt1 axt3 ax framen s1 
mesage=['nodes:',num2str(s1),  '    learnin rate:',num2str(tp(4))];
mesage=[];
mes='2-layer pure BP ';
if nargin ~= 8
  error('Wrong number of arguments.');
  end

% TRAINING PARAMETERS
df = tp(1);
me = tp(2);
eg = tp(3);
lr = tp(4);

% NETWORK PARAMETERS
W1 = w1;
B1 = b1;
DF1 = feval(f1,'delta');
W2 = w2;
B2 = b2;
DF2 = feval(f1,'delta');

% PRESENTATION PHASE
A1 = feval(f1,W1*p,B1);
A2 = feval(f1,W2*A1,B2);
E = t-A2;
SSE = sumsqr(E);

% TRAINING RECORD
TR = zeros(1,me);
SSE0 = SSE;

if size(p,1)>2
   gcf=figure(figt3);
   fig=figt3;
   clf;
   ax=axt3;
else
   gcf=figure(figt1);
   fig=figt1;
   clf;
   ax=axt1;
   gcf=figure(figt2);
   clf;
   drawnow
end

for epoch=1:me

  % CHECK PHASE
  if SSE < eg, epoch=epoch-1; break, end

  % BACKPROPAGATION PHASE
  D2 = feval(DF1,A2,E);
  D1 = feval(DF2,A1,D2,W2);

  % LEARNING PHASE
  [dW1,dB1] = learnbp(p,D1,lr);
  [dW2,dB2] = learnbp(A1,D2,lr);
  W1 = W1 + dW1; B1 = B1 + dB1;
  W2 = W2 + dW2; B2 = B2 + dB2;
  % PRESENTATION PHASE
  A1 = feval(f1,W1*p,B1);
  A2 = feval(f1,W2*A1,B2);
  E = t-A2;

  SSE = sumsqr(E);

  % TRAINING RECORD
  TR(epoch) = SSE;

  % DISPLAY RESULTS
%  if rem(epoch,df) == 0
%    gcf=figure(fig);
%    plottr([SSE0 TR(1,1:epoch)],mesage,mes)
%    end
 if (rem(epoch,500) == 0) | (epoch == 1)
plotr([SSE0 TR(1,1:epoch)],mesage,mes)  
  if size(p,1)<3
     gcf=figure(figt2);
     clf
     drawnow
     klasi=boun2(W1,B1,W2,B2);
     global klasi
  end
 end
 end

  plotr([SSE0 TR(1,1:epoch)],mesage,mes)  
  gcf=figure(fig);

  title(mesage,'color',[0.7930 0.1875 0.2031]);
  if size(p,1)<3
     gcf=figure(figt2);
     clf
     drawnow
     klasi=boun2(W1,B1,W2,B2);
     global klasi
  end

% RETURN RESULTS

nw1 = W1;
nb1 = B1;
nw2 = W2;
nb2 = B2;
te = epoch;
tr = [SSE0 TR(1:epoch)];


