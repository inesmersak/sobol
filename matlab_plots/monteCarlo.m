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
fitq = polyfit(log(N'),log(data(:,1)),1)
linfunq = @(x) exp(fitq(2)) * x.^fitq(1);
fitp = polyfit(log(N'),log(data(:,2)),1)
linfunp = @(x) exp(fitp(2)) * x.^fitp(1);

loglog(N',data(:,1),'o-b', N',linfunq(N'),'g--', N',data(:,2),'x-r', N',linfunp(N'),'m--')
grid on
title('Relative error of approximation for function x+y')
legend('quasi-random','trend line for quasi, coefficient -0.9170', 'pseudo-random', 'trend line for pseudo, coefficient -0.5130')

% sin(10*x^2 (1 - y))
exact = 0.298379255422;
filename = 'MonteCarlo_sinxsq1-y';
A = importdata(filename,delimiterIn,headerlinesIn);
data = A(:,2:3);
data = abs(exact - data)/exact;
fitq = polyfit(log(N'),log(data(:,1)),1);
linfunq = @(x) exp(fitq(2)) * x.^fitq(1);
fitp = polyfit(log(N'),log(data(:,2)),1);
linfunp = @(x) exp(fitp(2)) * x.^fitp(1);

pause
clf
loglog(N',data(:,1),'o-b', N',linfunq(N'),'g--', N',data(:,2),'x-r', N',linfunp(N'),'m--')
grid on
title('Relative error of approximation for function sin(10*x^2 (1 - y))')
legend('quasi-random','trend line for quasi, coefficient -0.9474', 'pseudo-random', 'trend line for pseudo, coefficient -0.5240');

