to run the demo
%-- 13-4-17 ÉÏÎç9:56 --%
cpath=pwd;
sound_card=1;
screen_res=1;
setup_var=1;

cd D:\matlabwork\prdemo
edit soundrec.m:
change
      '[ref1,Fsr1]=wavread([cpath,''\love_ref.wav'']);',...
      '[ref2,Fsr2]=wavread([cpath,''\kiss_ref.wav'']);',...
at line 384, 385 to
      '[ref1,Fsr1]=wavread(''love_ref.wav'');',...
      '[ref2,Fsr2]=wavread(''kiss_ref.wav'');',...




