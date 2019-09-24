

IMG_FILE=$1

AUTOCAR_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

if ["$IMG_FILE" == ""]; then
for image in `ls "${AUTOCAR_ROOT_DIR}"/docker/images`
    do
        if [[ $image == autocar:dev-* ]]
        then
            IMG_FILE="${AUTOCAR_ROOT_DIR}/docker/images/${image}"
        fi
    done
fi

docker load --input ${IMG_FILE}