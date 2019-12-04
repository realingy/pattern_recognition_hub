%%
function [nw,nb,nw2,nb2,te,tr]=bptrx(metrisis,max_epoch,err_goal,lr,lr_inc,lr_dec,mom_const,err_ratio);
global wt1 bt1 wt2 bt2 numclass s1

if numclass==2
  outlayer=1
else
  outlayer=numclass
end
if (size(wt1,2)~=size(metrisis,1))
  wt1=rand(s1,size(metrisis,1));
  bt1=rand(s1,1);
end

if (size(wt2,1)~=outlayer) | (size(wt2,2)~=s1)
  wt2=rand(outlayer,s1);
  bt2=rand(outlayer,1);
end
pat=size(metrisis,2)/numclass;
 t=zeros(outlayer,size(metrisis,2));
 b=1;
for i=1:outlayer
 t(i,b:b+pat-1)=ones(1,pat);
 b=b+pat;
end


tp=[100,max_epoch,err_goal,lr,lr_inc,lr_dec,mom_const,err_ratio];

[nw,nb,nw2,nb2,te,tr]=trbpx2(wt1,bt1,'logsig',wt2,bt2,metrisis,t,tp);
