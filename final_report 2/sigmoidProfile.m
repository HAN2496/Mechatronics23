function y = sigmoidProfile(vx, accelTime, t)
    k = 12.43683969;
    y = vx*accelTime*(1+exp(-k+10)) / (1 + exp(-k*t/accelTime+10));
end

