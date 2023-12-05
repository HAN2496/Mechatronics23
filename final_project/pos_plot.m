plot(xpos,ypos)
syms x y;
circle=(x-(x0+x1)/2)^2+(y-(y0+y1)/2)^2==r^2;
hold on
fimplicit(circle)
axis equal
hold off