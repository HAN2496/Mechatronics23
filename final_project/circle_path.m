
nowx = 0;   nowy = 0;   %현재위치
tarx = 40;   tary = 30; %목표위치


dx=(tarx-nowx);
dy=(tary-nowy);

vTarget = 4;

r = sqrt((dx)^2+(dy)^2)/2;
path_len = pi*r;
t0 = path_len/vTarget;
theta = atan((dy)/(dx));

t = (0:0.001:t0)';
vx = -2*r*sin(theta+t*pi/t0)*pi/t0;  vx(end+1:end+2000)=zeros(2000,1);
vy = 2*r*cos(theta+t*pi/t0)*pi/t0; vy(end+1:end+2000)=zeros(2000,1);

%이동후 멈추게 하려고 t0+2초 해줌 (2초동안 속도0)
t = (0:0.001:t0+2)';
plot(vx,vy)
tsec = seconds(t);

xvelinput = timetable(tsec,vx);
yvelinput = timetable(tsec,vy);

