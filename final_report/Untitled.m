timeVec=timeVec(1:5657);
xVec=xVec(1:end-1000);
plot(timeVec,sinex);
hold on
plot(timeVec,sigmoidx);
plot(timeVec,quinx);
plot(timeVec,xVec);
legend('Sine','Sigmoid','Quintic','Straight')
hold off