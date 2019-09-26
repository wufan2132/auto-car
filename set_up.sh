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

LOCAL_IMAGE="yes"

while [ $# -gt 0 ]
do
    case "$1" in
    -h|--help)
        show_usage
        ;;
    -b|--build)
        LOCAL_IMAGE="no"
        ;;
    *)
        echo -e "\033[93mWarning\033[0m: Unknown option: $1"
        exit 2
        ;;
    esac
    shift
done

# TODO: add autocar_base.sh to bashrc
source scripts/autocar_base.sh

echo ""
info "1.install docker..."
docker ps >/dev/null
if [ $? == 0 ]; then
    echo "docker is already installed,  skip install."
else
    sudo bash docker/install/install_docker.sh >/dev/null
fi

echo ""
info "2.download images tar..."
if [ -f docker/images/*\.tar ]; then
    echo "images tar is already exist!"
else
	echo "现在还没写好，客官下次再来！"
	exit 0
fi

echo ""
info "3.build docker image..."
if [ "$LOCAL_IMAGE" == 'yes' ]; 
then
    echo build image from tar
    bash docker/build/build_from_tar.sh
else
    echo build new image
    bash docker/build/build_dev.sh  docker/build/dev.x86_64.dockerfile
fi
#  if [ "$ARCH" == 'aarch64' ]; then
#     echo "暂不支持arm"
#  else
#     bash docker/build/build_dev.sh  docker/build/dev.x86_64.dockerfile
# fi
set -e
echo ""
info "3.generating docker container..."
bash docker/scripts/dev_start.sh
