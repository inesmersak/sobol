N = linspace(log(100),log(100000000),50);
N = unique(ceil(exp(N)));
N(end) = N(end) - 1;

filename = 'time_4d_100mil';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);
data = A(:,2);
fit = polyfit(log(N'),log(data),1);
linfun = @(x) exp(fit(2)) * x.^fit(1);

loglog(N',data,'o-b',N',linfun(N'),'r')
grid on
title('Time needed for generation of 4-dimensional vectors')
legend('time measured in seconds','fitted linear func, coefficient 0.8721')
legend('Location','northwest')
