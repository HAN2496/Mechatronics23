function y = sineProfile(vx, accelTime, t)
    A = vx*accelTime/1.68915773;
    B = accelTime*1.34767385/pi;
    y = A * sin(t / B - pi/2) + A;
end

