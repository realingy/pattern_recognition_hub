%%
function [nw,nb,te,tr,ep,er,bb,t]=bptrm3(metrisis,max_epoch,err_goal,lr,mom_const,err_ratio);
global wt1 bt1 wt2 bt2 wt3 bt3 tempwt2 tempbt2 numclass s1 s2
if numclass==2
  outlayer=1
else
  outlayer=numclass
end
if (size(wt1,2)~=size(metrisis,1))
  wt1=rand(s1,size(metrisis,1));
  bt1=rand(s1,1);
end

if size(wt2,1)~=s2
  wt2=tempwt2;
  bt2=tempbt2;
end
if (size(wt3,1)~=outlayer) | (size(wt3,2)~=s2)
  wt3=rand(outlayer,s2);
  bt3=rand(outlayer,1);
end
pat=size(metrisis,2)/numclass;
 t=zeros(outlayer,size(metrisis,2));
 b=1;
for i=1:outlayer
 t(i,b:b+pat-1)=ones(1,pat);
 b=b+pat;
end


tp=[100,max_epoch,err_goal,lr,mom_const,err_ratio];
[nw,nb,te,tr,ep,er,bb,t]=trbpm3(wt1,bt1,'logsig',wt2,bt2,'logsig',wt3,bt3,'logsig',metrisis,t,tp);