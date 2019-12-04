%							----------------------------------
%							|Copyright : Kopsinis Yannis     |
%							|            Pikrakis Aggelos    |
%							|            Basilas Stratos     |
%							|           -------------------- |
%							|           Dept. of Informatics |
%							|           University of Athens |
%							----------------------------------

function [best_path,cost]=itakura(N_type,col)
%SOLVES TYPE N PROBLEM , i.e COSTS ARE ASSIGNED TO THE NODES ONLY.
%MATRIX N_TYPE HOLDS THE COSTS ASSIGNED TO THE NODES.
%ALL PATHS ARE ASSUMED TO START AT NODE (0,0)
%MATRIX Y HOLDS THE PREDECESSOR TO EACH NODE. IT IS COMPLEX BECAUSE
%IT HAS TO STORE TWO INDEXES FOR EACH PREDECESSOR. THE REAL PART STORES
%THE ROW INDEX J, WHILE THE IMAGINARY PART STORES THE COLUMN INDEX I.

   %INITIALIZATION
   f=sqrt(-1);  
   [J,I]=size(N_type);

   %ALLOWABLE STARTING NODES
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
            if real(Y(j,i-1))<j,
               [g,ind]=min(Dmin(j-2:j,i-1)+N_type(j,i));
               Dmin(j,i)=g;
               Y(j,i)=j-2+ind-1+f*(i-1);
            elseif real(Y(j,i-1))==j,
               [g,ind]=min(Dmin(j-2:j-1,i-1)+N_type(j,i));
               Dmin(j,i)=g;
               Y(j,i)=j-2+ind-1+f*(i-1);
            end
	 % THE FIRST TWO ROWS HAVE TO BE TREATED SEPERATELY. 	    
         elseif j==2, % SECOND ROW
            if real(Y(j,i-1))<j,
 	       %21
               [g,ind]=min(Dmin(1:j,i-1)+N_type(j,i));
               Dmin(j,i)=g;
               Y(j,i)=ind+f*(i-1);
            elseif real(Y(j,i-1))==j,
               %22
               [g,ind]=min(Dmin(1:j-1,i-1)+N_type(j,i));
               Dmin(j,i)=g;
               Y(j,i)=1+f*(i-1);
            end
   	 elseif j==1,
            if real(Y(j,i-1))==0
               %11
               [g,ind]=min(Dmin(1:j,i-1)+N_type(j,i));
               Dmin(j,i)=g;
               Y(j,i)=j-ind+1+f*(i-1);       
               %[j,i,g,ind,Y(j,i)]
               %pause;
            elseif real(Y(j,i-1))==1,
   	       %22
               Dmin(j,i)=10000;
               Y(j,i)=1+f*(i-1);
               %[j,i,g,ind,Y(j,i)]
               %pause;
            end
         end
      end
   end
   cost=Dmin(J,I);
   
   %BACK TRACKING TO SCAN BEST PATH
   best_path(I+1)=J+f*I;
   for i=I:-1:2
      best_path(i)=Y(real(best_path(i+1)),imag(best_path(i+1)));
   end;
   best_path(1)=0;
   plot(real(best_path),imag(best_path),col);
   %title('Best path provided by DP');
   xlabel('Test Template','fontsize',[8]);
   cost=cost/length(best_path);


