#!/usr/bin/env bash

# Usage:
#  ./download_images.sh  [images_filename]

SERVER=sixianka

IMAGE=$1
if [[ "$IMAGE" != *\.tar ]]; then
    echo "images must be .tar!"
    exit 0
fi
AUTOCAR_ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
source "${AUTOCAR_ROOT_DIR}/config/servers/${SERVER}.sh"
source ${AUTOCAR_ROOT_DIR}/scripts/autocar_base.sh
check_in_docker
if [ "$AUTOCAR_IN_DOCKER" == "true" ]; then
        error "it must run in local. and can not run in docker!"
        exit 0
fi
#
echo "this password is ${S_PWD} ${S_PWD_DETALL}"
scp "${S_USER}@${S_IP}:${IMAGES_PATH}/${IMAGE}" "${AUTOCAR_ROOT_DIR}/docker/images/"

# move history images
if [ ! -d "${AUTOCAR_ROOT_DIR}/docker/images/history" ]; then
    mkdir "${AUTOCAR_ROOT_DIR}/docker/images/history"
fi

for image in $(ls "${AUTOCAR_ROOT_DIR}"/docker/images); do
    if [[ "$image" == autocar:dev-* && "$image" != "${IMAGE}" ]]; then
        echo "remove old images:${image}"
        mv "${AUTOCAR_ROOT_DIR}/docker/images/${image}" "${AUTOCAR_ROOT_DIR}/docker/images/history/${image}"
    fi
done
