%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------

function [best_path,cost]=sakoe(N_type,col)

   %INITIALIZATION
   f=sqrt(-1);
   [J,I]=size(N_type);
   for j=1:3
      Dmin(j,1)=N_type(j,1);
      Y(j,1)=0+f*0;
   end;
   for j=4:J
      Dmin(j,1)=10000;
      Y(j,1)=0+f*0;
   end;
   %RECURSION
   for i=2:I
      for j=1:J
         if j>=3,
               [g,ind]=min([Dmin(j-1,i-1),Dmin(j,i-1),Dmin(j-1,i)]+N_type(j,i));
               Dmin(j,i)=g; 
               if ind==1 | ind==2
                  Y(j,i)=j-1+ind-1+f*(i-1);
               elseif ind==3
                  Y(j,i)=j-1+f*i;
               end
 	 else
               [g,ind]=min(Dmin(1:j,i-1)+N_type(j,i));
               Dmin(j,i)=g;
               Y(j,i)=ind+f*(i-1);
   	 end
      end
   end
   cost=Dmin(J,I);
   
   %BACK-TRACKING TO SCAN BEST PATH   
   k=1;
   best_path(1)=J+f*I;
   while (Y(real(best_path(k)),imag(best_path(k)))~=0)
      k=k+1;
      best_path(k)=Y(real(best_path(k-1)),imag(best_path(k-1)));
   end;
   best_path(k)=0+f*0;
   best_path=fliplr(best_path);
   cost=cost/length(best_path);
   plot(real(best_path),imag(best_path),col);
   %title('Best path provided by SCDP');
   xlabel('Test Template','fontsize',[8]);



