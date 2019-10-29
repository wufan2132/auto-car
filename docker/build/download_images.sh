#!/usr/bin/env bash

# Usage:
#  ./download_images.sh  [images_filename]

set -e
PROJECT_ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
source ${PROJECT_ROOT_DIR}/configure
SERVER=${IMAGE_SERVER}
source "${PROJECT_ROOT_DIR}/config/servers/${SERVER}.sh"

IMAGE=$1
if [[ "$IMAGE" != *\.tar ]]; then
    echo "images must be .tar!"
    exit 0
fi

if [ "$PROJECT_IN_DOCKER" == "true" ]; then
        error "it must run in local. and can not run in docker!"
        exit 0
fi
#
echo "this password is ${S_PWD} ${S_PWD_DETALL}"
scp "${S_USER}@${S_IP}:${IMAGES_PATH}/${IMAGE}" "${PROJECT_ROOT_DIR}/docker/images/"

# move history images
if [ ! -d "${PROJECT_ROOT_DIR}/docker/images/history" ]; then
    mkdir "${PROJECT_ROOT_DIR}/docker/images/history"
fi

for image in $(ls "${PROJECT_ROOT_DIR}"/docker/images); do
    if [[ "$image" == ${PROJECT_NAME}:dev-* && "$image" != "${IMAGE}" ]]; then
        echo "remove old images:${image}"
        mv "${PROJECT_ROOT_DIR}/docker/images/${image}" "${PROJECT_ROOT_DIR}/docker/images/history/${image}"
    fi
done
