% 1회전당 2mm 이동
% 모터 최고 속도는 6.25 회전/s
delt = 0.001;
t0 = 5;

xtarget = 1;
ytarget = 10;
vtarget = 3;

vxtarget=xtarget/sqrt(xtarget.^2 + ytarget.^2);
vytarget=ytarget/sqrt(xtarget.^2 + ytarget.^2);


sum_term = 0;
for i=1:delt:t0
    sum_term = sum_term + sineprofile(vxtarget, t0, i) * delt;
end
t1 = (xtarget - sum_term) / vxtarget + 2 * t0;

time_index = 0:0.001:t1;
accel_len = t0 * 1000 + 1;
time_len = length(time_index)
velocity_profile=zeros(time_len ,2);


for idx=1:time_len
    t = time_index(idx);
    if idx <= accel_len
        velocity_profile(idx, 1) = sineprofile(vxtarget, t0, t);
        velocity_profile(idx, 2) = velocity_profile(idx, 1) * vytarget/vxtarget;
    elseif idx <= time_len - accel_len
        velocity_profile(idx, 1) = vxtarget;
        velocity_profile(idx, 2) = vytarget;
    else
        velocity_profile(idx, 1) = sineprofile(vxtarget, t0, t1-t);
        velocity_profile(idx, 2) = velocity_profile(idx, 1) * vytarget/vxtarget;
    end
end


% 데이터 확인용 플롯
plot(time_index, velocity_profile(:, 1))
hold on
plot(time_index, velocity_profile(:, 2))
