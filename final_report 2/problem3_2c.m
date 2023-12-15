time_step = 0.001;

targetX = 20;
targetY = 20;
targetV = 5;

xdata = xpos;
ydata = ypos;
len=length(xdata);
timeData = 0.001:0.001:len/1000;

tagetDist = sqrt(targetX.^2 + targetY.^2);

errorVec = zeros(len, 1);
vVec = zeros(len, 1);

for idx=1:len

    %오차 계산
    slope = targetY/targetX;
    dist = abs(slope * xdata(idx) - ydata(idx)) / sqrt(slope.^2+1);
    errorVec(idx) = dist; 
    
end

% 속도 계산
for idx = 1:len-20
    vVec(idx) = sqrt((xpos(idx+20)-xpos(idx)).^2+(ypos(idx+20)-ypos(idx)).^2)/0.02;
end


subplot(411)
plot(timeData, xpos)
title('X position (Sine)');
xlabel('Time');
ylabel('X position (mm)');

subplot(412)
plot(timeData, ypos)
title('Y position (Sine)');
xlabel('Time');
ylabel('Y position (mm)');

subplot(413)
plot(timeData, errorVec)
title('Error (Sine)');
xlabel('Time');
ylabel('Error');

subplot(414)
plot(timeData, vVec)
title('Velocity (Sine)');
xlabel('Time');
ylabel('Velocity');
