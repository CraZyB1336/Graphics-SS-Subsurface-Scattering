#!/bin/bash
RED='\e[31m'
GREEN='\e[32m'
MAGENTA='\e[35m'
CYAN='\e[36m'
RESET='\e[0m\033[0m'
ITALIC='\e[3m'
BOLD='\033[1m'

LOG=false
CLEANSTART=false

while [ $# -gt 0 ]; do
    case $1 in
        -l|--log)
            LOG=true
            shift
            ;;
        -cleanstart)
            CLEANSTART=true
            shift
            ;;
        *)
            echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${RED}Invalid option: $OPTARG" 1>&2
            exit 1;
            ;;
    esac
done

set -e

echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Starting Screen Space Subsurface Scattering Program (SSSS)... ${ITALIC}vrr.. vrr.. cling clang${RESET}"

if test -d "build"; then
    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Found exisitng build directory..."
    cd build

    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Building Program..."
    eval "cmake --build ./ $( [[ $LOG == true ]] && echo "" || echo ">/dev/null")" || {
        echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t ${BOLD}${RED}An error occured during building. Aborting${RESET}"
        exit 1
    }
    
    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t ${BOLD}${GREEN}Building successfull"
    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Starting Program..."

    ./SSSS || {
        echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t ${BOLD}${RED}Unexpected error occured starting the program. 
        Check if CMakeLists has project name \"SSSS\"${RESET}"
    }
else
    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t ${BOLD}${RED}No build directory exists. Aborting${RESET}"
fi

if [ $CLEANSTART == false ]; then
    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t To enable logging: ${BOLD}'-l'${RESET} or ${BOLD}'--log'${RESET}"
fi
