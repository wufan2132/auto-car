#!/usr/bin/env bash

###############################################################################
# Copyright 2017 The Apollo Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###############################################################################

INCHINA="no"
LOCAL_IMAGE="yes"
VERSION=""
ARCH=$(uname -m)
VERSION_OPT=""
IN_DOCKER_USER=cat
IN_DOCKER_GRP=${PROJECT_NAME}

PROJECT_ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
source ${PROJECT_ROOT_DIR}/configure


function show_usage() {
    cat <<EOF
Usage: $(basename $0) [options] ...
OPTIONS:
    -C                     Pull docker image from China mirror.
    -h, --help             Display this help and exit.
    -t, --tag <version>    Specify which version of a docker image to pull.
    stop                   Stop all running Apollo containers.
EOF
    exit 0
}

function stop_containers() {
    running_containers=$(docker ps --format "{{.Names}}")

    for i in ${running_containers[*]}; do
        if [[ "$i" =~ ${PROJECT_NAME}_* ]]; then
            printf %-*s 70 "stopping container: $i ..."
            docker stop $i >/dev/null
            if [ $? -eq 0 ]; then
                printf "\033[32m[DONE]\033[0m\n"
            else
                printf "\033[31m[FAILED]\033[0m\n"
            fi
        fi
    done
}


if [ ! -e /${PROJECT_NAME} ]; then
    sudo ln -sf ${PROJECT_ROOT_DIR} /${PROJECT_NAME}
fi

if [ -e /proc/sys/kernel ]; then
    echo "/${PROJECT_NAME}/data/core/core_%e.%p" | sudo tee /proc/sys/kernel/core_pattern >/dev/null
fi

MAP_VOLUME_CONF=""

while [ $# -gt 0 ]; do
    case "$1" in
    -C | --docker-cn-mirror)
        INCHINA="yes"
        ;;
    -image)
        echo -e "\033[093mWarning\033[0m: This option has been replaced by \"-t\" and \"--tag\", please use the new one.\n"
        show_usage
        ;;
    -t | --tag)
        IMG=$1
        ;;
    -h | --help)
        show_usage
        ;;
    -l | --local)
        LOCAL_IMAGE="yes"
        ;;
    --map)
        map_name=$2
        shift
        source ${PROJECT_ROOT_DIR}/docker/scripts/restart_map_volume.sh \
            "${map_name}" "${VOLUME_VERSION}"
        ;;
    stop)
        stop_containers
        exit 0
        ;;
    *)
        echo -e "\033[93mWarning\033[0m: Unknown option: $1"
        exit 2
        ;;
    esac
    shift
done

if [ -z "${DOCKER_REPO}" ]; then
    DOCKER_REPO=${PROJECT_NAME}
fi

if [ "$IMG" == "" ]; then
    if [ "$VERSION" == "" ]; then
        for file in $(docker images); do
            if [[ $file == dev-${ARCH}* ]]; then
                VERSION=$file
                break
            fi
        done
    fi
    if [ "$VERSION" == "" ]; then
        echo "images not found!":
        exit 0
    fi
    IMG=${DOCKER_REPO}:$VERSION
fi

function main() {
    if [ "$LOCAL_IMAGE" = "yes" ]; then
        info "Start docker container based on local image : $IMG"
    else
        info "Start pulling docker image $IMG ..."
        docker pull $IMG
        if [ $? -ne 0 ]; then
            error "Failed to pull docker image."
            exit 1
        fi
    fi

    #del old container
    docker ps -a --format "{{.Names}}" | grep ${PROJECT_NAME} 1>/dev/null
    if [ $? == 0 ]; then
        docker stop ${PROJECT_NAME}_dev 1>/dev/null
        docker rm -v -f ${PROJECT_NAME}_dev 1>/dev/null
    fi

    local display=""
    if [[ -z ${DISPLAY} ]]; then
        display=":0"
    else
        display="${DISPLAY}"
    fi

    USER_ID=$(id -u)
    GRP_ID=$(id -g)
    LOCAL_HOST=$(hostname)
    DOCKER_HOME="/home/$USER"
    if [ "$USER" == "root" ]; then
        DOCKER_HOME="/root"
    fi
    if [ ! -d "$HOME/.cache" ]; then
        mkdir "$HOME/.cache"
    fi

    info "Starting docker container \"${PROJECT_NAME}_dev\" ..."

    DOCKER_CMD="nvidia-docker"
    if ! [ -x "$(command -v ${DOCKER_CMD})" ]; then
        DOCKER_CMD="docker"
    fi

    EXTRA_VOLUMES=""
    if [ "$ARCH" == 'aarch64' ]; then
        EXTRA_VOLUMES="
        -v /usr/lib/aarch64-linux-gnu/tegra:/usr/lib/aarch64-linux-gnu/tegra    \
        -v /usr/lib/aarch64-linux-gnu/gstreamer-1.0:/usr/lib/aarch64-linux-gnu/gstreamer-1.0    \
        -v /usr/lib/aarch64-linux-gnu/tegra-egl:/usr/lib/aarch64-linux-gnu/tegra-egl    \
        -v /usr/lib/aarch64-linux-gnu/mesa-egl:/usr/lib/aarch64-linux-gnu/mesa-egl    \
        -v /run:/run    \
        -v /lib/firmware/tegra18x:/lib/firmware/tegra18x
        "
    fi

    ${DOCKER_CMD} run -it \
        -t \
        -d \
        --privileged \
        --name ${PROJECT_NAME}_dev \
        --user=$USER_ID \
        -e DISPLAY=$display \
        -e DOCKER_USER=$IN_DOCKER_USER \
        -e DOCKER_USER_ID=$USER_ID \
        -e DOCKER_GRP=$IN_DOCKER_GRP \
        -e DOCKER_GRP_ID=$GRP_ID \
        -e DOCKER_IMG=$IMG \
        ${EXTRA_VOLUMES} \
        -v $PROJECT_ROOT_DIR:/${PROJECT_NAME} \
        --net host \
        -w /${PROJECT_NAME} \
        --add-host in_dev_docker:127.0.0.1 \
        --add-host ${LOCAL_HOST}:127.0.0.1 \
        --hostname in_dev_docker \
        --shm-size 2G \
        --pid=host \
        -v /dev/null:/dev/raw1394 \
        $IMG \
        /bin/bash

    if [ $? -ne 0 ]; then
        error "Failed to start docker container \"${PROJECT_NAME}_dev\" based on image: $IMG"
        exit 1
    fi

    if [ "${USER}" != "root" ]; then
        docker exec -u root ${PROJECT_NAME}_dev bash -c "/${PROJECT_NAME}/docker/scripts/docker_adduser.sh"
    fi

    ok "Finished setting up ${PROJECT_NAME} docker environment. Now you can enter with: \nbash docker/scripts/dev_into.sh"
    ok "Enjoy!"
}

main
