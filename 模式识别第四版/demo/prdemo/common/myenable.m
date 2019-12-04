%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------
%%
function myen(onoma)
globcontr
dis=get(eval(onoma),'enable')
if dis(1,1:2)=='on'
   set(eval(onoma),'enable','off');
end

if dis(1,1:2)=='of'
   set(eval(onoma),'enable','on');
end
