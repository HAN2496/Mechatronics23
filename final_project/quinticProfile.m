function  y=quinticProfile(vTarget,t0,t) 
a = 3 * vTarget / t0.^4;
b = - 8 * vTarget / t0.^3;
c = 6 * vTarget / t0.^2;
y = a * t.^5 + b * t.^4 + c * t.^3;
end