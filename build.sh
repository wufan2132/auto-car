#!/usr/bin/env bash

PROJECT_ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source ${PROJECT_ROOT_DIR}/configure

if [ "$PROJECT_IN_DOCKER" == "false" ]; then
        error "build.sh must run in docker!"
        exit 0
fi

set -e
TASK=""
TARGET=$2
DEBUG_CMD=""
case "$1" in
-h | --help)
    show_usage
    ;;
-b | --build)
    TASK="build"
    ;;
-d | --debug)
    TASK="build"
    DEBUG_CMD="-DCMAKE_BUILD_TYPE=Debug"
    ;;    
-c | --clean)
    TASK="clean"
    ;;
*)
    TASK="build"
    ;;
esac

function build_x86_64() {
    info "build all target"
    catkin_make -DCATKIN_WHITELIST_PACKAGES="" ${DEBUG_CMD}
}

function build_aarch64() {
    error "暂不支持arm！"
}

function build() {
    get_start_time

    if [ "$TARGET" == "" ]; then
        if [ "$ARCH" == "aarch64" ]; then
            build_aarch64
        else
            build_x86_64
        fi
    else
        info "build target: $TARGET"
        catkin_make -DCATKIN_WHITELIST_PACKAGES="$TARGET" ${DEBUG_CMD}
    fi
    success "build success"
}

function clean() {
    rm -fr ${PROJECT_ROOT_DIR}/devel ${PROJECT_ROOT_DIR}/build
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
