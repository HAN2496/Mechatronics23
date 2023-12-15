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
totalTime = tagetDist / targetV;

timeVec = (0:timeStep:totalTime)';
lenTimeVec = length(timeVec);

xVec1 = zeros(lenTimeVec, 1);
yVec1 = zeros(lenTimeVec, 1);

tmp = 0;
tmp2 = 0;
for idx=1:lenTimeVec-1
    t = timeVec(idx);
    if t <= accelTime
        xVec1(idx) = sineProfile(targetVx, accelTime, t);
        yVec1(idx) = xVec1(idx) * targetVy/targetVx;
        tmp = xVec1(idx);
        tmp2 = idx;
    elseif t >= totalTime - accelTime
        xVec1(idx) = - sineProfile(targetVx, accelTime, totalTime - t) + targetX;
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
totalTime = tagetDist / targetV;

timeVec = (0:timeStep:totalTime)';
lenTimeVec = length(timeVec);

xVec2 = zeros(lenTimeVec, 1);
yVec2 = zeros(lenTimeVec, 1);

tmp = 0;
tmp2 = 0;
for idx=1:lenTimeVec-1
    t = timeVec(idx);
    if t <= accelTime
        xVec2(idx) = sineProfile(targetVx, accelTime, t) + x1;
        yVec2(idx) = (xVec2(idx)-x1) * targetVy/targetVx + y1;
        tmp = xVec2(idx);
        tmp2 = idx;
    elseif t >= totalTime - accelTime
        xVec2(idx) = - sineProfile(targetVx, accelTime, totalTime - t) + targetX + x1;
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
positionProfileX = [xVec1; xVec2; xVec3];
positionProfileY = [yVec1; yVec2; yVec3];

positionProfileX(end+1:end+1000) = zeros(1000,1);   % 이동후 1초간 위치 (0, 0)
positionProfileY(end+1:end+1000) = zeros(1000,1);   %

time_all = 0:0.001:(length(positionProfileX)-1)/1000;
time_all = time_all';
time_all = seconds(time_all);

xInput = timetable(time_all,positionProfileX);
yInput = timetable(time_all,positionProfileY);


%plot(time_all, positionProfileY)
%hold on;
%yline(y1)
%yline(y2)
%hold off;

plot(positionProfileX, positionProfileY)
hold on;
scatter(0, 0)
scatter(x1, y1)
scatter(x2, y2)
hold off;