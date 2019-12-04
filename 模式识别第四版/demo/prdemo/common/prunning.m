%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function [W1,B1,W2,B2,W3,B3]=prunning(W1,B1,W2,B2,W3,B3,maskw1,maskb1,maskw2,maskb2,maskw3,maskb3);
k=size(maskw1);
for i=1:k(1);
W1(maskw1(i,1),maskw1(i,2))=0;
end;
k=size(maskb1);
for i=1:k(1);
B1(maskb1(i))=0;
end;
k=size(maskw2); 
for i=1:k(1);
W2(maskw2(i,1),maskw2(i,2))=0;
end;
k=size(maskb2);
for i=1:k(1);
B2(maskb2(i))=0;
end;
k=size(maskw3);
for i=1:k(1);
W3(maskw3(i,1),maskw3(i,2))=0;
end;
k=size(maskb3);
for i=1:k(1);
B3(maskb3(i))=0;
end;