clear;clc;
timeStep = 0.001;

T = readtable('23_results.csv');
t = T.Var1(18499:end)-18.498;
lenTime = length(t);
x = T.Var2(18499:end);
y = T.Var3(18499:end);
v = 8;

x1 = 40; y1 = -30;
x2 = -45; y2 = 0;
referenceX = zeros(lenTime, 1);
referenceY = zeros(lenTime,1);



x0 = x2; y0 = y2; %현재위치
x_r = x0/2;
y_r = y0/2;

r = sqrt(x0^2+y0^2)/2;
path_len = pi*r;
t0 = path_len/v;
theta = atan(y0/x0);

intervalVec = (0:0.001:t0)';
lenInterval = length(intervalVec);

xVec = zeros(lenInterval, 1);
yVec = zeros(lenInterval, 1);

for idx = 1:lenInterval
    pos = intervalVec(idx);
    xVec(idx) = x_r - r * cos(theta - pos * pi / t0);
    yVec(idx) = y_r - r * sin(theta - pos * pi / t0);
end


vxVec = zeros(lenTime, 1);
vyVec = zeros(lenTime, 1);

for idx = 2: lenTime
    vxVec(idx) = (x(idx) - x(idx-1)) /  timeStep;
    vyVec(idx) = (y(idx) - y(idx-1)) / timeStep;
end


subplot(3,2,[1 2])
plot([0, x1], [0, y1], color='blue')
hold on;
scatter(x1, y1, 100)
scatter(x2, y2, 100)
scatter(0, 0, 100)
plot([x1, x2], [y1, y2], color='blue')
plot(xVec, yVec, color='blue')
plot(x, y, color='red')
hold off;
title('Problem 4 Position (x-y)');
xlabel('X position (mm)');
ylabel('Y position (mm)');

subplot(3,2,3)

plot(t, x, 'LineWidth', 4)
title('Problem 5 Position (t - x)');
xlabel('t (sec)');
ylabel('X position (mm)');

subplot(3,2,4)
plot(t, vxVec, 'LineWidth', 4)
title('Problem 4 Velocity (t - v_x)');
xlabel('t (sec)');
ylabel('X velocity(mm/sec)');

subplot(3, 2,5)
plot(t, y, 'LineWidth', 4)
title('Problem 4 Position (t - y)');
xlabel('t (sec)');
ylabel('Y position (mm)');

subplot(3,2,6)
plot(t, vyVec, 'LineWidth', 4)
title('Problem 4 Velocity (t - v_y)');
xlabel('t (sec)');
ylabel('Y velocity (mm/sec)');