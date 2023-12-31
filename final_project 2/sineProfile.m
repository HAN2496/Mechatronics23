function y = sineProfile(vx, accelTime, t, x0, y0)
    A = vx*accelTime/2;
    B = accelTime/pi;
    y = A * sin(t / B - pi/2) + A;
end

