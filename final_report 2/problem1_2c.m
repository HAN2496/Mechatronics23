%문제 1-2번, 1-3번

data = xpos;
timeData = data.Time;
posData = data.Data;

% 데이터 시각화
plot(timeData, posData);
title('Problem 1-2 (Not considering paths) ');
xlabel('Time (s)');
ylabel('Position');