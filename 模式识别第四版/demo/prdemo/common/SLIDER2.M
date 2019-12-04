%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
% Sliders
global numclass figt3
numclass=2;
gcf=figure(figt3);

drawnow

s = 0.01;
p = 20;
shape1 = [s p];
[plithos,metrisis]=plot3l(s,p);
nc = uicontrol('style','slider','units','normal','pos',[.05 .00 .25 .035], ...
     'min',0,'max',0.03,'val',s, ...
     'call',[...
     'set(nct,''string'',[''variance : '',num2str(get(nc,''val''))]),',...     
     's = get(nc,''value''); [plithos,metrisis]=plot3l(s,p);']);

nct = uicontrol('style','text','units','normal','pos',[.075 .057 .2 .05], ...
     'string',['variance : ',num2str(get(nc,'value'))]);

ec = uicontrol('style','slider','units','normal','pos',[.70 .00 .25 .035], ...
     'min',5,'max',100,'val',p, ...
     'call',[...
     'k=get(ec,''val''),',...  
     'set(ect,''string'',[''patterns : '',num2str(round(k))]),',...     
     'p = get(ec,''value''); [plithos,metrisis]=plot3l(s,p);']);
ect = uicontrol('style','text','units','normal','pos',[.725 .057 .2 .05], ...
     'string',['patterns : ',num2str(round(get(ec,'value')))]);

p=round(p);

