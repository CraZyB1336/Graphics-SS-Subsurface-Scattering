# Graphics-SS-Subsurface-Scattering
Project to implement subsurface scattering using screen space calculations.

# Building
## How to build
```sh
mkdir build
cd build
cmake ..
cmake --build ./
```
## Run
```sh
./SSSS
```

## How to build using bash scripts.
```sh
./clean.sh # Creates a new build directory and cleans the cmake configurations.
```
```sh
./start.sh # Builds and starts the SSSS program.
```
```sh
./cleanstart.sh # Does all of the above.
```
Add the **-l** or **--log** flag for CMake log outputs.