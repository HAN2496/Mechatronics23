clear;clc;
timeStep = 0.001;

accelTime =4; % 가속구간 길이
targetX = 20;
targetY = 20;
targetV = 5;
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
a=accelTime;
for idx=1:lenTimeVec
    t = timeVec(idx);
    if t <= accelTime
        xVec(idx) = sigmoidProfile(targetVx, accelTime, t);
        yVec(idx) = xVec(idx) * targetVy/targetVx;
        tmp = xVec(idx);
        tmp2 = idx;
    else
        xVec(idx) = tmp + targetX/lenTimeVec * (idx-tmp2);
        yVec(idx) = xVec(idx) * targetVy/targetVx;
    end
end

vxVec = zeros(lenTimeVec, 1);
vyVec = zeros(lenTimeVec, 1);
for idx = 2: lenTimeVec
    vxVec(idx) = (xVec(idx) - xVec(idx-1)) /  timeStep;
    vyVec(idx) = (yVec(idx) - yVec(idx-1)) / timeStep;
end

timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

plot(timeVec, xVec)


subplot(3,2,[1 2])
plot(xVec, yVec, 'LineWidth', 4)
title('Problem 3-1 Position (Sigmoid)');
xlabel('X position (mm)');
ylabel('Y position (mm)');

subplot(3,2,3)
plot(timeVec, xVec, 'LineWidth', 4)
title('Problem 3-1 Position (t - x)');
xlabel('t (sec)');
ylabel('X position (mm)');

subplot(3,2,4)
plot(timeVec, vxVec, 'LineWidth', 4)
title('Problem 3-1 Velocity (t - v_x)');
xlabel('t (sec)');
ylabel('X velocity(mm/sec)');

subplot(3, 2,5)
plot(timeVec, yVec, 'LineWidth', 4)
title('Problem 3-1 Position (t - y)');
xlabel('t (sec)');
ylabel('Y position (mm)');

subplot(3,2,6)
plot(timeVec, vyVec, 'LineWidth', 4)
title('Problem 3-1 Velocity (t - v_y)');
xlabel('t (sec)');
ylabel('Y velocity (mm/sec)');