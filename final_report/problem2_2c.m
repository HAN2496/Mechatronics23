clear;clc;
time_step = 0.001;

targetX = 64;
targetY = 48;
targetV = 5;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV;

timeVec = (0:time_step:totalTime)';
lenTimeVec = length(timeVec)-1;

xVec = zeros(lenTimeVec+1, 1);
yVec = zeros(lenTimeVec+1, 1);

for idx=1:lenTimeVec+1
    xVec(idx) = targetX/lenTimeVec * (idx-1);
    yVec(idx) = targetY/lenTimeVec * (idx-1);
end

xVec(idx+1:idx+1000)=targetX*ones(1000,1); % 1초씩 더들어감 (발산 방지)
yVec(idx+1:idx+1000)=targetY*ones(1000,1);

timeVec = (0:time_step:totalTime+1)';   % 1초 추가

size(xVec)
timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

subplot(3,1,1)
scatter(xVec, yVec)
hold on;
plot(xVec, yVec)
hold off;
title('Problem 2-2 (velocity)');
xlabel('X position (mm)');
ylabel('Y position (mm)');

subplot(3,1,2)
scatter(timeVec, xVec)
hold on;
plot(timeVec, xVec)
hold off;
title('Problem 2-2 (t - x)');
xlabel('t (sec)');
ylabel('X position (mm)');

subplot(3,1, 3)
scatter(timeVec, yVec)
hold on;
plot(timeVec, yVec)
hold off;
title('Problem 2-2 (t - y)');
xlabel('time (sec)');
ylabel('Y position (mm)');