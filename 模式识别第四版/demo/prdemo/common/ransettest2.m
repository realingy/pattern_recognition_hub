function [plithos,metrisis]=pl(center1,center2,p);
global metrisis plithos;




x1=randn(p,2)*0.5;
x2=randn(p,2)*0.5;


testset1=[(x1(:,1)+center1) (x1(:,2)+2)];
plot(testset1(:,1),testset1(:,2),'rx');
maxx1=max([testset1(:,1)]);
minx1=min([testset1(:,1)]);
maxy1=max([testset1(:,2)]);
miny1=min([testset1(:,2)]);




testset2=[(x2(:,1)+center2) (x2(:,2)+2)];
hold on
plot(testset2(:,1),testset2(:,2),'bx');

grid
maxx1=max([testset1(:,1)]);
minx1=min([testset1(:,1)]);
maxy1=max([testset1(:,2)]);
miny1=min([testset1(:,2)]);

maxx2=max([testset2(:,1)]);
minx2=min([testset2(:,1)]);
maxy2=max([testset2(:,2)]);
miny2=min([testset2(:,2)]);




maxx=max(maxx1, maxx2);
minx=min(minx1, minx2);
maxy=max(maxy1, maxy2);
miny=min(miny1, miny2);




axis([minx-0.5 maxx+0.5 miny-0.5 maxy+0.5]);
hold off;
 
metrisis=[testset1',testset2'];