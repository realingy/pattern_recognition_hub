function [plithos,metrisis]=pl(sx1,sy1,sxy1,sx2,sy2,sxy2,p);
global metrisis plithos;



Center_1_x=0.5;
Center_1_y=-0.5;
x=randn(p,1);
y=randn(p,1);
Centerposition1=[ones(p,1)*Center_1_x  ones(p,1)*Center_1_y];
testset1=[x y]*[sx1 sxy1;sxy1 sy1]+Centerposition1;
plot(testset1(:,1),testset1(:,2),'r+');
maxx1=max([testset1(:,1)]);
minx1=min([testset1(:,1)]);
maxy1=max([testset1(:,2)]);
miny1=min([testset1(:,2)]);




Center_2_x=-0.5;
Center_2_y=0.5;
x=randn(p,1);
y=randn(p,1);
Centerposition2=[ones(p,1)*Center_2_x ones(p,1)*Center_2_y];
testset2=[x y]*[sx2 sxy2;sxy2 sy2]+Centerposition2;
maxx2=max([testset2(:,1)]);
minx2=min([testset2(:,1)]);
maxy2=max([testset2(:,2)]);
miny2=min([testset2(:,2)]);

maxx=max(maxx1, maxx2);
minx=min(minx1, minx2);
maxy=max(maxy1, maxy2);
miny=min(miny1, miny2);

hold on
plot(testset2(:,1),testset2(:,2),'b+');

grid
axis([minx-0.5 maxx+0.5 miny-0.5 maxy+0.5]);
hold off;
 
metrisis=[testset1',testset2'];