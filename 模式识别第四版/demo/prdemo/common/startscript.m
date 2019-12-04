%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
if strcmp(algorithm,'bptr3pr')
   [nw1,nb1,nw2,nb2,nw3,nb3]=bptr3pr(metrisis,max_epoch,err_goal,lr);
end

if strcmp(algorithm,'bptr')
   [nw1,nb1,nw2,nb2]=bptr(metrisis,max_epoch,err_goal,lr);
end

if strcmp(algorithm,'bptra')
   [nw,nb]=bptra(metrisis,max_epoch,err_goal,lr,lr_inc,lr_dec,err_ratio);
end

if strcmp(algorithm,'bptrm')
   [nw,nb]=bptrm(metrisis,max_epoch,err_goal,lr,mom_const,err_ratio);
end

if strcmp(algorithm,'bptrx')
   [nw,nb]=bptrx(metrisis,max_epoch,err_goal,lr,lr_inc,lr_dec,mom_const,err_ratio);
end

if strcmp(algorithm,'bptr3')
   [nw,nb]=bptr3(metrisis,max_epoch,err_goal,lr);
end

if strcmp(algorithm,'bptra3')
   [nw,nb]=bptra3(metrisis,max_epoch,err_goal,lr,lr_inc,lr_dec,err_ratio);
end

if strcmp(algorithm,'bptrm3')
   [nw,nb]=bptrm3(metrisis,max_epoch,err_goal,lr,mom_const,err_ratio);
end

if strcmp(algorithm,'bptrx3')
   [nw1,nb1,nw2,nb2,nw3,nb3,a,tr]=bptrx3(metrisis,max_epoch,err_goal,lr,lr_inc,lr_dec,mom_const,err_ratio);
end




















   
   
   
   
   
   
   
   
   
   
   
   