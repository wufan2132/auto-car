
sudo groupadd docker 

sudo gpasswd -a ${USER} docker

sudo chmod a+rw /var/run/docker.sock
