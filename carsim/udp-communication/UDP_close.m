function UDP_close()
    global u
    fclose(u);
    delete(u);
    echoudp('off');
    delete(timerfind) 
end