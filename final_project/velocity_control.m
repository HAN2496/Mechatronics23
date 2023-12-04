delt = 0.001;
x1=10;
vtarget=1;
t0 = 5;

sum_term = 0;
for i=1:delt:t0
    sum_term = sum_term + sineprofile(vtarget, t0, i) * delt;
end
t1 = (x1 - sum_term) / vtarget + 2 * t0;

time_index = 0:0.001:t1;
accel_len = t0 * 1000 + 1;
time_len = length(time_index)
velocity_profile=zeros(time_len ,1);


for idx=1:time_len
    t = time_index(idx);
    if idx <= accel_len
        velocity_profile(idx) = sineprofile(vtarget, t0, t);
    elseif idx <= time_len - accel_len
        velocity_profile(idx) = vtarget;
    else
        velocity_profile(idx) = sineprofile(vtarget, t0, t1-t);
    end
end

plot(time_index, velocity_profile)

