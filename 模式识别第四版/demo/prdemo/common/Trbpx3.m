function [nw1,nb1,nw2,nb2,nw3,nb3,te,tr] = ...
  trbpx3(w1,b1,f1,w2,b2,f2,w3,b3,f3,p,t,tp)
global figmain fig
global figt1 figt2 figt3 axt1 axt3 ax framen s1 s2 
tp5=(tp(5)-1)*100;
tp6=(1-tp(6))*100;
mesage=['1st layer:',num2str(s1),'  2nd layer:',num2str(s2),'  learnin rate:',num2str(tp(4)),'   momentum:',num2str(tp(7)),'    lr_inc:',num2str(tp5),'%','    lr_dec:',num2str(tp6),'%'];
mes='3-layer adaptive BP with momentum';
if nargin ~= 12
  error('Wrong number of arguments.');
  end

% TRAINING PARAMETERS
df = tp(1);
me = tp(2);
eg = tp(3);
lr = tp(4);
im = tp(5);
dm = tp(6);
mc = tp(7);
er = tp(8);
%p=play(p);
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

dW1 = W1*0;
dB1 = B1*0;
dW2 = W2*0;
dB2 = B2*0;
dW3 = W3*0;
dB3 = B3*0;
MC = 0;

% PRESENTATION PHASE
A1 = feval(f1,W1*p,B1);
A2 = feval(f2,W2*A1,B2);
A3 = feval(f3,W3*A2,B3);
E = t-A3;
SSE = sumsqr(E);

% TRAINING RECORD
TR = zeros(2,me);
SSE0 = SSE;
lr0 = lr;

% BACKPROPAGATION PHASE
D3 = feval(DF3,A3,E);
D2 = feval(DF2,A2,D3,W3);
D1 = feval(DF1,A1,D2,W2);


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

  % LEARNING PHASE
  [dW1,dB1] = learnbpm(p,D1,lr,MC,dW1,dB1);
  [dW2,dB2] = learnbpm(A1,D2,lr,MC,dW2,dB2);
  [dW3,dB3] = learnbpm(A2,D3,lr,MC,dW3,dB3);
  MC = mc;
  TW1 = W1 + dW1; TB1 = B1 + dB1;
  TW2 = W2 + dW2; TB2 = B2 + dB2;
  TW3 = W3 + dW3; TB3 = B3 + dB3;

  % PRESENTATION PHASE
  TA1 = feval(f1,TW1*p,TB1);
  TA2 = feval(f2,TW2*TA1,TB2);
  TA3 = feval(f3,TW3*TA2,TB3);
  TE = t-TA3;
  TSSE = sumsqr(TE);


  % MOMENTUM & ADAPTIVE LEARNING RATE PHASE
  if TSSE > SSE*er
    lr = lr * dm;
    MC = 0;
  else
    if TSSE < SSE
      lr = lr * im;
      end
    W1=TW1; B1=TB1; W2=TW2; B2=TB2; W3=TW3; B3=TB3;
    A1=TA1; A2=TA2; A3 = TA3; E=TE; SSE=TSSE;

    % BACKPROPAGATION PHASE
    D3 = feval(DF3,A3,E);
    D2 = feval(DF2,A2,D3,W3);
    D1 = feval(DF1,A1,D2,W2);
    end

  % TRAINING RECORD
  TR(1,epoch) = SSE;
  TR(2,epoch) = lr;

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
tr = [[SSE0; lr0] TR(:,1:epoch)];
