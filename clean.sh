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

# Exit on any error
set -e

echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Cleaning CMake build directory... ${ITALIC}scrub scrub${RESET}"

# Check if directory exists
if test -d "build"; then
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Found existing build directory..."

    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Removing build directory..."

    # Try standard removal. If fails use sudo
    rm -rf build/ || {
        sudo rm -rf build/ || {
            echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${RED}Failed to remove build directory${RESET}"
            exit 1
        }
    }

    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${GREEN}Build directory successfully removed${RESET}"
else
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t No build directory found"
fi

echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Creating build directory"
mkdir build || {
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${RED}Creating build directory failed${RESET}"
    exit 1
}
echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${GREEN}Build directory successfully created${RESET}"
cd build

echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Initializing CMake Configurations..."
echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ..."
eval "cmake .. $( [[ $LOG == true ]] && echo "" || echo ">/dev/null")" || {
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${RED}Initializing CMake Configurations failed"
    exit 1
}

echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${GREEN}CMake build directory cleaned and configured${RESET}"

if [ $CLEANSTART == false ]; then
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Either run the build bash file \"start.sh\" or execute:
    ${BOLD}${CYAN}cd build${RESET}
    ${BOLD}${CYAN}cmake --build ./${RESET}
    ${BOLD}${CYAN}./SSSS\n${RESET}"
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t To enable logging: ${BOLD}'-l'${RESET} or ${BOLD}'--log'${RESET}"
fi