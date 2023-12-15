function  y=quadraticProfile(vTarget,t0,t) 
a = 6 * vTarget / 2 / t0.^4 - 2 * vTarget / t0.^2;
b = - vTarget / t0.^2 - 2 * a * t0;
c = 2 * vTarget / t0 + a * t0.^2;
y = a * t.^4 + b * t.^3 + c * t.^2;
end