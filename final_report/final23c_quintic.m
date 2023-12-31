clear;clc;
timeStep = 0.001;

accelTime = 1; % 가속구간 길이

x1 = 64; y1 =48;
x2 = 40; y2 = -20;
targetV = 5;


%첫 번째
delX = x1;
delY = y1;


targetX = delX;
targetY = delY;
targetVx = targetV / sqrt(targetX.^2 + targetY.^2) * targetX;
targetVy = targetV / sqrt(targetX.^2 + targetY.^2) * targetY;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime1 = tagetDist / targetV;
decelTime1 = totalTime1 - accelTime;
timeVec = (0:timeStep:totalTime1)';
lenTimeVec = length(timeVec);

xVec1 = zeros(lenTimeVec, 1);
yVec1 = zeros(lenTimeVec, 1);

tmp = 0;
tmp2 = 0;
for idx=1:lenTimeVec-1
    t = timeVec(idx);
    if t <= accelTime
        xVec1(idx) = quinticProfile(targetVx, accelTime, t);
        yVec1(idx) = xVec1(idx) * targetVy/targetVx;
        tmp = xVec1(idx);
        tmp2 = idx;
    elseif t >= decelTime1
        xVec1(idx) = - quinticProfile(targetVx, accelTime, totalTime1 - t) + targetX;
        yVec1(idx) = xVec1(idx) * targetVy/targetVx;
    else
        xVec1(idx) = tmp + targetX/lenTimeVec * (idx-tmp2);
        yVec1(idx) = xVec1(idx) * targetVy/targetVx;
    end

end
xVec1(lenTimeVec) = targetX;
yVec1(lenTimeVec) = targetY;

%두 번째
delX = x2 - x1;
delY= y2 - y1;


targetX = delX;
targetY = delY;
targetVx = targetV / sqrt(targetX.^2 + targetY.^2) * targetX;
targetVy = targetV / sqrt(targetX.^2 + targetY.^2) * targetY;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime2 = tagetDist / targetV;
decelTime2 = totalTime2 - accelTime;
timeVec = (0:timeStep:totalTime2)';
lenTimeVec = length(timeVec);

xVec2 = zeros(lenTimeVec, 1);
yVec2 = zeros(lenTimeVec, 1);

tmp = 0;
tmp2 = 0;
for idx=1:lenTimeVec-1
    t = timeVec(idx);
    if t <= accelTime
        xVec2(idx) = quinticProfile(targetVx, accelTime, t) + x1;
        yVec2(idx) = (xVec2(idx)-x1) * targetVy/targetVx + y1;
        tmp = xVec2(idx);
        tmp2 = idx;
    elseif t >= decelTime2
        xVec2(idx) = - quinticProfile(targetVx, accelTime, totalTime2 - t) + targetX + x1;
        yVec2(idx) = (xVec2(idx)-x1) * targetVy/targetVx + y1;
    else
        xVec2(idx) = tmp + targetX/lenTimeVec * (idx-tmp2);
        yVec2(idx) = (xVec2(idx)-x1) * targetVy/targetVx + y1;
    end

end
xVec2(lenTimeVec) = x2;
yVec2(lenTimeVec) = y2;


%세 번째 (원파트)
x0 = x2; y0 = y2; %현재위치
x_r = x0/2;
y_r = y0/2;

r = sqrt(x0^2+y0^2)/2;
path_len = pi*r;
t0 = path_len/targetV;
theta = atan(y0/x0);

timeVec = (0:0.001:t0)';
lenTimeVec = length(timeVec);

xVec3 = zeros(lenTimeVec, 1);
yVec3 = zeros(lenTimeVec, 1);

for idx = 1:lenTimeVec
    t = timeVec(idx);
    xVec3(idx) = x_r+ r * cos(theta - t * pi / t0);
    yVec3(idx) = y_r+ r * sin(theta - t * pi / t0);
end


t = (0:0.001:t0+0.5)';
tsec = seconds(t);
xVec = [xVec1; xVec2; xVec3];
yVec = [yVec1; yVec2; yVec3];

xVec(end+1:end+1000) = zeros(1000,1);   % 이동후 1초간 위치 (0, 0)
yVec(end+1:end+1000) = zeros(1000,1);   %

timeVec = 0:0.001:(length(xVec)-1)/1000;
timeVec = timeVec';
lenTimeVec = length(timeVec);

timeSec = seconds(timeVec);

xInput = timetable(timeSec,xVec);
yInput = timetable(timeSec,yVec);


vxVec(lenTimeVec) = targetX;
vyVec(lenTimeVec) = targetY;

for idx = 2: lenTimeVec
    vxVec(idx) = (xVec(idx) - xVec(idx-1)) /  timeStep;
    vyVec(idx) = (yVec(idx) - yVec(idx-1)) / timeStep;
    if timeVec(idx) == decelTime1
        vxVec(idx) = vxVec(idx-1);
        vyVec(idx) = vyVec(idx-1);
    elseif idx == 29425
        timeVec(idx)
        vxVec(idx) = vxVec(idx-1);
        vyVec(idx) = vyVec(idx-1);
    end
end
%{
subplot(3,2,[1 2])
plot(xVec, yVec, 'LineWidth', 4)
hold on;
scatter(x1, y1, 100)
scatter(x2, y2, 100)
scatter(0, 0, 100)
hold off;
title('Problem 4 Position (x-y)');
xlabel('X position (mm)');
ylabel('Y position (mm)');

subplot(3,2,3)
plot(timeVec, xVec, 'LineWidth', 4)
title('Problem 4 Position (t - x)');
xlabel('t (sec)');
ylabel('X position (mm)');

subplot(3,2,4)
plot(timeVec, vxVec, 'LineWidth', 4)
title('Problem 4 Velocity (t - v_x)');
xlabel('t (sec)');
ylabel('X velocity(mm/sec)');

subplot(3, 2,5)
plot(timeVec, yVec, 'LineWidth', 4)
title('Problem 4 Position (t - y)');
xlabel('t (sec)');
ylabel('Y position (mm)');

subplot(3,2,6)
plot(timeVec, vyVec, 'LineWidth', 4)
title('Problem 4 Velocity (t - v_y)');
xlabel('t (sec)');
ylabel('Y velocity (mm/sec)');
%}
plot(timeVec, vyVec, 'LineWidth', 4)
hold on;
plot(timeVec, yVec, 'LineWidth', 4)
hold off
title('Problem 4 Velocity (t - v_y)');
xlabel('t (sec)');
ylabel('Y velocity (mm/sec)');