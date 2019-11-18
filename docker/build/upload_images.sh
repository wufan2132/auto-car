#!/usr/bin/env bash
# Usage:
#  ./upload_images.sh  [images_path]
PROJECT_ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
source ${PROJECT_ROOT_DIR}/configure

SERVER=${IMAGE_SERVER}
source "${PROJECT_ROOT_DIR}/config/servers/${SERVER}.sh"

IMAGE=$1

if [ "$PROJECT_IN_DOCKER" == "true" ]; then
        error "it must run in local. and can not run in docker!"
        exit 0
fi
#
echo "the password is ${S_PWD} ${S_PWD_DETALL}"
scp  "./$IMAGE" "${S_USER}@${S_IP}:${IMAGES_PATH}"
