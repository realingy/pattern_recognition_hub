
function[]=linear_tester(X,Y,alpha,w,b,stp,max_step)
xmin=min(X(:,1));
xmax=max(X(:,1));
ymin=min(X(:,2));
ymax=max(X(:,2));
clear i_1
clear i_2


global figt4   
gcf=figure(figt4);
clf
set(figt4,...
    'numbertitle','off',...
    'menubar','none');
drawnow

hold on




    epsilon = 1e-5;  
      yaxis = 2;
    xaxis = 1;
    mag = 0.1;
    aspect = 0;
   





   for i = 1:size(Y)
        if (Y(i) == 1)
            plot(X(i,xaxis),X(i,yaxis),'r+','LineWidth',2) % Class A
        else
            plot(X(i,xaxis),X(i,yaxis),'b+','LineWidth',2) % Class B
        end
        if (abs(alpha(i)) > epsilon)
            plot(X(i,xaxis),X(i,yaxis),'ko') % Support Vector
        end
    end 
    

    
    
%wx-b=0
x1=xmin:((xmax-xmin)/10):xmax;
 for i=1:size(x1')
  x2(i)=(+b-w(1,1)*x1(i))/w(1,2);
end


 for i=1:size(x1')
  x3(i)=(1+b-w(1,1)*x1(i))/w(1,2);
end


 for i=1:size(x1')
  x4(i)=(-1+b-w(1,1)*x1(i))/w(1,2);
end
H3=plot(x1,x2,'k',x1,x3,'r',x1,x4,'b');
grid off
axis([xmin-0.5 xmax+0.5 ymin-0.5 ymax+0.5]);
% 
if stp>=max_step
    title('THE ALGORITHM DID NOT TERMINATED PROPERLY')
end
legend(H3,'wx+b=0','wx+b=+1','wx+b=-1');



 hold off