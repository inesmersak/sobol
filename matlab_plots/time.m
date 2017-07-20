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

filename = 'time_4d_100mil_nogray';
A = importdata(filename,delimiterIn,headerlinesIn);
data_ng = A(:,2);

loglog(N',data,'o-b', N',data_ng,'g-x', N',linfun(N'),'r--')
grid on
title('Time needed for generation of 4-dimensional vectors')
xlabel('Number of vectors')
ylabel('Time in seconds')
legend('using gray code', 'not using gray code', 'trend line for gray code, coefficient 0.8721')
legend('Location','northwest')
