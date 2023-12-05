clear;clc;
% 1회전당 2mm 이동
% 모터 최고 속도는 6.25 회전/s
timeStep = 0.001;
t0 = 0.5;

x1 = 32;
x2 = 23;
targetV = 3;

targetX = x1/2;
targetY = x2/2;
targetVx = targetX/sqrt(targetX.^2 + targetY.^2) * targetV;
targetVy = targetY/sqrt(targetX.^2 + targetY.^2) * targetV;


sum_term = 0;
for i=1:timeStep:t0
    sum_term = sum_term + sineprofile(targetVx, t0, i) * timeStep;
end
totalTime = (targetX - sum_term) / targetVx + 2 * t0;

timePoints = 0:0.001:totalTime;
accel_len = t0 * 1000 + 1;
time_len = length(timePoints);

velocityProfile1=zeros(time_len ,2);
for idx=1:time_len
    velocityProfile1(idx, 1) = targetX/time_len * idx;
    velocityProfile1(idx, 2) = targetY/time_len * idx;
end






% 1회전당 2mm 이동
% 모터 최고 속도는 6.25 회전/s
timeStep = 0.001;
t0 = 5;

x1 = -8;
x2 = -35;
targetV = 3;

targetX = x1/2;
targetY = x2/2;
targetVx = targetX/sqrt(targetX.^2 + targetY.^2) * targetV;
targetVy = targetY/sqrt(targetX.^2 + targetY.^2) * targetV;


sum_term = 0;
for i=1:timeStep:t0
    sum_term = sum_term + sineprofile(targetVx, t0, i) * timeStep;
end
totalTime = (targetX - sum_term) / targetVx + 2 * t0;


timePoints = 0:0.001:totalTime;
accel_len = t0 * 1000 + 1;
time_len = length(timePoints);
velocityProfile2=zeros(time_len ,2);

velocityProfile2=zeros(time_len ,2);
for idx=1:time_len
    velocityProfile2(idx, 1) = velocityProfile1(end, 1) + targetX/time_len * idx;
    velocityProfile2(idx, 2) = velocityProfile1(end, 2) + targetY/time_len * idx;
end





delt=0.0001;
x0 = 24; y0 = -12; %현재위치
x1 = 0; y1 = 0; %목표위치
vTarget = 3;

r = sqrt((x0-x1)^2+(y0-y1)^2)/2/2;
path_len = pi*r;
t0 = path_len/vTarget;
theta = atan((y0-y1)/(x0-x1));

t = (0:0.001:t0)';
vx = r*sin(theta-t*pi/t0)*pi/t0;  vx(end+1:end+500)=zeros(500,1);
vy = -r*cos(theta-t*pi/t0)*pi/t0; vy(end+1:end+500)=zeros(500,1);

t = (0:0.001:t0+0.5)';
tsec = seconds(t);

xvelinput = timetable(tsec,vx);
yvelinput = timetable(tsec,vy);



x_vel_all = [velocityProfile1(:, 1); velocityProfile2(:, 1); vx];
y_vel_all = [velocityProfile1(:, 2); velocityProfile2(:, 2); vy];
time_all = 0:0.001:(length(x_vel_all)-1)/1000;
time_all = time_all';
time_all = seconds(time_all);

xvelinput = timetable(time_all,x_vel_all);
yvelinput = timetable(time_all,y_vel_all);
