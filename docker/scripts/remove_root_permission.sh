
sudo gpasswd -a ${USER} docker

su - ${USER}

sudo systemctl restart docker

docker ps

if [ $? -eq 0 ]; then
     echo "清除docker权限成功！"
else
     echo "清除docker权限失败."
fi
