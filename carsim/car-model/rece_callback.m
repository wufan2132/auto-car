function rece_callback(~,~)
    global rece_buf
    global u
    size = 32;
    rece =char(fread(u, size));
    rece_buf = sprintf(rece);
end