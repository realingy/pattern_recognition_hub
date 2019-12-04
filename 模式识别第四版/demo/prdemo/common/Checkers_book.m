function [plithos,metrisis] = Checkers(d, m, n, cells_per_dim, range, dist, r_seed, r_state)
%creates samples (2 classes 1 and -1) randomly
%samples are column vectors
%INPUT
% d : dimension of feature space
% m : num of points of A class (default = 20)
% n : num of points of B class (default = 20)
% cells_per_dim : number of different areas (cells) per side (dimension)
% range : range of feature values, assuming 0 the centre of values (default = 200)
%           range shrinks (or expands) according to dist
% dist : distance of classes (convex hulls) (default = 0.01). If negative, classes intersect.
% r_seed : integer to be the random seed. 0=reset to initial (see matlab
%          help), Missing (=default) -> set randomly by clock function,
%          -1=set rand 'state' to r_state vector supplied
%OUTPUT
% X : matrix of samples (m+n rows (samples) of d columns (attributes))
% Y : column-array of (m+n) rows, each row representing the class-value (-1 or 1) for the corresponding sample

%Algorithm :
%1. Use 2 different random number sequences:
%      One for finding a point (at a time) in the range of one (d-dimensional) cell
%      and a second for findind (for each point) the cell number (coefficient) in each dimension
%2. We assume that all points in the cell (1,1,1,...,1) belongs to class -1,
%      all points in the cell (1,1,1,...,2) belongs to class 1, etc
%      Generally, if address of cell (i.e. (1,1,1,...,1) has sum of coefficients S, we have
%        i.   if d is odd and S is odd then cell points belong to class -1
%        ii.  if d is odd and S is even then cell points belong to class 1
%        iii. if d is even and S is odd then cell points belong to class 1
%        iv.  if d is even and S is even then cell points belong to class -1
% 

rs = rand('state'); %get state of random-num generator, to restore it on return
if (nargin < 1)
    error('at least one argument must be supplied')
end
if (nargin < 7)
    rand('state', sum(100*clock)); %set random seed to random num generator (default)
elseif r_seed(1,1)>=0 %rest random state to initial
    rand('state', floor(r_seed(1,1)));
elseif r_seed(1,1)==-1 && nargin>=7
    rand('state', r_state);
else
    error('r_seed must be a non-negative integer or -1');
end
if (nargin < 6)
    dist = 0.01;
end
if (nargin < 5)
    range = 2;
end
if (nargin < 4)
    cells_per_dim = 2;
end
if (nargin < 3)
    n = 20;
end
if (nargin < 2)
    m = 20;
end
if (nargin < 1 || d < 1)
    error('dimension of input space should be at least 1')
end

X=zeros((m+n),d);
Y=zeros((m+n),1);

max_steps = 20 * d * (m+n); %max allowed steps to perform
step = 1;
fail = 0;

halfRange = range / 2.0;
halfDist = dist / 2.0;
%odd = mod(cells_per_dim, 2); %find if cells per_dim is odd or even
cell_width = range / cells_per_dim; %total width of each cell
cell_net_width = cell_width - dist; %cell width within samples reside - if dist negative we have class ovelapping

i = 0; %counter of samples for class -1
j = 0; %counter of samples for class 1
while (i < m || j < n)
    step = step + 1;
    if (step > max_steps)
        fail = 1;
        break;
    end
    %find point in a cell, and cell address
    %1-st row represents point coordinates in a cell
    %2-nd row represents cell address (cell coordinates)
    v = rand([2 d]); %random numbers are in [0,1]
    v(1,:) = v(1,:) .* cell_net_width; %extend [0,1]^d to take all net space of a cell
    v(2,:) = (v(2,:) .* cells_per_dim) - 0.5; %extend [0,1]^d to take all cell addresses
    v(2,:) = round(v(2,:)) + 1; %normalize cell addresses (make the integers, starting form 1 
    v(1,:) = v(1,:) + halfDist + ((v(2,:) - 1) .* cell_width); %find absolute coordinates for the point
    v(1,:) = v(1,:) - halfRange; %translate centre of cube to coinside to axes-origin
    %find class value
    s = sum(v(2,:));
    s_odd = mod(s, 2);
    d_odd = mod(d,2);
    s_d_odd = mod(s_odd+d_odd, 2);
    if (s_d_odd == 1)
        c = 1; %class = 1
    else
        c = -1; %class = -1
    end
    if (c == -1 && i < m)
        i = i + 1;
    elseif (c == 1 && j < n)
        j = j + 1;
    else
        continue;
    end
    X(i+j,:) = v(1,:);
    Y(i+j) = c;
 
end
ione=find(Y==1);
  x1=X(ione,:);
  i_minus_one=find(Y==-1);
  x2=X(i_minus_one,:);
  plithos=length(X(:,1));
  metrisis=[x1;x2]';
  
  hold off
  plot(x1(:,1),x1(:,2),'r+')
  hold on
  plot(x2(:,1),x2(:,2),'bx')
  axis([-1 1 -1 1]);