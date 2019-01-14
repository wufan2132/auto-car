function send_callback(~,~)
    global send_buf
    global u
    fwrite(u,send_buf);
end