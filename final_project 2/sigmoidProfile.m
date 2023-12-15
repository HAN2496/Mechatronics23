function y = sigmoidProfile(vx, accelTime, t)
    A = accelTime;
    y = vx / (1 + exp(-10/A*(t-A)));
end

