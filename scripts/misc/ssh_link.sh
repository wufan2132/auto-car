#!/usr/bin/env bash
# Usage:
#  ./ssh_link.sh  [server_name]

SERVER=$1
if [ "$SERVER" == "" ]; then
    echo "please input server_name!"
    echo "Usage: ./ssh_link.sh  [server_name]"
    exit 0
fi
AUTOCAR_ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
source "${AUTOCAR_ROOT_DIR}/config/servers/${SERVER}.sh"
#
echo "this password is ${S_PWD} ${S_PWD_DETALL}"
ssh "${S_USER}@${S_IP}"
