clear;clc;
timeStep = 0.001;

accelTime =4; % 가속구간 길이

x1 = 20; y1 = 10;
x2 = 30; y2 = -10;
targetV = 3;


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
a=accelTime;
for idx=1:lenTimeVec
    t = timeVec(idx);
    if t <= a-a/10-log((5/a-targetVx+sqrt((targetVx-10/a)^2-targetVx^2))/targetVx)
        xVec1(idx) = sineProfile(targetVx, accelTime, t, 0);
        yVec1(idx) = xVec1(idx) * targetVy/targetVx;
        tmp = xVec1(idx);
        tmp2 = idx;
    else
        xVec1(idx) = tmp + targetX/lenTimeVec * (idx-tmp2);
        yVec1(idx) = xVec1(idx) * targetVy/targetVx;
    end
end

plot(xVec1, yVec1)

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
for idx=1:lenTimeVec
    t = timeVec(idx);
    if t <= a-a/10-log((5/a-targetVx+sqrt((targetVx-10/a)^2-targetVx^2))/targetVx)
        xVec2(idx) =    sineProfile(targetVx, accelTime, t, x1);
        yVec2(idx) = y1 + xVec2(idx) * targetVy/targetVx;
        tmp = xVec2(idx);
        tmp2 = idx;
    else
        xVec2(idx) = x1 + tmp + targetX/lenTimeVec * (idx-tmp2);
        yVec2(idx) = y1 + xVec2(idx) * targetVy/targetVx;
    end
end

hold on;
plot(xVec2, yVec2)
hold off;

%세 번째 (원파트)
x0 = x2; y0 = y2; %현재위치
x1 = 0; y1 = 0; %목표위치
x_r = (x0+x1)/2;
y_r = (y0+y1)/2;

r = sqrt((x0-x1)^2+(y0-y1)^2)/2;
path_len = pi*r;
t0 = path_len/targetV;
theta = atan((y0-y1)/(x0-x1));

t = (0:0.001:t0)';
time_len = length(t);
velocityProfile3=zeros(time_len ,2);

for idx = 1:time_len
    velocityProfile3(idx, 1) = x_r+ r * cos(theta - t(idx) * pi / t0);
    velocityProfile3(idx, 2) = y_r+ r * sin(theta - t(idx) * pi / t0);
end


t = (0:0.001:t0+0.5)';
tsec = seconds(t);





positionProfileX = [xVec1; xVec2; velocityProfile3(:, 1)];
positionProfileY = [yVec1; yVec2; velocityProfile3(:, 2)];

positionProfileX(end+1:end+1000) = zeros(1000,1);   % 이동후 1초간 위치 (0, 0)
positionProfileY(end+1:end+1000) = zeros(1000,1);   %

time_all = 0:0.001:(length(positionProfileX)-1)/1000;
time_all = time_all';
time_all = seconds(time_all);

xInput = timetable(time_all,positionProfileX);
yInput = timetable(time_all,positionProfileY);




%plot(positionProfileX, positionProfileY)
