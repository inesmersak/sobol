N = linspace(log(10),log(10000000),50);
N = unique(ceil(exp(N)));
N(end) = N(end) - 1;

% x+y
exact = 1;
filename = 'MonteCarlo_xplusy';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);
data = A(:,2:3);
data = abs(exact - data)/exact;
loglog(N',data(:,1),'o-b', N',data(:,2),'x-r')
grid on
title('Relative error of approximation for function x+y')
legend('quasi-random','pseudo-random')

% sin(10*x^2 (1 - y))
exact = 0.298379255422;
filename = 'MonteCarlo_sinxsq1-y';
A = importdata(filename,delimiterIn,headerlinesIn);
data = A(:,2:3);
data = abs(exact - data)/exact;
pause
clf
loglog(N',data(:,1),'o-b', N',data(:,2),'x-r')
grid on
title('Relative error of approximation for function sin(10*x^2 (1 - y))')
legend('quasi-random','pseudo-random')