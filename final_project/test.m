delt = 0.001
x1=10;
vtarget=1;
t0 = 4;


sum_term = 0;
for i=1:delt:t0
    sum_term = sum_term + accelprofile(vtarget, t0, i) * delt
end
t1 = (x1 - sum_term) / vtarget + 2 * t0

tmp1 = int16(t1/delt);
tmp2 = int16(t0/delt);

velocity_profile=zeros(tmp1 + 1 ,1);

for i=2:t0 / delt
    velocity_profile(i) = accelprofile(vtarget, t0, i * delt);
end
for i=t0/delt+1 : t1/delt-t0/delt+1
    velocity_profile(i) = vtarget;
end

for i=tmp1-tmp2+1:tmp1+1
    tmp3 = t1 - double(i) * delt;
    velocity_profile(i) = accelprofile(vtarget, t0, tmp3);
end

t = 0:0.001:t1;
size(t)
size(velocity_profile)
plot(t, velocity_profile)
