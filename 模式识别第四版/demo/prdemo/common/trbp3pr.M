%%
function [nw1,nb1,nw2,nb2,nw3,nb3,te,tr] = ...
  trbp3pr(w1,b1,f1,w2,b2,f2,w3,b3,f3,p,t,tp)
global figmain fig
global figt1 figt2 figt3 axt1 axt3 ax framen s1 s2
 zw1=find(w1);
 zw2=find(w2);
 zw3=find(w3);
 zb1=find(b1);
 zb2=find(b2);
 zb3=find(b3);
 nonzero = size(zw1)+size(zb1)+size(zw2)+size(zb2)+size(zw3)+size(zb3)
mesage=['1st layer:',num2str(s1),'  2nd layer:',num2str(s2),'  learnin rate:',num2str(tp(4))];
mes=['Prunning with 3-layer pure BP   weights: ',int2str(nonzero(1,1))];
size(p);
size(w1);
maskw1=[];
maskw2=[];
maskb1=[];
maskb2=[];
maskw3=[];
maskb3=[];
tw1=0;
tw2=0;
tw3=0;
tb1=0;
tb2=0;
tb3=0;
tmaskw1=[];
tmaskw2=[];
tmaskb1=[];
tmaskb2=[];
tmaskw3=[];
tmaskb3=[];
if nargin ~= 12
  error('Wrong number of arguments.');
  end

% TRAINING PARAMETERS
df = tp(1);
me = tp(2)
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

bes=0;
tempsse=SSE
protompike=0;
stathero=0;
tic

for epoch=1:me

  % CHECK PHASE
  if SSE < eg, epoch=epoch-1; break, end
  mpike=0;
  if 1.7*tempsse < SSE 
   tempsse=SSE;
   ep=epoch;
   bes=1;
  end;
  if (bes==1) 
   if epoch>(ep+78) 
    if (0.9*tempsse)<SSE
     [W1,B1,W2,B2,W3,B3]=prunning(tw1,tb1,tw2,tb2,tw3,tb3,tmaskw1,tmaskb1,tmaskw2,tmaskb2,tmaskw3,tmaskb3);
     gcf=figure(fig);
     plotr([SSE0 TR(1,1:epoch)],mesage,mes);
     if size(p,1)<3
      gcf=figure(figt2);
      clf
      drawnow
      klasi=boun3(W1,B1,W2,B2,W3,B3);
      global klasi
     end
     break
    end;
   end;
  end;
  
  % BACKPROPAGATION PHASE
  D3 = feval(DF3,A3,E);
  D2 = feval(DF2,A2,D3,W3);
  D1 = feval(DF1,A1,D2,W2);

  % LEARNING PHASE
  [dW1,dB1] = learnbp(p,D1,lr);
  [dW2,dB2] = learnbp(A1,D2,lr);
  [dW3,dB3] = learnbp(A2,D3,lr);

if (SSE<SSE0/7) 
 if (rem(epoch,80)==0)
  bes=0;
  tw1=W1;
  tb1=B1;
  tw2=W2;
  tb2=B2;
  tw3=W3;
  tb3=B3;
  tmaskw1=maskw1;
  tmaskb1=maskb1;
  tmaskw2=maskw2;
  tmaskb2=maskb2;
  tmaskw3=maskw3;
  tmaskb3=maskb3;   
  [maskw1,maskw2,maskw3,maskb1,maskb2,maskb3]=sali(maskw1,maskw2,maskw3,maskb1,maskb2,maskb3,W1,W2,W3,dW1,dW2,dW3,B1,B2,B3,dB1,dB2,dB3,lr);
  protompike=1;
  mpike=1;
  tempsse=SSE;
 end;
end;
  W1 = W1 + dW1; B1 = B1 + dB1;
  W2 = W2 + dW2; B2 = B2 + dB2;
  W3 = W3 + dW3; B3 = B3 + dB3;
[W1,B1,W2,B2,W3,B3]=prunning(W1,B1,W2,B2,W3,B3,maskw1,maskb1,maskw2,maskb2,maskw3,maskb3);
if mpike==1
 zw1=find(W1);
 zw2=find(W2);
 zw3=find(W3);
 zb1=find(B1);
 zb2=find(B2);
 zb3=find(B3);
 nonzero = size(zw1)+size(zb1)+size(zw2)+size(zb2)+size(zw3)+size(zb3);
mes=['Prunning with 3-layer pure BP   weights: ',int2str(nonzero(1,1))];
end;
  % PRESENTATION PHASE
  A1 = feval(f1,W1*p,B1);
  A2 = feval(f2,W2*A1,B2);
  A3 = feval(f3,W3*A2,B3);
  E = t-A3;
  SSE = sumsqr(E);

  % TRAINING RECORD
  TR(epoch) = SSE;

  % DISPLAY RESULTS
  if (rem(epoch,200) == 0) | (epoch == 1)
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

  if (rem(epoch,200) == 0) | (epoch == 1)
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

