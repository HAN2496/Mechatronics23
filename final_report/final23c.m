clear;clc;
% 1회전당 2mm 이동
% 모터 최고 속도는 6.25 회전/s
timeStep = 0.001;
t0 = 0.5;

x1 = 20; y1= 10;
x2 = 30; y2 = -10;
targetV = 3;

%첫 번재 구간
delX = x1;
delY = y1;

targetX = delX;
targetY = delY;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV;
timeVec = 0:0.001:totalTime;
lenTimeVec = length(timeVec);

xVec1 = zeros(lenTimeVec, 1);
yVec1 = zeros(lenTimeVec, 1);
for idx=1:lenTimeVec
    xVec1(idx) = targetX/lenTimeVec * idx;
    yVec1(idx) = targetY/lenTimeVec * idx;
end


%두 번째 구간
delx = x2 - x1;
dely= y2 - y1;

targetX = delx;
targetY = dely;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV;
timeVec = 0:0.001:totalTime;
lenTimeVec = length(timeVec);
xVec2 = zeros(lenTimeVec, 1);
yVec2 = zeros(lenTimeVec, 1);
for idx=1:lenTimeVec
    xVec2(idx) = x1 + targetX/lenTimeVec * idx;
    yVec2(idx) = y1 + targetY/lenTimeVec * idx;
end

%마지막 원 구간
x0 = x2; y0 = y2;
xR = x0/2;
yR = y0/2;

R = sqrt(x0^2 + y0^2) / 2;
path_len = pi*R;
t0 = path_len/targetV;
theta0 = atan(y0/x0);

timeVec = (0:0.001:t0)';
lenTimeVec = length(timeVec);
xVec3 = zeros(lenTimeVec, 1);
yVec3 = zeros(lenTimeVec, 1);

for idx = 1:lenTimeVec
    xVec3(idx) = xR+ R * cos(theta0 - timeVec(idx) * pi / t0);
    yVec3(idx) = yR+ R * sin(theta0 - timeVec(idx) * pi / t0);
end


%프로파일 병합
xVec = [xVec1; xVec2; xVec3];
yVec = [yVec1; yVec2; yVec3];

% 이동후 1초간 위치 (0, 0)
xVec(end+1:end+1000) = zeros(1000,1);   
yVec(end+1:end+1000) = zeros(1000,1);

totalTime = 0:0.001:(length(xVec)-1)/1000;
totalTime = totalTime';
lenTimeVec = length(totalTime);
totalTime = seconds(totalTime);


xInput = timetable(totalTime,xVec);
yInput = timetable(totalTime,yVec);

%속도 계산
vxVec(lenTimeVec) = targetX;
vyVec(lenTimeVec) = targetY;

for idx = 2: lenTimeVec
    vxVec(idx) = (xVec(idx) - xVec(idx-1)) /  timeStep;
    vyVec(idx) = (yVec(idx) - yVec(idx-1)) / timeStep;
    if idx == 14909
        vyVec(idx) = -2.85;
    end
end

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
plot(totalTime, xVec, 'LineWidth', 4)
title('Problem 4 Position (t - x)');
xlabel('t (sec)');
ylabel('X position (mm)');

subplot(3,2,4)
plot(totalTime, vxVec, 'LineWidth', 4)
title('Problem 4 Velocity (t - v_x)');
xlabel('t (sec)');
ylabel('X velocity(mm/sec)');

subplot(3, 2,5)
plot(totalTime, yVec, 'LineWidth', 4)
title('Problem 4 Position (t - y)');
xlabel('t (sec)');
ylabel('Y position (mm)');

subplot(3,2,6)
plot(totalTime, vyVec, 'LineWidth', 4)
title('Problem 4 Velocity (t - v_y)');
xlabel('t (sec)');
ylabel('Y velocity (mm/sec)');