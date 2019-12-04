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
gcf=figure(figt3);
numclass=2;
p=20;
dim=2;
m=20;
cells_per_dim=2;
range=2;
dist=0.1;
drawnow
[plithos,metrisis]=checkers_book(dim, m, m, cells_per_dim, range, dist);

nc = uicontrol('style','slider','units','normal','pos',[0.1 0 .1 .035], ...
     'min',20,'max',200,'val',m, ...
     'call',[...
     'set(nct,''string'',[''number of samples: '',num2str(round(get(nc,''val'')))]),',...     
     'm = round(get(nc,''value'')); [plithos, metrisis]=checkers_book(dim, m, m, cells_per_dim, range, dist);']);
 
nct = uicontrol('style','text','units','normal','pos',[0.1 .035 .15 .035], ...
     'string',['number of samples:',num2str(round(get(nc,'value')))]);


 
nc2 = uicontrol('style','slider','units','normal','pos',[0.4 0.0 .1 .035], ...
     'min',-0.3,'max',0.3,'val',dist, ...
     'call',[...
     'set(nct2,''string'',[''dist: '',num2str(get(nc2,''val''))]),',...     
     'dist = get(nc2,''value''); [plithos, metrisis]=checkers_book(dim, m, m, cells_per_dim, range, dist);']);

nct2 = uicontrol('style','text','units','normal','pos',[0.4 .035 .1 .035], ...
     'string',['dist: ',num2str(get(nc2,'value'))]);


nc3 = uicontrol('style','slider','units','normal','pos',[.7 .0 .08 .035], ...
     'min',2,'max',5,'SliderStep',[0.3 0.6 ],'val',cells_per_dim, ...
     'call',[...
     'set(nct3,''string'',[''cells per dim '',num2str(round(get(nc3,''val'')))]),',...     
     'cells_per_dim = round(get(nc3,''value'')); [plithos,metrisis]=checkers_book(dim, m, m, cells_per_dim, range, dist);']);

nct3 = uicontrol('style','text','units','normal','pos',[.7 .035 .1 .035], ...
     'string',['cells per dim ',num2str(round(get(nc3,'value')))]);
   
 
 


