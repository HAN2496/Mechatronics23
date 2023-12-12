clear;clc;
timeStep = 0.001;

accelTime =10; % 가속구간 길이
targetX = 20;
targetY = 20;
targetV = 3;
targetVx = targetV / sqrt(targetX.^2 + targetY.^2) * targetX;
targetVy = targetV / sqrt(targetX.^2 + targetY.^2) * targetY;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV;

timeVec = (0:timeStep:totalTime)';
lenTimeVec = length(timeVec);

xVec = zeros(lenTimeVec, 1);
yVec = zeros(lenTimeVec, 1);
tmp = 0;
tmp2 = 0;
for idx=1:lenTimeVec
    t = timeVec(idx);
    if t <= accelTime/pi * (acos(2/pi) + pi/2)
        xVec(idx) = sineProfile(targetVx, accelTime, t, 0);
        yVec(idx) = xVec(idx) * targetVy/targetVx;
        tmp = xVec(idx);
        tmp2 = idx;
    else
        xVec(idx) = tmp + targetX/lenTimeVec * (idx-tmp2);
        yVec(idx) = xVec(idx) * targetVy/targetVx;
    end
end

timeVecSec = seconds(timeVec);
xInput = timetable(timeVecSec, xVec);
yInput = timetable(timeVecSec, yVec);

plot(timeVec, xVec)


title('Problem 3-1 (Not considering paths) ');
xlabel('X position');
ylabel('Y position');