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

IMAGE_SOURCE="local"

while [ $# -gt 0 ]; do
    case "$1" in
    -h | --help)
        show_usage
        ;;
    -b | --build)
        IMAGE_SOURCE="build"
        ;;
    -d | --download)
        IMAGE_SOURCE="server"
        ;;
    -l | --local)
        IMAGE_SOURCE="local"
        ;;
    *)
        echo -e "\033[93mWarning\033[0m: Unknown option: $1"
        exit 2
        ;;
    esac
    shift
done

echo "set up env....."
PROJECT_ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source ${PROJECT_ROOT_DIR}/configure

if [ "$PROJECT_IN_DOCKER" == "true" ]; then
    error "setup.sh must run in local. and can not run in docker!"
    exit 0
fi
create_data_dir

echo ""
info "1.install docker..."
docker ps >/dev/null
if [ $? == 0 ]; then
    echo "docker is already installed, skip install."
else
    sudo bash "${PROJECT_ROOT_DIR}/docker/install/install_docker.sh" >/dev/null
    sudo bash "${PROJECT_ROOT_DIR}/docker/install/install_nvidia_docker.sh" >/dev/null
fi
set -e
echo ""
info "2.download images tar..."
if [ -f ${PROJECT_ROOT_DIR}/docker/images/${PROJECT_NAME}:*\.tar ] && [ "$IMAGE_SOURCE" == 'local' ]; then
    echo "images tar is already exist, skip download."
elif [ "$IMAGE_SOURCE" != 'build' ]; then
    source "${PROJECT_ROOT_DIR}/docker/images/release_images.sh"
    if [ "$ARCH" == 'aarch64' ]; then
        IMG=$IMG_aarch64
    else
        IMG=$IMG_x86_64
    fi
    if [ -f ${PROJECT_ROOT_DIR}/docker/images/${IMG} ]; then
        echo "images tar is already exist, skip download."
    else
        bash "${PROJECT_ROOT_DIR}/docker/build/download_images.sh" $IMG
    fi
fi

echo ""
info "3.build docker image..."
if [ "$IMAGE_SOURCE" == 'local' ] || [ "$IMAGE_SOURCE" == 'server' ]; then
    echo build image from tar
    bash "${PROJECT_ROOT_DIR}/docker/build/build_from_tar.sh"
elif [ "$IMAGE_SOURCE" == 'build' ]; then
    echo build new image
    bash "${PROJECT_ROOT_DIR}/docker/build/build_dev.sh docker/build/dev.x86_64.dockerfile"
fi
#  if [ "$ARCH" == 'aarch64' ]; then
#     echo "暂不支持arm"
#  else
#     bash docker/build/build_dev.sh  docker/build/dev.x86_64.dockerfile
# fi
echo ""
info "4.generating docker container..."
bash "${PROJECT_ROOT_DIR}/docker/scripts/dev_start.sh"
