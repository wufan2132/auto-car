#!/bin/bash 

AUTOCAR_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source ${AUTOCAR_ROOT_DIR}/scripts/autocar_base.sh
source ${AUTOCAR_ROOT_DIR}/scripts/autocar_launch.sh
source ${AUTOCAR_ROOT_DIR}/devel/setup.sh
RUN_MODE="default"
TARGET_NODE=$2
while [ $# -gt 0 ]; do
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
        echo -e "\033[93mWarning\033[0m: Unknown option: $1"
        exit 2
        ;;
    esac
    shift
done

roslaunch launch/auto-car-env.launch

if [ "${RUN_MODE}" == "default" ]; then
    start planning 
    start control
elif [ "${RUN_MODE}" == "output" ]; then
    start planning -o
    start control -o
elif [ "${RUN_MODE}" == "debug" ]; then
    start planning 
    start control
elif [ "${RUN_MODE}" == "single" ]; then
    start ${TARGET_NODE} -o 
else
    error "Unknown mode!"
fi