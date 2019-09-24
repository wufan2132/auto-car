

IMG_FILE=$1

AUTOCAR_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

if [ "$IMG_FILE" == "" ]; then
for image in `ls "${AUTOCAR_ROOT_DIR}"/docker/images`
    do
        if [[ $image == autocar:dev-* ]]
        then
            IMG_FILE="${AUTOCAR_ROOT_DIR}/docker/images/${image}"
        fi
    done
fi

if [ "$IMG_FILE" == "" ]; then
    error "找不到镜像文件: ${IMG_FILE}  "
    info "请将镜像文件拷贝到 docker/images 目录下"
    exit 0
fi

docker load --input ${IMG_FILE}
