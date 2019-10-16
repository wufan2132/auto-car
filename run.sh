#!/usr/bin/env bash

AUTOCAR_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source ${AUTOCAR_ROOT_DIR}/scripts/autocar_base.sh
source ${AUTOCAR_ROOT_DIR}/scripts/autocar_launch.sh
source ${AUTOCAR_ROOT_DIR}/devel/setup.sh

check_in_docker
if [ "$AUTOCAR_IN_DOCKER" == "false" ]; then
        error "build.sh must run in docker!"
        exit 0
fi

RUN_MODE="default"
TARGET_NODE=$2

case "$1" in
-h | --help)
    show_usage
    ;;
-s | --single)
    RUN_MODE="single"
    ;;
-d | --debug)
    RUN_MODE="debug"
    ;;
-o | --output)
    RUN_MODE="output"
    ;;
*)
    ;;
esac




if [ "${RUN_MODE}" == "default" ]; then
    info "runmode: default"
    start planning 
    start control
    roslaunch launch/auto-car-env.launch
elif [ "${RUN_MODE}" == "output" ]; then
    info "runmode: output"
    start planning -o
    start control -o
    roslaunch launch/auto-car-env.launch
elif [ "${RUN_MODE}" == "debug" ]; then
    info "runmode: debug ${TARGET_NODE}"
    eval "gdbserver :2333 devel/lib/${TARGET_NODE}/${TARGET_NODE}_node  \
        --flagfile=/autocar/src/${TARGET_NODE}/conf/${TARGET_NODE}.conf"
elif [ "${RUN_MODE}" == "single" ]; then
    info "just run ${TARGET_NODE}"
    start ${TARGET_NODE} -o 
else
    error "Unknown mode!"
fi
