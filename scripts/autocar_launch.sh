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

AUTOCAR_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

source ${AUTOCAR_ROOT_DIR}/scripts/autocar_base.sh


function start() {
  set -e
  NODE_NAME=$1
  OUTPUT=$2
  if [ "$OUTPUT" == "-o" ]; then
    # 输出到屏幕
    eval "rosrun ${NODE_NAME} ${NODE_NAME}_node \
          --flagfile=${AUTOCAR_ROOT_DIR}/src/${NODE_NAME}/conf/${NODE_NAME}.conf \
          &"
  else
    # 输出到文件
    eval "nohup rosrun ${NODE_NAME} ${NODE_NAME}_node \
          --flagfile=${AUTOCAR_ROOT_DIR}/src/${NODE_NAME}/conf/${NODE_NAME}.conf\
          $@ </dev/null >${AUTOCAR_ROOT_DIR}/data/log/${NODE_NAME}.out 2>&1 &"
  fi
  info "${NODE_NAME} is running..."
}

function stop() {
  set -e
  NODE_NAME=$1
  rosnode kill  /${NODE_NAME}
  info "${NODE_NAME} is stop"
}