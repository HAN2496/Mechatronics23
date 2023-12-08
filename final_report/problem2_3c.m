clear;clc;
time_step = 0.001;

xdata = xpos;
timeData = xdata.Time;
xposData = xdata.Data;

ydata = ypos;
timeData = ydata.Time;
yposData = ydata.Data;

targetX = 64;
targetY = 48;
targetV = 5;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV * time_step;

timeVec = (0:time_step:totalTime)';
lenTimeVec = length(timeVec);

xVec = zeros(lenTimeVec, 1);
yVec = zeros(lenTimeVec, 1);
errorVec = zeros(lenTimeVec, 1);
vVec = zeros(lenTimeVec, 1);

for idx=1:lenTimeVec
    xVec(idx) = targetX/lenTimeVec * idx;
    yVec(idx) = targetY/lenTimeVec * idx;
    
    %오차 계산
    pointVec = [xVec(idx), yVec(idx), 0];
    targetVec = [targetX, targetY, 0];
    crossProd = cross(pointVec, targetVec);
    errorVec(idx) = norm(crossProd) / norm(targetVec); 
    % 속도 계산
    if idx == 1
        vVec(idx) = 0; % 초기속도
    else
        distance = sqrt((xVec(idx) - xVec(idx-1))^2 + (yVec(idx) - yVec(idx-1))^2);
        vVec(idx) = distance / time_step;
    end

end

timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

plot(timeVec, xVec)
plot(timeVec, yVec)
plot(timeVec, errorVec)
plot(timeVec, vVec)

title('Problem 2-1 (Not considering paths) ');
xlabel('X position');
ylabel('Y position');