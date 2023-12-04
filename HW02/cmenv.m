t = 0:0.001:10;
t = t';
t=seconds(t);
simout5 = ones(10001, 1) * 10;
simin = timetable(t, simout5);
