%%
function [nw1,nb1,nw2,nb2,nw3,nb3,te,tr] = ...
  trbp3(w1,b1,f1,w2,b2,f2,w3,b3,f3,p,t,tp)
global figmain fig
global figt1 figt2 figt3 axt1 axt3 ax framen s1 s2
mesage=['1st layer:',num2str(s1),'  2nd layer:',num2str(s2),'  learnin rate:',num2str(tp(4))];
mes='3-layer pure BP ';
if nargin ~= 12
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
DF2 = feval(f2,'delta');
W3 = w3;
B3 = b3;
DF3 = feval(f3,'delta');
e=0.3;
% PRESENTATION PHASE
A1 = feval(f1,W1*p,B1);
A2 = feval(f2,W2*A1,B2);
A3 = feval(f3,W3*A2,B3);
E = t-A3;
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


tic
for epoch=1:me

  % CHECK PHASE
  if SSE < eg, epoch=epoch-1; break, end

  % BACKPROPAGATION PHASE
  D3 = feval(DF3,A3,E);
  D2 = feval(DF2,A2,D3,W3);
  D1 = feval(DF1,A1,D2,W2);

  % LEARNING PHASE
  [dW1,dB1] = learnbp(p,D1,lr);
  [dW2,dB2] = learnbp(A1,D2,lr);
  [dW3,dB3] = learnbp(A2,D3,lr);
  W1 = W1 + dW1; B1 = B1 + dB1;
  W2 = W2 + dW2; B2 = B2 + dB2;
  W3 = W3 + dW3; B3 = B3 + dB3;


  % PRESENTATION PHASE
  A1 = feval(f1,W1*p,B1);
  A2 = feval(f2,W2*A1,B2);
  A3 = feval(f3,W3*A2,B3);
  E = t-A3;

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
     klasi=boun3(W1,B1,W2,B2,W3,B3);
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
     klasi=boun3(W1,B1,W2,B2,W3,B3);
     global klasi
  end

el_time=toc
% RETURN RESULTS

nw1 = W1;
nb1 = B1;
nw2 = W2;
nb2 = B2;
nw3 = W3;
nb3 = B3;
te = epoch;
tr = [SSE0 TR(1:epoch)];

