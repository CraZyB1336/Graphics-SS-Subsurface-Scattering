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


# Creating build directory
echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Creating build directory"
mkdir build || {
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${RED}Creating build directory failed${RESET}"
    exit 1
}
echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${GREEN}Build directory successfully created${RESET}"
cd build


# Spinner animation
cmake_with_spinner() {
    local frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')
    local log_file="/tmp/cmake_output.log"

    if [ $LOG == true ]; then
        cmake ..
    else
        cmake .. > "$log_file" 2>&1 &
        local pid=$!

        # Hide the cursor
        tput civis

        echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${RESET}Initializing CMake Configurations..."

        # Animation
        local frame_index=0
        while kill -0 $pid 2>/dev/null; do
            local frame=${frames[$frame_index]}
            printf "\r${MAGENTA}${BOLD}[Clean]${RESET}\t ${GREEN}${BOLD}%s" "$frame"
            frame_index=$(( (frame_index + 1) % ${#frames[@]} ))
            sleep 0.08
        done

        wait $pid
        local exit_code=$?

        tput cnorm
        printf "\r\033[K"

        if [ $exit_code -eq 0 ]; then
            echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${GREEN}CMake configuration completed${RESET}"
        else
            echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${RED}CMake configuration failed${RESET}"
            echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Error details:"
            while IFS= read -r line; do
                echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${RED}$line"
            done < "$log_file"
        fi

        rm -f "$log_file"
        return $exit_code
    fi
}

cmake_with_spinner || {
    exit 1
}

echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t ${BOLD}${GREEN}CMake build directory cleaned and configured${RESET}"

if [ $CLEANSTART == false ]; then
    echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t Either run the build bash file \"start.sh\" or execute:
    ${BOLD}${CYAN}cd build${RESET}
    ${BOLD}${CYAN}cmake --build ./${RESET}
    ${BOLD}${CYAN}./SSSS\n${RESET}"

    if [ $LOG == false ]; then
        echo -e "${MAGENTA}${BOLD}[Clean]${RESET}\t To enable logging: ${BOLD}'-l'${RESET} or ${BOLD}'--log'${RESET}"
    fi
fi