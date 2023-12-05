clear;clc;
% 1회전당 2mm 이동
% 모터 최고 속도는 6.25 회전/s
timeStep = 0.001;
t0 = 0.5;

x1 = -10; y1=-20;
x2 = 20; y2 = -10;
targetV = 3;

delX = x1;
delY = y1;

targetX = delX/2;
targetY = delY/2;

totalTime = sqrt(delx.^2 + dely.^2) / targetV;
timePoints = 0:0.001:totalTime;
time_len = length(timePoints);

positionProfile1=zeros(time_len ,2);
for idx=1:time_len
    positionProfile1(idx, 1) = targetX/time_len * idx;
    positionProfile1(idx, 2) = targetY/time_len * idx;
end



delx = x2 - x1;
dely= y2 - y1;

targetX = delx/2;
targetY = dely/2;

totalTime = sqrt(targetX.^2 + targetY.^2) / targetV;
timePoints = 0:0.001:totalTime;
time_len = length(timePoints);
positionProfile2=zeros(time_len ,2);
for idx=1:time_len
    positionProfile2(idx, 1) = positionProfile1(end, 1) + targetX/time_len * idx;
    positionProfile2(idx, 2) = positionProfile1(end, 2) + targetY/time_len * idx;
end


delt=0.0001;
x0 = 20; y0 = -40; %현재위치
x1 = 0; y1 = 0; %목표위치
x_r = (x0+x1)/2;
y_r = (y0+y1)/2;

r = sqrt((x0-x1)^2+(y0-y1)^2)/2/2;
path_len = pi*r;
t0 = path_len/targetV;
theta = atan((y0-y1)/(x0-x1));

t = (0:0.001:t0)';
time_len = length(t);
velocityProfile3=zeros(time_len ,2);

for idx = 1:time_len
    velocityProfile3(idx, 1) = r * cos(theta - t(idx) * pi / t0);
    velocityProfile3(idx, 2) = r * sin(theta - t(idx) * pi / t0);
end
plot(velocityProfile3(:, 1), velocityProfile3(:, 2))
vx = r*sin(theta-t*pi/t0)*pi/t0;  vx(end+1:end+500)=zeros(500,1);
vy = -r*cos(theta-t*pi/t0)*pi/t0; vy(end+1:end+500)=zeros(500,1);

t = (0:0.001:t0+0.5)';
tsec = seconds(t);

xvelinput = timetable(tsec,vx);
yvelinput = timetable(tsec,vy);



x_vel_all = [positionProfile1(:, 1); positionProfile2(:, 1); velocityProfile3(:, 1)];
y_vel_all = [positionProfile1(:, 2); positionProfile2(:, 2); velocityProfile3(:, 2)];
time_all = 0:0.001:(length(x_vel_all)-1)/1000;
time_all = time_all';
time_all = seconds(time_all);

xvelinput = timetable(time_all,x_vel_all);
yvelinput = timetable(time_all,y_vel_all);
