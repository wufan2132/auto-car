#!/usr/bin/env bash

# Usage:
#  ./pack_image.sh  [commit_msg]
# or
#  ./pack_image.sh  [commit_msg]  [CONTAINER_ID]
ARCH=$(uname -m)

REPO=autocar
COMMIT_MSG=$1
CONTAINER_ID=$2
TIME=$(date +%Y%m%d_%H%M)

AUTOCAR_ROOT_DIR="$(cd "$(dirname $0)/../.." && pwd)"
source ${AUTOCAR_ROOT_DIR}/scripts/autocar_base.sh

get_start_time

if [ "${CONTAINER_ID}" == "" ]; then
    for id in $(docker ps -q); do
        if [ "$CONTAINER_ID" == "" ]; then
            CONTAINER_ID=$id
        else
            error "Multiple containers is running, please assign the CONTAINER_ID"
        fi
    done
fi

if [ "${CONTAINER_ID}" == "" ]; then
    error "the docker container must be running!"
    exit 0
fi

set -e
if [ "${COMMIT_MSG}" == "" ]; then
    error "please input the commit message!"
    exit 0
fi

TAG="${REPO}:dev-${ARCH}-${TIME}"
# commit
docker commit \
    -m $COMMIT_MSG \
    -a "wufan" \
    $CONTAINER_ID ${TAG}

# move history images
if [ ! -d "${AUTOCAR_ROOT_DIR}/docker/images/history" ]; then
    mkdir "${AUTOCAR_ROOT_DIR}/docker/images/history"
fi

for image in $(ls "${AUTOCAR_ROOT_DIR}"/docker/images); do
    if [[ "$image" == autocar:dev-* ]]; then
        echo "remove old images:${image}"
        mv "${AUTOCAR_ROOT_DIR}/docker/images/${image}" "${AUTOCAR_ROOT_DIR}/docker/images/history/${image}"
    fi
done

# save image
docker save \
    -o "${AUTOCAR_ROOT_DIR}/docker/images/${REPO}:dev-${ARCH}-${TIME}.tar" $TAG

# log
echo "${TAG}.tar  ${COMMIT_MSG}" 
echo "${TAG}.tar  ${COMMIT_MSG}" >>"${AUTOCAR_ROOT_DIR}/docker/images/images-log-${USER}.md"

success "build images success"
