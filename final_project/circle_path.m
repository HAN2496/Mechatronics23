delt=0.0001;
x0 = 5; y0 = 4; %현재위치
x1 = 3; y1 = 2; %목표위치
vTarget = 3;

r = sqrt((x0-x1)^2+(y0-y1)^2)/2;
path_len = pi*r;
t0 = path_len/vTarget;
theta = atan((y0-y1)/(x0-x1));

t = (0:0.001:t0)';
vx = -r*sin(theta+t*pi/t0)*pi/t0;  vx(end+1:end+500)=zeros(500,1);
vy = r*cos(theta+t*pi/t0)*pi/t0; vy(end+1:end+500)=zeros(500,1);

t = (0:0.001:t0+0.5)';
tsec = seconds(t);

xvelinput = timetable(tsec,vx);
yvelinput = timetable(tsec,vy);

