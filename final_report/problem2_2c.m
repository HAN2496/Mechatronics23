clear;clc;
time_step = 0.001;

targetX = 64;
targetY = 48;
targetV = 5;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV;

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

title('Problem 2-2');
xlabel('X position');
ylabel('Y position');