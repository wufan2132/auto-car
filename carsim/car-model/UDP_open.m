function UDP_open()
    global send_buf
%    global rece_buf
    global u
%     send_buf = 'hello';
%     rece_buf = '';
    %开启前先关闭
    echoudp('off');
    %设置本地端口
    echoudp('on',8099);
    %设置远程IP与端口
    Rrmotehost = '192.168.174.1';
    u = udp(Rrmotehost,8088);
    %设置接收等待时间
    set(u,'TimeOut',0.1);
    set(u,'InputBufferSize',1000);
    fopen(u);
    %输入缓存赋值，可以在其他线程赋值
    % send_buf = 'hello';
    delete(timerfind)   % 开启前删除现有的定时器 
    send_timer = timer('StartDelay',1,'TimerFcn',@send_callback,'Period',2,'ExecutionMode','fixedRate');
    rece_timer = timer('StartDelay',1,'TimerFcn',@rece_callback,'Period',2,'ExecutionMode','fixedRate');
    fwrite(u,send_buf);
    start([send_timer,rece_timer])
end

