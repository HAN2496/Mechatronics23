clear;clc;
timeStep = 0.001;

divideDistance = 0.5 % 나누는 길이
targetX = 64;
targetY = 48;
tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / divideDistance * timeStep;

timeVec = (0:timeStep:totalTime)'; %시간 벡터
lenTimeVec = length(timeVec)-1;

xVec = zeros(lenTimeVec+1, 1);
yVec = zeros(lenTimeVec+1, 1);

for idx=1:lenTimeVec+1
    xVec(idx) = targetX/lenTimeVec * (idx-1);
    yVec(idx) = targetY/lenTimeVec * (idx-1);
end

timeVecSec = seconds(timeVec);
xInput = timetable(timeVecSec, xVec);
yInput = timetable(timeVecSec, yVec);

subplot(3,1,1)
scatter(xVec, yVec)
hold on;
plot(xVec, yVec)
hold off;
title('Problem 2-1 (Dividing n euqal parts) ');
xlabel('X position (mm)');
ylabel('Y position (mm)');

subplot(3,1,2)
scatter(timeVec, xVec)
hold on;
plot(timeVec, xVec)
hold off;
title('Problem 2-1 (t - x)');
xlabel('t (sec)');
ylabel('X position (mm)');

subplot(3,1, 3)
scatter(timeVec, yVec)
hold on;
plot(timeVec, yVec)
hold off;
title('Problem 2-1 (t - y)');
xlabel('time (sec)');
ylabel('Y position (mm)');

