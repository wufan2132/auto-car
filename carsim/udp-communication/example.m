global send_buf
global rece_buf
send_buf = 'HELLO WORLD!';
UDP_open();
pause(5);
send_buf = 'Hawdadawd!';
fprintf(rece_buf);
pause(5);
UDP_close();