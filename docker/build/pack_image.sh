

ARCH=$(uname -m)

REPO=autocar
COMMIT_MSG=$2
CONTAINER_ID=$1
TIME=$(date +%Y%m%d_%H%M)
AUTOCAR_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

if [ ${COMMIT_MSG} == ""]; then
    COMMIT_MSG="defult"
fi

TAG="${REPO}:dev-${ARCH}-${TIME}"
# commit 
docker commit \
        -m $COMMIT_MSG \
        -a "wufan"  \
        $CONTAINER_ID ${TAG}

# move history images
mkdir "${AUTOCAR_ROOT_DIR}/docker/images/history"
for image in `ls "${AUTOCAR_ROOT_DIR}"/docker/images`
    do
        if [[ $image == autocar:dev-* ]]
        then
            mv "${AUTOCAR_ROOT_DIR}/docker/images/${image}" "${AUTOCAR_ROOT_DIR}/docker/images/history/${image}"
        fi
    done

# save image
docker save \
    -o "${AUTOCAR_ROOT_DIR}/docker/images/${REPO}:dev-${ARCH}-${TIME}.tar" $TAG

# log
echo "${USER}  ${tag}  ${COMMIT_MSG}" >>  "${AUTOCAR_ROOT_DIR}/docker/images/images-log.md"