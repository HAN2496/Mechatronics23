function  y=accelprofile(vTarget,t0,t)
y=vTarget/2*(sin(pi/t0*(t-t0/2))+1);
end