%setup pattern recognition demo.
echo off
warning off
clear all
close all hidden
cpath=pwd;
path(path, cpath);
path(path, [cpath,'/common']);;
load imbook;
f=figure('units','norm');
set(f,'numbertitle','off','menubar','none','color',[0.9 0.88 0.9],...
   'name','Pattern Recognition DEMO');
subplot(1,2,1)
colormap(map);
%image(c);
set(gca,'units','norm','pos',[0.02 0.4 0.3 0.5]);
image(c)
axis off;
sound_card=1;
screen_res=1;
subplot(1,2,2);
info={'This demo includes a set of '
   'MATLAB examples, associated with'
   'the book Pattern Recognition.   '
   '        '
   'The demo is being used only for '
   'educational purposes in the dept.'
   'of Informatics, University of Athens.'};
set(gca,'units','norm','pos',[0.35 0.1 0.6 0.8]);
axis off;
helpstring=uicontrol(f,'style','listbox','units','norm',...
   'back','white','pos',[0.5 0.43 0.4 0.45],'string',info);

textsound=uicontrol(f,'style','text','string','Do you have a sound card?',...
   'units','norm','pos',[0 0.3 0.3 0.05],'back',[0.9 0.88 0.9]);
rads1=uicontrol(f,'units','norm','string','Yes','value',1,...
   'style','radio','pos',[0.05 0.25 0.1 0.05],'back',[0.9 0.88 0.9],...
   'call',[...
      'set(rads2,''value'',0);',...
      'sound_card=1;']);
rads2=uicontrol(f,'units','norm','string','No','value',0,...
   'pos',[0.2 0.25 0.1 0.05],'style','radio','back',[0.9 0.88 0.9],...
   'call',[...
      'set(rads1,''value'',0);',...
      'sound_card=0;']);
screen_res=1;
websiteb=uicontrol(f,'string','Visit the web site','units','norm','pos',[0.55 0.34 0.3 0.05],...
   'call','web(''http://www.di.uoa.gr/~stpatrec'')');
contaut=uicontrol(f,'string','Contact Author','units','norm','pos',[0.55 0.28 0.3 0.05],...
   'call','web(''mailto:stheodor@di.uoa.gr'')');

Okbutton=uicontrol(f,'string','Start Patern Recognition Demo','units','norm','pos',[0.55 0.2 0.3 0.07],...
   'call',[...
      'save setmat cpath sound_card screen_res setup_var;prdemo;']);

tsipikoulia=1;
setup_var=1;

