

IMG_FILE=$1


PROJECT_ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
source ${PROJECT_ROOT_DIR}/configure

if [ "$IMG_FILE" == "" ]; then
for image in `ls "${PROJECT_ROOT_DIR}"/docker/images`
    do
        if [[ $image == ${PROJECT_NAME}:dev-${ARCH}* ]]
        then
            IMG_FILE="${PROJECT_ROOT_DIR}/docker/images/${image}"
            info "images file path: ${IMG_FILE}"
        fi
    done
fi

if [ "$IMG_FILE" == "" ]; then
    error "找不到镜像文件: ${PROJECT_NAME}:dev-${ARCH}xxxxxx.tar "
    info "请将镜像文件拷贝到 docker/images 目录下"
    exit 0
fi

docker load --input ${IMG_FILE}
