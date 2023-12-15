time_step = 0.001;

targetX = 64;
targetY = 48;
targetV = 5;

xdata = xpos;
ydata = ypos;
timeData = timeVec;
lenTimeData = length(timeData);
xData = xdata;
yData = ydata;

tagetDist = sqrt(targetX.^2 + targetY.^2);

errorVec = zeros(lenTimeVec, 1);
vVec = zeros(lenTimeVec, 1);

for idx=1:lenTimeData

    %오차 계산
    slope = targetY/targetX;
    dist = abs(slope * xData(idx) - yData(idx)) / sqrt(slope.^2+1);
    errorVec(idx) = dist; 
    % 속도 계산
    if idx <=20
        vVec(idx) = 0; % 초기속도
    else
        distance = sqrt((xData(idx) - xData(idx-20))^2 + (yData(idx) - yData(idx-20))^2);
        vVec(idx) = distance / (time_step*20);
    end

end

timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

subplot(4,1,1)
plot(timeVec, xpos)
title('Problem 2-3');
xlabel('time');
ylabel('X position');

subplot(4,1,2)
plot(timeVec, ypos)
xlabel('time');
ylabel('Y position');

subplot(4,1,3)
plot(timeVec, errorVec)
xlabel('time');
ylabel('Error');

subplot(4,1,4)
plot(timeVec, vVec)
xlabel('time');
ylabel('Velocity');
