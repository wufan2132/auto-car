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

ARCH=$(uname -m)



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
info "2.build docker image..."
 if [ "$ARCH" == 'aarch64' ]; then
    echo "暂不支持arm"
 else
    bash docker/build/build_dev.sh  docker/build/dev.x86_64.dockerfile
fi

echo ""
info "3.generating docker container..."
bash docker/scripts/dev_start.sh