filename = '2dvectors';
delimiterIn = ' ';
headerlinesIn = 0;
A = importdata(filename,delimiterIn,headerlinesIn);

filename = 'web-version/out';
delimiterIn = ' ';
headerlinesIn = 0;
B = importdata(filename,delimiterIn,headerlinesIn);

C = rand(1000,2);

scatter(A(:,1),A(:,2))
title('My Sobol generator')
pause
clf
scatter(B(101:end,1),B(101:end,2))
title('Web Sobol generator')
pause
clf
scatter(C(:,1),C(:,2))
title('MATLAB pseudorandom')
