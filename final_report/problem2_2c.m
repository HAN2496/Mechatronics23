clear;clc;
timeStep = 0.001;

%단위시간(1초)동안 이동하는 거리 (mm)
targetV = 5 ;

%목표 x, y위치(targetX, targetY) 및 최종 이동거리(totalDist)
targetX = 64;
targetY = 48;
targetDist = sqrt(targetX.^2 + targetY.^2);

%x, y축 속도
targetVx = targetX / targetDist * targetV;
targetVy = targetY / targetDist * targetV;

%목표 위치까지 도달하는데 걸리는 시간
totalTime = targetDist / targetV;

%timeStep단위로 증가하는 시간 프로파일(timeVec)
timeVec = (0:timeStep:totalTime)';
lenTimeVec = length(timeVec);

%x, y 프로파일 초기화
xVec = zeros(lenTimeVec, 1);
yVec = zeros(lenTimeVec, 1);

%초기 위치를 제외하고 프로파일 업데이트
for idx=2:lenTimeVec
    xVec(idx) = targetVx * (idx-1) * timeStep;
    yVec(idx) = targetVy * (idx-1) * timeStep;
end

%목표 위치 값을 1초 더 넣어주어 발산 방지
xVec(idx+1:idx+1000)=targetX*ones(1000,1); 
yVec(idx+1:idx+1000)=targetY*ones(1000,1);

% 1초 추가
timeVec = (0:timeStep:totalTime+1)';

%timetable 형태로 input
timeVecSec = seconds(timeVec);
xvelinput = timetable(timeVecSec, xVec);
yvelinput = timetable(timeVecSec, yVec);

subplot(3,1,1)
scatter(xVec, yVec)
hold on;
plot(xVec, yVec)
hold off;
title('Problem 2-2 (velocity)');
xlabel('X position (mm)');
ylabel('Y position (mm)');

subplot(3,1,2)
scatter(timeVec, xVec)
hold on;
plot(timeVec, xVec)
hold off;
title('Problem 2-2 (t - x)');
xlabel('t (sec)');
ylabel('X position (mm)');

subplot(3,1, 3)
scatter(timeVec, yVec)
hold on;
plot(timeVec, yVec)
hold off;
title('Problem 2-2 (t - y)');
xlabel('time (sec)');
ylabel('Y position (mm)');