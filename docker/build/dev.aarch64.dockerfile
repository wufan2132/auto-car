# This is an auto generated Dockerfile for ros:robot
# generated from docker_images/create_ros_image.Dockerfile.em
FROM arm64v8/ros:melodic-ros-base-bionic

# install ros packages
RUN apt-get update && apt-get install -y \
    ros-melodic-robot=1.4.1-0* \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update -y && \
    apt-get install -y \
    apt-utils \
    sudo \
    ca-certificates \
    gnupg


RUN apt-get update -y && \
    apt-get install -y \
    apt-transport-https \
    bc \
    build-essential \
    cmake \
    cppcheck \
    curl \
    vim \
    debconf-utils \
    doxygen \
    gdb \
    git \
    google-perftools \
    graphviz \
    lcov \
    libblas-dev \
    libboost-all-dev \
    libcurl4-openssl-dev \
    libfreetype6-dev \
    liblapack-dev \
    libpcap-dev \
    locate \
    lsof \
    nfs-common \
    shellcheck \
    software-properties-common \
    sshfs \
    subversion \
    unzip \
    v4l-utils \
    wget \
    zip && \
    apt-get clean && rm -rf /var/lib/apt/lists/* && \
    echo '\n\n\n' | ssh-keygen -t rsa

WORKDIR /autocar
#USER autocar
