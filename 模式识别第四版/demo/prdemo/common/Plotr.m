%%
function plotr(tr,t,mes)
global fig ax
gcf=figure(fig);

 

clf reset
set(fig,...
    'numbertitle','off',...
    'menubar','none',...
    'name',mes);

[r,c] = size(tr);

fontsize=[4];
semilogy(0:c-1,tr(1,:),'r');
xlabel('Epoch')
ylabel('Sum-Squared Error')
set(gca,'fontsize',[8]);
if nargin == 1
  title('Network Error')
else
  title(t)
end

if r >= 2
  subplot(212)
 plot(0:c-1,tr(2,:),'r');
 xlabel('Epoch')
  ylabel('Learning Rate')
  if nargin == 1
    title('Network Learning Rate')
  else
    title(t)
    end
  end
drawnow
set(fig,'NextPlot','replace')
