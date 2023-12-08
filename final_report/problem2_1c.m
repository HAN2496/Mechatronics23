clear;clc;
time_step = 0.001;

divideInterval = 10;
targetX = 64;
targetY = 48;
tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / divideInterval * time_step;

timeVec = (0:time_step:totalTime)';
lenTimeVec = length(timeVec);

xVec = zeros(lenTimeVec, 1);
yVec = zeros(lenTimeVec, 1);

for idx=1:lenTimeVec
    xVec(idx) = targetX/lenTimeVec * idx;
    yVec(idx) = targetY/lenTimeVec * idx;
end

timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

scatter(xVec, yVec)

title('Problem 2-1 (Not considering paths) ');
xlabel('X position');
ylabel('Y position');