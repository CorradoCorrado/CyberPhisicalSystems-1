clear all
close all
clc


l = 0.2;

t = 0;
Tf = 5;
dt = 0.01;

x = 0;
y = 0;
theta = 0;

% vr = 0.2;
% vl = 0;

xd = 1;
yd = 0.7;

kt = 10;
kr = 100;

while t<Tf

    xe = x - xd;
    ye = y - yd;

    thetad = atan2(yd-y,xd-x);
    thetae = theta - thetad;

    v = kt*sqrt(xe^2 + ye^2);
    omega = -kr*thetae;

    if v > 1
        v = 1;
    end
    if omega > pi/2
        omega = pi/2;
    end
    if omega < -pi/2
        omega = -pi/2;
    end

    vr = v + 0.5*l*omega;
    vl = v - 0.5*l*omega;

%     if vr > 1
%         vr = 1;
%     end
%     if vr < -1
%         vr = -1;
%     end
% 
% 
%     if vl > 1
%         vl = 1;
%     end
%     if vl < -1
%         vl = -1;
%     end
    %%---------------------
    %%Esto es como el robot real:

    v = (vr + vl)/2;
    omega = (vr - vl)/l;

    xp = v*cos(theta);
    yp = v*sin(theta);
    thetap = omega;
    
    x = x + xp*dt;
    y = y + yp*dt;
    theta = theta + thetap*dt;

    t = t + dt;

    figure(1)
    scatter(x,y)
    hold on
end

