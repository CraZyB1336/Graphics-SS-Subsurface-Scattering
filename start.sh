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

# Spinner animation with progress bar.
cmake_with_bar_and_spinner() {
    local frames_spin=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')
    local log_file="/tmp/cmake_output.log"

    if [ $LOG == true ]; then
        cmake --build ./
    else
        cmake --build ./ > "$log_file" 2>&1 &
        local pid=$!

        # Hide the cursor
        tput civis

        echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Building Program..."

        # Animation
        local frame_index=0
        local current_percentage=0

        while kill -0 $pid 2>/dev/null; do
            local frame=${frames_spin[$frame_index]}

            # Check for latest percentage.
            local latest_percentage=$(grep -o '\[[[:space:]]*[0-9]*%\]' "$log_file" 2>/dev/null | grep -o '[0-9]*' | tail -1)
            if [[ $latest_percentage =~ ^[0-9]+$ ]]; then
                current_percentage=$latest_percentage
            fi

            local bar_width=40
            local filled=$((current_percentage * bar_width / 100))
            local empty=$((bar_width - filled))

            local progress_bar=""
            for ((i=0; i<filled; i++)); do
                progress_bar+="█"
            done
            for ((i=0; i<empty; i++)); do
                progress_bar+="▒"
            done

            printf "\r${MAGENTA}${BOLD}[Start]${RESET}\t ${GREEN}${BOLD}%s ${GREEN}${BOLD}%s ${BOLD}${GREEN}%d%%${RESET}" "$frame" "$progress_bar" $current_percentage

            frame_index=$(( (frame_index + 1) % ${#frames_spin[@]} ))
            sleep 0.08
        done

        wait $pid
        local exit_code=$?

        tput cnorm
        printf "\r\033[K"

        if [ $exit_code -eq 0 ]; then
            echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t ${GREEN}${BOLD}████████████████████████████████████████ 100%${RESET}"
        else
            echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t ${RED}${BOLD}CMake building failed${RESET}"
            echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Error details:"
            while IFS= read -r line; do
                echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t ${RED}$line"
            done < "$log_file"
        fi

        rm -f "$log_file"
        return $exit_code
    fi
}


set -e

echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Starting Screen Space Subsurface Scattering Program (SSSS)... ${ITALIC}vrr.. vrr.. cling clang${RESET}"

if test -d "build"; then
    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t Found exisitng build directory..."
    cd build
    
    cmake_with_bar_and_spinner || {
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

if [ $CLEANSTART == false ] && [ $LOG == false ]; then
    echo -e "${MAGENTA}${BOLD}[Start]${RESET}\t To enable logging: ${BOLD}'-l'${RESET} or ${BOLD}'--log'${RESET}"
fi
