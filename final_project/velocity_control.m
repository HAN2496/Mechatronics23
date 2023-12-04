% 1회전당 2mm 이동
% 모터 최고 속도는 6.25 회전/s
timeStep = 0.001;
t0 = 5;

x1 = 1;
x2 = 6;
targetV = 3;

targetX = x1*2;
targetY = x2*2;
targetVx = targetX/sqrt(targetX.^2 + targetY.^2) * targetV;
targetVy = targetY/sqrt(targetX.^2 + targetY.^2) * targetV;


sum_term = 0;
for i=1:timeStep:t0
    sum_term = sum_term + sineprofile(targetVx, t0, i) * timeStep;
end
totalTime = (targetX - sum_term) / targetVx + 2 * t0;

timePoints = 0:0.001:totalTime;
accel_len = t0 * 1000 + 1;
time_len = length(timePoints)
velocityProfile=zeros(time_len ,2);


for idx=1:time_len
    t = timePoints(idx);
    if idx <= accel_len
        velocityProfile(idx, 1) = sineprofile(targetVx, t0, t);
        velocityProfile(idx, 2) = velocityProfile(idx, 1) * targetVy/targetVx;
    elseif idx <= time_len - accel_len
        velocityProfile(idx, 1) = targetVx;
        velocityProfile(idx, 2) = targetVy;
    else
        velocityProfile(idx, 1) = sineprofile(targetVx, t0, totalTime-t);
        velocityProfile(idx, 2) = velocityProfile(idx, 1) * targetVy/targetVx;
    end
end


% 데이터 확인용 플롯
plot(timePoints, velocityProfile(:, 1))
hold on
plot(timePoints, velocityProfile(:, 2))
