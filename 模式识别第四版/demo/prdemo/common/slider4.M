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


center1=-1;
center2=1;
p = 40;
[plithos,metrisis]=ransettest2(center1,center2,p);

cen1 = uicontrol('style','slider','units','normal','pos',[.05 .00 .15 .04], ...
     'min',-2,'max',0,'SliderStep',[0.1 0.3],'val',center1, ...
     'call',[...
     'set(cen1t,''string'',[''center1 : '',num2str(get(cen1,''val''))]),',...     
     'center1 = get(cen1,''value''); [plithos,metrisis]=ransettest2(center1,center2,p);']);

cen1t = uicontrol('style','text','units','normal','pos',[.05 .04 .15 .025], ...
     'string',['center 1 : ',num2str(get(cen1,'value'))]);

 
cen2 = uicontrol('style','slider','units','normal','pos',[.4 .00 .15 .04], ...
     'min',0,'max',2,'SliderStep',[0.1 0.3],'val',center2, ...
     'call',[...
     'set(cen2t,''string'',[''center2 : '',num2str(get(cen2,''val''))]),',...     
     'center2 = get(cen2,''value''); [plithos,metrisis]=ransettest2(center1,center2,p);']);

cen2t = uicontrol('style','text','units','normal','pos',[.4 .04 .15 .025], ...
     'string',['center 2 : ',num2str(get(cen2,'value'))]);


 
 
ec = uicontrol('style','slider','units','normal','pos',[.70 .00 .15 .04], ...
     'min',5,'max',100,'val',p, ...
     'call',[...
     'k=get(ec,''val'');,',...  
     'set(ect,''string'',[''patterns : '',num2str(round(k))]),',...     
     'p = get(ec,''value'');  [plithos,metrisis]=ransettest2(center1,center2,p);']);
 
ect = uicontrol('style','text','units','normal','pos',[.7 .04 .15 .025], ...
     'string',['patterns : ',num2str(round(get(ec,'value')))]);

p=round(p);

