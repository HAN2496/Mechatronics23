function y = cubicProfile(a, t0, t)
    y = - a / t0 / t0 * t.^3 + 2 * a / t0 * t.^2;
end

