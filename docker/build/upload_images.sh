#!/usr/bin/env bash
# Usage:
#  ./upload_images.sh  [images_path]
SERVER=sixianka

IMAGE=$1

AUTOCAR_ROOT_DIR="$( cd "$( dirname "$0" )/../.." && pwd )"
source "${AUTOCAR_ROOT_DIR}/config/servers/${SERVER}.sh"
#
echo "the password is ${S_PWD} ${S_PWD_DETALL}"
scp  $IMAGE "${S_USER}@${S_IP}:${IMAGES_PATH}"
