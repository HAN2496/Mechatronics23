function  y=quinticDervProfile(vTarget,t0,t) 
a = 3 * vTarget / t0.^4;
b = - 8 * vTarget / t0.^3;
c = 6 * vTarget / t0.^2;
y = 5 * a * t.^4 + 4 * b * t.^3 + 3 * c * t.^2;
end