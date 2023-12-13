clear;clc;
% 1회전당 2mm 이동
% 모터 최고 속도는 6.25 회전/s
timeStep = 0.001;
t0 = 0.5;

x1 = 20; y1= 10;
x2 = 30; y2 = -10;
targetV = 3;

delX = x1;
delY = y1;

targetX = delX;
targetY = delY;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV;
timeVec = 0:0.001:totalTime;
lenTimeVec = length(timeVec);

positionProfile1=zeros(lenTimeVec ,2);
for idx=1:lenTimeVec
    positionProfile1(idx, 1) = targetX/lenTimeVec * idx;
    positionProfile1(idx, 2) = targetY/lenTimeVec * idx;
end



delx = x2 - x1;
dely= y2 - y1;

targetX = delx;
targetY = dely;

tagetDist = sqrt(targetX.^2 + targetY.^2);
totalTime = tagetDist / targetV;
timeVec = 0:0.001:totalTime;
lenTimeVec = length(timeVec);
positionProfile2=zeros(lenTimeVec ,2);
for idx=1:lenTimeVec
    positionProfile2(idx, 1) = positionProfile1(end, 1) + targetX/lenTimeVec * idx;
    positionProfile2(idx, 2) = positionProfile1(end, 2) + targetY/lenTimeVec * idx;
end


x0 = x2; y0 = y2; %현재위치
x1 = 0; y1 = 0; %목표위치
x_r = (x0+x1)/2;
y_r = (y0+y1)/2;

r = sqrt((x0-x1)^2+(y0-y1)^2)/2;
path_len = pi*r;
t0 = path_len/targetV;
theta = atan((y0-y1)/(x0-x1));

t = (0:0.001:t0)';
lenTimeVec = length(t);
velocityProfile3=zeros(lenTimeVec ,2);

for idx = 1:lenTimeVec
    velocityProfile3(idx, 1) = x_r+ r * cos(theta - t(idx) * pi / t0);
    velocityProfile3(idx, 2) = y_r+ r * sin(theta - t(idx) * pi / t0);
end

t = (0:0.001:t0+0.5)';
tsec = seconds(t);




positionProfileX = [positionProfile1(:, 1); positionProfile2(:, 1); velocityProfile3(:, 1)];
positionProfileY = [positionProfile1(:, 2); positionProfile2(:, 2); velocityProfile3(:, 2)];

positionProfileX(end+1:end+1000) = zeros(1000,1);   % 이동후 1초간 위치 (0, 0)
positionProfileY(end+1:end+1000) = zeros(1000,1);   %

time_all = 0:0.001:(length(positionProfileX)-1)/1000;
time_all = time_all';
time_all = seconds(time_all);

xInput = timetable(time_all,positionProfileX);
yInput = timetable(time_all,positionProfileY);




plot(positionProfileX, positionProfileY)