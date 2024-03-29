%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
tsip=exist('tsipikoulia');
if tsip==0
   startdemo;
   break
end

clear all;
close all;
tsipikoulia=1;
load setmat;
load imbook;
figarx=figure('units','normalized');



colormap(map);
image(c);
set(gca,'units','norm','pos',[0.05 0.3 0.3 0.55]);
axis off

     
neur=uicontrol(figarx,'style','listbox',...
               'string',{'Neural Networks';'Speech Recognition';'Support Vector Machines'},...
               'units','norm',...
               'position',[0.4    0.4880    0.2    0.3],...
               'call',[...
                  'val=get(neur,''value'');',...
                  'if val==1;neuralmenu;',...
                  'elseif val==2;soundrec;',...
                  'elseif val==3;smomenu;end;']);
str=uicontrol(figarx,'style','text',...
               'string','Demos',...
               'units','norm',...
               'pos',[0.4 0.795 0.2 0.03],...
               'back',[0.5 0.55 0.7]);

if screen_res==0
   set(str,'fontsize',[8]);
elseif screen_res==1
   set(str,'fontsize',[11]);
else
   set(str,'fontsize',[13]);
end


exitm=uicontrol(figarx,'style','push',...
               'string','Exit Demo',...
               'units','norm',...
               'pos',[0.4    0.1692    0.2    0.0513],...
               'call','rmpath(cpath,[cpath,''\common'']);clear all;close all hidden;');

set(figarx,'name','                                           P A T T E R N       R E C O G N I S I O N     (Main Menu)',...
    'color',[0.2 0.55 0.7],...
    'numbertitle','off',...
    'menubar','none');
set(figarx,'pos',[0 0 1 0.93]);


   ab={'This demo includes a set of '
   'MATLAB examples, associated with'
   'the book Pattern Recognition.   '
   '        '
   'The demo is being used only for '
   'educational purposes in the dept.'
   'of Informatics, University of Athens.'
   'for any questions suggestions  or'
   'problems contact the author:'
   'stpatrec@di.uoa.gr'};

about=uimenu(figarx,'label','About','call','msgbox(ab,''About'')');
