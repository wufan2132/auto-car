AUTOCAR_ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source ${AUTOCAR_ROOT_DIR}/scripts/autocar_base.sh
set -e
TASK=""
TARGET=$2
case "$1" in
-h | --help)
    show_usage
    ;;
-b | --build)
    TASK="build"
    ;;
-c | --clean)
    TASK="clean"
    ;;
*)
    TASK="build"
    ;;
esac

function build_x86_64() {
    info "1.build msg"
    catkin_make -DCATKIN_WHITELIST_PACKAGES="car_msgs"

    info "2.build other node"
    catkin_make -DCATKIN_WHITELIST_PACKAGES=""
}

function build_aarch64() {
    error "暂不支持arm！"
}

function build() {
    get_start_time
    if [ $TARGET == "" ]; then
        if [ $ARCH == "aarch64" ]; then
            build_aarch64
        else
            build_x86_64
        fi
    else
        catkin_make -DCATKIN_WHITELIST_PACKAGES="$TARGET"
    fi
    success "build success"
}

function clean() {
    rm -fr ${AUTOCAR_ROOT_DIR}/devel ${AUTOCAR_ROOT_DIR}/build
}

function main() {
    info "task: $TASK"
    case $TASK in
    "build")
        build
        ;;
    "clean")
        clean
        ;;
    *) ;;
    esac
}

main
