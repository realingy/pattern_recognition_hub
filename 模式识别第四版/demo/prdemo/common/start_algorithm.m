

X=metrisis';
Y=[ones(1,length(metrisis)/2) -1*ones(1,length(metrisis)/2)]';

i=randperm(length(X));
X=X(i,:);
Y=Y(i);



global regularisation_factor
global tol_constant
global method
global epsilon
global kernel

% switch kernel
%     case kernel==1
%         ker='linear';
%     case kernel==2
%         ker='rbf';
%     case kernel==3
%         ker='poly';
%     otherwise
%         ker='sigmoid';
% end

if kernel==1
    ker='linear';
end
if kernel==2
    ker='rbf';
end



% ALGORITHMOS SMO    
[alpha, b, w, evals, stp, glob]= SMO2(X, Y, ker, kernel_parameter_1, kernel_parameter_2, regularisation_factor,...
                                    tol_constant, max_step, epsilon, method);

%  if kernel==1
%      linear_tester(X,Y,alpha,w,b,stp,max_step);
%  else   
          svcplot_book(X,Y,ker,kernel_parameter_1,kernel_parameter_2,alpha,-b);
%  end