#!/usr/bin/env bash
curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey |
  sudo apt-key add -
curl -s -L https://nvidia.github.io/nvidia-docker/ubuntu18.04/nvidia-docker.list |
  sudo tee /etc/apt/sources.list.d/nvidia-docker.list
sudo apt-get update
sudo apt-get install nvidia-docker2
sudo pkill -SIGHUP dockerd
# run test
read -p "Run nvidia-docker test ?  y or n" ans
if [ "$ans" == "y" ]; then
  sudo nvidia-docker run --rm nvidia/cuda:10.0-devel nvidia-smi
fi
echo "ok"