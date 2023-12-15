len = length(xVec)-1000;
v=zeros(len,1);

for idx = 1:len-20
    v(idx) = sqrt((xpos(idx+20)-xpos(idx)).^2+(ypos(idx+20)-ypos(idx)).^2)/0.02;
end

vAvg = mean(v);                     
dVel = abs(vAvg/targetV-1);         % Dvel

disSquare = 100 * ones(len+10,1);

for i = 1:len
    for n = 1:len
        d = ((xpos(i) - xVec(n))^2 + (ypos(i) - yVec(n))^2);    
        if d < disSquare(i)
            disSquare(i) = d;       % [Contour Error]^2
        end        
    end         
end

rms = sqrt(mean(disSquare));        % CErms

fprintf('Dvel = %d,  RMS = %d',dVel,rms);