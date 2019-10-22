#!/usr/bin/env bash

# Usage:
#  ./pack_image.sh  [commit_msg]
# or
#  ./pack_image.sh  [commit_msg]  [CONTAINER_ID]
ARCH=$(uname -m)

PROJECT_ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
source ${PROJECT_ROOT_DIR}/configure

REPO=${PROJECT_NAME}
COMMIT_MSG=$1
CONTAINER_ID=$2
TIME=$(date +%Y%m%d_%H%M)




if [ "$PROJECT_IN_DOCKER" == "true" ]; then
        error "it must run in local. and can not run in docker!"
        exit 0
fi

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
if [ ! -d "${PROJECT_ROOT_DIR}/docker/images/history" ]; then
    mkdir "${PROJECT_ROOT_DIR}/docker/images/history"
fi

for image in $(ls "${PROJECT_ROOT_DIR}"/docker/images); do
    if [[ "$image" == ${REPO}:dev-* ]]; then
        echo "remove old images:${image}"
        mv "${PROJECT_ROOT_DIR}/docker/images/${image}" "${PROJECT_ROOT_DIR}/docker/images/history/${image}"
    fi
done

# save image
docker save \
    -o "${PROJECT_ROOT_DIR}/docker/images/${REPO}:dev-${ARCH}-${TIME}.tar" $TAG

# log
echo "${TAG}.tar  ${COMMIT_MSG}" 
echo "${TAG}.tar  ${COMMIT_MSG}" >>"${PROJECT_ROOT_DIR}/docker/images/images-log-${USER}.md"

success "build images success"
