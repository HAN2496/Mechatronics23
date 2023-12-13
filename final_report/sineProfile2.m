function y = sineProfile2(vx, accelTime, t)
    b = vx * accelTime;
    y = b / 2 * sin (pi * t / accelTime - pi / 2) + b / 2;
end

