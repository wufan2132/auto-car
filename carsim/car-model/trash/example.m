global send_buf
global rece_buf
send_buf = 0
rece_buf = 0
function [speed_cmd,steer_cmd] = comunicate(x,y,yaw,vx,steer)
send_buf = x;
UDP_open();
pause(5);

speed_cmd = rece_buf;
steer_cmd = 0;
UDP_close();
