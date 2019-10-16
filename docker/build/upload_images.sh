#!/usr/bin/env bash
# Usage:
#  ./upload_images.sh  [images_path]
SERVER=sixianka

IMAGE=$1

AUTOCAR_ROOT_DIR="$( cd "$( dirname "$0" )/../.." && pwd )"
source "${AUTOCAR_ROOT_DIR}/config/servers/${SERVER}.sh"
source ${AUTOCAR_ROOT_DIR}/scripts/autocar_base.sh
check_in_docker
if [ "$AUTOCAR_IN_DOCKER" == "true" ]; then
        error "it must run in local. and can not run in docker!"
        exit 0
fi
#
echo "the password is ${S_PWD} ${S_PWD_DETALL}"
scp  "$IMAGE" "${S_USER}@${S_IP}:${IMAGES_PATH}"
