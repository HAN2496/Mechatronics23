clear;clc;
timeStep = 0.001;

divideInterval = 10;
targetX = 64;
targetY = 48;
tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / divideInterval * timeStep;

timeVec = (0:timeStep:totalTime)';
lenTimeVec = length(timeVec)-1;

xVec = zeros(lenTimeVec+1, 1);
yVec = zeros(lenTimeVec+1, 1);

for idx=1:lenTimeVec+1
    xVec(idx) = targetX/lenTimeVec * (idx-1);
    yVec(idx) = targetY/lenTimeVec * (idx-1);
end

timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

scatter(xVec, yVec)

title('Problem 2-1 (Not considering paths) ');
xlabel('X position');
ylabel('Y position');