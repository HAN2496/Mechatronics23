len = length(positionProfileX)-1000;
v=zeros(len,1);

for idx = 1:len
    v(idx) = sqrt((xpos(idx+20)-xpos(idx)).^2+(ypos(idx+20)-ypos(idx)).^2)/0.02;
end

vAvg = mean(v);                     
dVel = abs(vAvg/targetV-1);         % Dvel

disSquare = 100 * ones(len+10,1);

for i = 1:len+10
    for n = 1:len+10
        d = ((xpos(i) - positionProfileX(n))^2 + (ypos(i) - positionProfileY(n))^2);    
        if d < disSquare(i)
            disSquare(i) = d;       % [Contour Error]^2
        end        
    end         
end

rms = sqrt(mean(disSquare));        % CErms

fprintf('Dvel = %d,  RMS = %d',dVel,rms);