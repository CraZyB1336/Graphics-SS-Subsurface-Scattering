#!/bin/bash
RED='\e[31m'
GREEN='\e[32m'
MAGENTA='\e[35m'
CYAN='\e[36m'
RESET='\e[0m\033[0m'
ITALIC='\e[3m'
BOLD='\033[1m'

LOG=false
NVIDIA=false

while [ $# -gt 0 ]; do
    case $1 in
        -l|--log)
            LOG=true
            shift
            ;;
        --nvidia)
            NVIDIA=true
            shift
            ;;
        *)
            echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${RED}Invalid option: $OPTARG" 1>&2
            exit 1;
            ;;
    esac
done

FLAGS="-cleanstart"
[ $LOG == true ] && FLAGS="$FLAGS -l"

set -e

echo -e "${MAGENTA}${BOLD}[Clean-Start]${RESET}\t Executing \"clean.sh\"..."

./clean.sh $FLAGS || {
    echo -e "${MAGENTA}${BOLD}[Clean-Start]${RESET}\t ${BOLD}${RED}An error occured during cleaning. Aborting"
    exit 1
}

echo -e "${MAGENTA}${BOLD}[Clean-Start]${RESET}\t Executing \"start.sh\"..."

[ $NVIDIA == true ] && FLAGS="$FLAGS --nvidia"

./start.sh $FLAGS || {
    echo -e "${MAGENTA}${BOLD}[Clean-Start]${RESET}\t ${BOLD}${RED}An error occured during starting. Aborting"
    exit 1
}

if [ $LOG == false ]; then
    echo -e "${MAGENTA}${BOLD}[Clean-Start]${RESET}\t To enable logging: ${BOLD}'-l'${RESET} or ${BOLD}'--log'${RESET}"
fi

if [ $NVIDIA == false ]; then
    echo -e "${MAGENTA}${BOLD}[Clean-Start]${RESET}\t To enable nvidia vendor: ${BOLD}'--nvidia'${RESET}"
fi