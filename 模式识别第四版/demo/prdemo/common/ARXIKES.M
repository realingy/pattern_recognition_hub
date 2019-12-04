%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function [w1,b1,w2,b2]=arxikes
global w1 b1 w2 b2 epilogi
if epilogi==2
 w1=rand(3,2)
 b1=rand(3,1)
 w2=rand(1,3)
 b2=rand
else 
 w1=rand(2,2)
 b1=rand(2,1)
 w2=rand(1,2)
 b2=rand
end;
