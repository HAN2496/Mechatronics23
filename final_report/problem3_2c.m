clear;clc;
time_step = 0.001;

targetX = 64;
targetY = 48;
targetV = 5;

xdata = xpos;
ydata = ypos;
timeData = xdata.Time;
lenTimeData = length(timeData);
xData = xdata.Data;
yData = ydata.Data;

tagetDist = sqrt(targetX.^2 + targetY.^2);

errorVec = zeros(lenTimeVec, 1);
vVec = zeros(lenTimeVec, 1);

for idx=1:lenTimeData

    %오차 계산
    slope = targetY/targetX;
    dist = abs(slope * xData(idx) - yData(idx)) / sqrt(slope.^2+1);
    errorVec(idx) = dist; 
    % 속도 계산
    if idx == 1
        vVec(idx) = 0; % 초기속도
    else
        distance = sqrt((xData(idx) - yData(idx-1))^2 + (xData(idx) - yData(idx-1))^2);
        vVec(idx) = distance / time_step;
    end

end

timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

subplot(411)
plot(timeVec, xVec)
subplot(412)
plot(timeVec, yVec)
subplot(421)
plot(timeVec, errorVec)
subplot(422)
plot(timeVec, vVec)

title('Problem 2-3');
xlabel('X position');
ylabel('Y position');